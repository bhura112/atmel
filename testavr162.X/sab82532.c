/*
 * sab82532.c
 *
 * Created: 01-06-2022 10:09:31
 *  Author: HP
 */
#include "sab82532.h"

sab_obj_t sabObj;

//#define CPU_VECT_NUM 28
//
//#define GIS_VECT _VECTOR(CPU_VECT_NUM)

//ISR(GIS_VECT)
//{
//    putchar('t');
//    putchar('\n');
//    putchar('\r');
//    
//    uint8_t isr0 = SABRegMem.r.isr0;
//    uint8_t isr1 = SABRegMem.r.isr1;
//    
//    if(isr0 & 0x01)
//    {
//        
//    }
//    
//}

void SAB82532_CalcEbrg(uint32_t baud, int *n_ret, int *m_ret) {
    int n, m;

    if (baud == 0) {
        *n_ret = 0;
        *m_ret = 0;
        return;
    }

    n = (SAB_BASE_BAUD * 10) / baud;
    m = 0;
    while (n >= 640) {
        n = n / 2;
        m++;
    }

    n = (n + 5) / 10;

    if ((m == 0) && ((n & 1) == 0)) {
        n = n / 2;
        m++;
    }
    *n_ret = n - 1;
    *m_ret = m;
}

bool SAB82532_WaitCec(sab_obj_t *sab) {
    uint32_t i = sab->cec_time;
    for (;;) {
        if ((SABRegMem.r.star & SAB_STAR_CEC) == 0)
            return 0;
        if (--i == 0)
            return 1;
        _delay_us(1);
    }
    return 0;
}

bool SAB82532_WaitTec(sab_obj_t *sab) {
    uint32_t i = sab->tec_time;
    for (;;) {
        if ((SABRegMem.r.star & SAB_STAR_TEC) == 0)
            return 0;
        if (--i == 0)
            return 1;
        _delay_us(1);
    }
    return 0;
}

void SAB82532_xMemTxIdle(sab_obj_t *sab) {
    if (tstBit(&sab->irqFlags, SAB_REGS_PENDING)) {
        uint8_t tmp;

        clrBit(&sab->irqFlags, SAB_REGS_PENDING);
        sab->dafo = 0;
        SABRegMem.rw.mode = sab->mode;
        SABRegMem.rw.pvr = sab->pvr;
        SABRegMem.w.dafo = sab->dafo;
        SABRegMem.w.bgr = sab->ebrg;

        tmp = SABRegMem.rw.ccr2;
        tmp &= ~0xc0;
        tmp |= ((sab->ebrg >> 2) & 0xc0);
        SABRegMem.rw.ccr2 = tmp;

    }
}

bool SAB82532_xMemFlushFifo(sab_obj_t *sab) {
    SABRegMem.w.cmdr = SAB_CMDR_RRES;
    if (SAB82532_WaitCec(sab)) {
        return 1;
    }

    SABRegMem.w.cmdr = SAB_CMDR_XRES;
    if (SAB82532_WaitCec(sab)) {
        return 1;
    }
    return 0;
}

bool SAB82532_ReceiveFifo(sab_obj_t *sab) {

    int i, rbcl;

    if (SABRegMem.r.star & SAB_STAR_RFNE) {

        rbcl = SABRegMem.r.rbcl & 31;

        if (rbcl == 0)
            rbcl = 32;

        for (i = 0; i < rbcl; i += 2) {
            sab->yfifo[i] = SABRegMem.r.rfifo[0];
        }

        sab->yfifo_size = i;
    }

    if (SAB82532_WaitCec(sab))
        return 1;

    SABRegMem.w.cmdr = SAB_CMDR_RMC;

    if (SAB82532_WaitCec(sab))
        return 1;

    return (0);
}

bool SAB82532_TransmitFifo(sab_obj_t *sab) {

    int i;

    while (!(SABRegMem.r.star & SAB_STAR_XFW));
    
    for (i = 0; i < sab->yfifo_size; i++)
        SABRegMem.w.xfifo[i] = sab->yfifo[i];

    if (SAB82532_WaitCec(sab))
        return 1;

    SABRegMem.w.cmdr = SAB_CMDR_XF;

    if (SAB82532_WaitCec(sab))
        return 1;

    return (0);
}

bool SAB82532_xMemGetCChar(sab_obj_t *sab, uint8_t *chr) {

    if ((SABRegMem.r.star & SAB_STAR_RFNE) != 0) {
        if (SAB82532_WaitCec(sab))
            return 1;
        SABRegMem.w.cmdr = SAB_CMDR_RFRD;
        if (SAB82532_WaitCec(sab))
            return 1;
        while ((SABRegMem.r.isr0 & SAB_ISR0_TCD) == 0);
        *chr = SABRegMem.r.rfifo[0];
        SABRegMem.w.cmdr = SAB_CMDR_RMC;
        if (SAB82532_WaitCec(sab))
            return 1;

        return 0;
    }
    return (0);

}

bool SAB82532_xMemGetFChar(sab_obj_t *sab, uint8_t *chr) {

    while ((SABRegMem.r.star & (SAB_STAR_CEC | SAB_STAR_RFNE)) != SAB_STAR_RFNE);

    SABRegMem.w.cmdr = SAB_CMDR_RFRD;
    if (SAB82532_WaitCec(sab))
        return 1;

    while ((SABRegMem.r.isr0 & SAB_ISR0_TCD) == 0);
    *chr = SABRegMem.r.rfifo[0];

    SABRegMem.w.cmdr = SAB_CMDR_RMC;
    if (SAB82532_WaitCec(sab))
        return 1;

    return 0;
}

bool SAB82532_xMemPutFChar(sab_obj_t *sab, uint8_t chr) {

    if (SABRegMem.r.star != (SAB_STAR_CTS | SAB_STAR_XFW))
        return 1;

    SABRegMem.w.xfifo[0] = chr;

    SABRegMem.w.cmdr = SAB_CMDR_XF;

    if (SAB82532_WaitCec(sab))
        return 1;

    return 0;
}

bool SAB82532_xMemPutTChar(sab_obj_t *sab, uint8_t chr) {

    if (chr == 0)
        return 0;

    if (SAB82532_WaitTec(sab))
        return 1;

    SABRegMem.w.tic = chr;

    if (SAB82532_WaitTec(sab))
        return 1;

    return 0;
}

bool SAB82532_xMemSetUp(sab_obj_t *sab) {

    SABRegMem.w.ccr0 = 0;

    SABRegMem.w.ccr0 = /*SAB_CCR0_MCE | */SAB_CCR0_SC_NRZ | SAB_CCR0_SM_ASYNC;

    SABRegMem.w.ccr1 = SAB_CCR1_ODS | SAB_CCR1_BCR | SAB_CCR1_CM_1;

    SABRegMem.w.ccr2 = SAB_CCR2_BDF | SAB_CCR2_SSEL | SAB_CCR2_TOE;

    SABRegMem.w.ccr3 = 0;

    SABRegMem.w.ccr3 = /*SAB_CCR4_MCK4 |*/ SAB_CCR4_EBRG;

    sab->mode = SAB_MODE_RTS |  SAB_MODE_FRTS | SAB_MODE_RAC;

    SABRegMem.w.mode = sab->mode;

    SABRegMem.w.rfc = SAB_RFC_DPS | SAB_RFC_DXS | SAB_RFC_RFTH_32CHAR;

    SABRegMem.w.pcr = 0xe0;

    SABRegMem.w.ipc = SAB_IPC_ICPH;

    // SABRegMem.w.iva = CPU_VECT_NUM << 1;

    if (SAB82532_WaitCec(sab)) {
        return 1;
    }

    if (SAB82532_WaitTec(sab)) {
        return 1;
    }

    SABRegMem.w.imr0 = 0xFF;
    SABRegMem.w.imr1 = 0xFF;
    
    sab->ygis  = SABRegMem.r.gis;
    sab->yisr0 = SABRegMem.r.isr0;
    sab->yisr1 = SABRegMem.r.isr1;

    uint8_t temp = SABRegMem.rw.ccr0;

    temp |= SAB_CCR0_PU; //power up

    SABRegMem.w.ccr0 = temp;

    sab->int_m0 = SAB_IMR0_PERR | SAB_IMR0_FERR | SAB_IMR0_RFO |
            SAB_IMR0_PLLA | SAB_IMR0_RPF;

    SABRegMem.w.imr0 = sab->int_m0;

    sab->int_m1 = SAB_IMR1_BRKT | SAB_IMR1_ALLS | SAB_IMR1_TIN |
            SAB_IMR1_CSC | SAB_IMR1_XPR;

    SABRegMem.w.imr1 = sab->int_m1;

    setBit(&sab->irqFlags, SAB_ALLS);
    setBit(&sab->irqFlags, SAB_XPR);

    return 0;
}

bool SAB82532_xMemInitiailze(sab_obj_t *sab, uint32_t baud) {

    int n = 0, m = 0;

    MCUCR |= (1 << SRE) ;

    SFIOR = (1 << XMM2) | (1 << XMM1) |(1 << XMM0);

    SAB82532_CalcEbrg(baud, &n, &m);

    sab->ebrg = n | (m << 6);
    sab->tec_time = (2457600UL) / baud;
    sab->cec_time = sab->tec_time >> 2;

    if (SAB82532_xMemSetUp(sab))
        return 1;

    setBit(&sab->irqFlags, SAB_REGS_PENDING);

    if (tstBit(&sab->irqFlags, SAB_XPR))
        SAB82532_xMemTxIdle(sab);

    return 0;
}

//
//bool SAB82532_xMemGetc(sab_obj_t *sab,uint8_t *chr) {
//
//    uint8_t r, len, ipc;
//
//    *chr = 0;
//
//    ipc = SABReg(SAB_IPC).byte;
//
//    SABReg(SAB_IPC).byte = ipc | SAB_IPC_VIS;
//again:
//    do {
//        r = SABReg(SAB_STAR).byte;
//    } while ((r & SAB_STAR_RFNE) == 0);
//
//    if (SAB82532_WaitCec())
//        return 1;
//
//    SABReg(SAB_STAR).byte = SAB_CMDR_RFRD;
//    do {
//        r = SABReg(SAB_ISR0).byte;
//    } while ((r & SAB_ISR0_TCD) == 0);
//
//    len = SABReg(SAB_RBCL).byte & (32 - 1);
//    if (len == 0)
//        goto again;
//
//    r = SABReg(SAB_RFIFO).byte;
//
//    if (SAB82532_WaitCec())
//        return 1;
//
//    SABReg(SAB_CMDR).byte = SAB_CMDR_RMC;
//    SABReg(SAB_IPC).byte = ipc;
//
//    *chr = r;
//
//    return 0;
//}