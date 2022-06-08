/*
 * sab82532.h
 *
 * Created: 01-06-2022 10:09:04
 *  Author: HP
 */ 


#ifndef SAB82532_H_
#define SAB82532_H_

#include "common_utils.h"
#include "gpio_drv.h"

#define	SAB_NCHAN	2	/* number of channels */
#define	SAB_CHANLEN	0x40	/* length of channel register set */

#define	SAB_CHAN_A	0x00	/* channel A register offset */
#define	SAB_CHAN_B	0x40	/* channel B register offset */

#define	SAB_RFIFO	0x00	/* r: rx fifo */
#define	SAB_XFIFO	0x00	/* w: tx fifo */
#define	SAB_STAR	0x20	/* r: status register */
#define	SAB_CMDR	0x20	/* w: command register */
#define	SAB_MODE	0x22	/* rw: mode register */
#define	SAB_TIMR	0x23	/* rw: timer register */
#define	SAB_XON		0x24	/* rw: xon character */
#define	SAB_XOFF	0x25	/* rw: xoff character */
#define	SAB_TCR		0x26	/* rw: termination character */
#define	SAB_DAFO	0x27	/* rw: data format */
#define	SAB_RFC		0x28	/* rw: rfifo control register */
#define	SAB_RBCL	0x2a	/* r: rx byte count low */
#define	SAB_TBCL	0x2a	/* w: tx byte count low */
#define	SAB_RBCH	0x2b	/* r: rx byte count high */
#define	SAB_XBCH	0x2b	/* w: tx byte count high */
#define	SAB_CCR0	0x2c	/* rw: channel configuration register 0 */
#define	SAB_CCR1	0x2d	/* rw: channel configuration register 1 */
#define	SAB_CCR2	0x2e	/* rw: channel configuration register 2 */
#define	SAB_CCR3	0x2f	/* rw: channel configuration register 3 */
#define	SAB_TSAX	0x30	/* w: time-slot assignment register tx */
#define	SAB_TSAR	0x31	/* w: time-slot assignment register rx */
#define	SAB_XCCR	0x32	/* w: tx channel capacity register */
#define	SAB_RCCR	0x33	/* w: receive channel capacity register */
#define	SAB_VSTR	0x34	/* r: version status */
#define	SAB_BGR		0x34	/* w: baud rate generator */
#define	SAB_TIC		0x35	/* w: transmit immediate character */
#define	SAB_MXN		0x36	/* w: mask xon character */
#define	SAB_MXF		0x37	/* w: mask xoff character */
#define	SAB_GIS		0x38	/* r: global interrupt status */
#define	SAB_IVA		0x38	/* w: interrupt vector address */
#define	SAB_IPC		0x39	/* rw: interrupt port configuration */
#define	SAB_ISR0	0x3a	/* r: interrupt status 0 */
#define	SAB_IMR0	0x3a	/* w: interrupt mask 0 */
#define	SAB_ISR1	0x3b	/* r: interrupt status 1 */
#define	SAB_IMR1	0x3b	/* w: interrupt mask 1 */
#define	SAB_PVR		0x3c	/* rw: port value register */
#define	SAB_PIS		0x3d	/* r: port interrupt status */
#define	SAB_PIM		0x3d	/* w: port interrupt mask */
#define	SAB_PCR		0x3e	/* w: port configuration register */
#define	SAB_CCR4	0x3f	/* rw: channel configuration register 4 */

/* SAB_STAR: status register */
#define	SAB_STAR_XDOV	0x80	/* transmit data overflow */
#define	SAB_STAR_XFW	0x40	/* transmit fifo write enable */
#define	SAB_STAR_RFNE	0x20	/* rfifo not empty */
#define	SAB_STAR_FCS	0x10	/* flow control status */
#define	SAB_STAR_TEC	0x08	/* tx immediate char is executing */
#define	SAB_STAR_CEC	0x04	/* command is executing */
#define	SAB_STAR_CTS	0x02	/* cts status: 0:inactive/high,1:active/low */

/* SAB_CMDR: command register */
#define	SAB_CMDR_RMC	0x80	/* receive message complete */
#define	SAB_CMDR_RRES	0x40	/* receiver reset */
#define	SAB_CMDR_RFRD	0x20	/* receive fifo read enable */
#define	SAB_CMDR_STI	0x10	/* start timer */
#define	SAB_CMDR_XF	0x08	/* transmit frame */
#define	SAB_CMDR_XRES	0x01	/* transmit reset */

/* SAB_MODE: mode register */
#define	SAB_MODE_FRTS	0x40	/* flow control using rts */
#define	SAB_MODE_FCTS	0x20	/* flow control using cts */
#define	SAB_MODE_FLON	0x10	/* flow control on */
#define	SAB_MODE_RAC	0x08	/* receiver active */
#define	SAB_MODE_RTS	0x04	/* request to send */
#define	SAB_MODE_TRS	0x02	/* timer resolution */
#define	SAB_MODE_TLP	0x01	/* test loop */

/* SAB_TIMR: timer register */
#define	SAB_TIMR_CNT	0xe0	/* count mask */
#define	SAB_TIMR_VAL	0x1f	/* value mask */

/* SAB_DAFO: data format */
#define	SAB_DAFO_XBRK	0x40	/* transmit break */
#define	SAB_DAFO_STOP	0x20	/* stop bit: 0:1 bit, 1:2 bits */
#define	SAB_DAFO_PAR1	0x10	/* parity 1, see below */
#define	SAB_DAFO_PAR0	0x08	/* parity 0, see below */
#define	SAB_DAFO_PARE	0x04	/* parity enable */
#define	SAB_DAFO_CHL1	0x02	/* character length 1, see below */
#define	SAB_DAFO_CHL0	0x01	/* character length 0, see below */

#define	SAB_DAFO_CHL_CSIZE	(SAB_DAFO_CHL1|SAB_DAFO_CHL0)
#define	SAB_DAFO_CHL_CS5	(SAB_DAFO_CHL1|SAB_DAFO_CHL0)
#define	SAB_DAFO_CHL_CS6	(SAB_DAFO_CHL1)
#define	SAB_DAFO_CHL_CS7	(SAB_DAFO_CHL0)
#define	SAB_DAFO_CHL_CS8	(0)

#define	SAB_DAFO_PARMASK	(SAB_DAFO_PAR1|SAB_DAFO_PAR0|SAB_DAFO_PARE)
#define	SAB_DAFO_PAR_MARK	(SAB_DAFO_PAR1|SAB_DAFO_PAR0|SAB_DAFO_PARE)
#define	SAB_DAFO_PAR_EVEN	(SAB_DAFO_PAR1|SAB_DAFO_PARE)
#define	SAB_DAFO_PAR_ODD	(SAB_DAFO_PAR0|SAB_DAFO_PARE)
#define	SAB_DAFO_PAR_SPACE	(SAB_DAFO_PARE)
#define	SAB_DAFO_PAR_NONE	(0)

/* SAB_RFC: rfifo control register */
#define	SAB_RFC_DPS	0x40	/* disable parity storage */
#define	SAB_RFC_DXS	0x20	/* disable storage of xon/xoff characters */
#define	SAB_RFC_RFDF	0x10	/* rfifo data format: 0 data,1 data+stat */
#define	SAB_RFC_RFTH1	0x08	/* rfifo threshold level 1, see below */
#define	SAB_RFC_RFTH0	0x04	/* rfifo threshold level 0, see below */
#define	SAB_RFC_TCDE	0x01	/* termination character detection enable */

#define	SAB_RFC_RFTH_MASK	(SAB_RFC_RFTH1|SAB_RFC_RFTH0)
#define	SAB_RFC_RFTH_32CHAR	(SAB_RFC_RFTH1|SAB_RFC_RFTH0)
#define	SAB_RFC_RFTH_16CHAR	(SAB_RFC_RFTH1)
#define	SAB_RFC_RFTH_4CHAR	(SAB_RFC_RFTH0)
#define	SAB_RFC_RFTH_1CHAR	(0)

/* SAB_RBCH: received byte count high */
#define	SAB_RBCH_DMA	0x80	/* read back of XBCH DMA bit */
#define	SAB_RBCH_CAS	0x20	/* read back of XBCH CAS bit */
#define	SAB_RBCH_CNT	0x0f	/* ms 4 bits of rx byte count (not used) */

/* SAB_XBCH: transmit byte count high */
#define	SAB_XBCH_DMA	0x80	/* dma mode: 1:dma, 0:interrupt */
#define	SAB_XBCH_CAS	0x20	/* carrier detect auto-start */
#define	SAB_XBCH_XC	0x10	/* transmit continuously */
#define	SAB_XBCH_CNT	0x0f	/* ms 4 bits of tx byte count */

/* SAB_CCR0: channel configuration register 0 */
#define	SAB_CCR0_PU	0x80	/* 0:power-down, 1:power-up */
#define	SAB_CCR0_MCE	0x40	/* master clock enable */
#define	SAB_CCR0_SC2	0x10	/* serial port config 2, see below */
#define	SAB_CCR0_SC1	0x08	/* serial port config 1, see below */
#define	SAB_CCR0_SC0	0x04	/* serial port config 0, see below */
#define	SAB_CCR0_SM1	0x02	/* serial mode 1, see below */
#define	SAB_CCR0_SM0	0x01	/* serial mode 0, see below */

#define	SAB_CCR0_SC_MASK	(SAB_CCR0_SC2|SAB_CCR0_SC1|SAB_CCR0_SC0)
#define	SAB_CCR0_SC_NRZ		(0)
#define	SAB_CCR0_SC_NRZI	(SAB_CCR0_SC1)
#define	SAB_CCR0_SC_FM0		(SAB_CCR0_SC2)
#define	SAB_CCR0_SC_FM1		(SAB_CCR0_SC2|SAB_CCR0_SC0)
#define	SAB_CCR0_SC_MANCHESTER	(SAB_CCR0_SC2|SAB_CCR0_SC1)

#define	SAB_CCR0_SM_MASK	(SAB_CCR0_SM1|SAB_CCR0_SM0)
#define	SAB_CCR0_SM_DLC		(0)
#define	SAB_CCR0_SM_DLCLOOP	(SAB_CCR0_SM0)
#define	SAB_CCR0_SM_BISYNC	(SAB_CCR0_SM1)
#define	SAB_CCR0_SM_ASYNC	(SAB_CCR0_SM1|SAB_CCR0_SM0)

/* SAB_CCR1: channel configuration register 1 */
#define	SAB_CCR1_ODS	0x10	/* Output driver select:1:pushpull,0:odrain */
#define	SAB_CCR1_BCR	0x08	/* bit clock rate: 1:async, 0:isochronous */
#define	SAB_CCR1_CM2	0x04	/* clock mode 2, see below */
#define	SAB_CCR1_CM1	0x02	/* clock mode 1, see below */
#define	SAB_CCR1_CM0	0x01	/* clock mode 0, see below */

#define	SAB_CCR1_CM_MASK	(SAB_CCR1_CM2|SAB_CCR1_CM1|SAB_CCR1_CM0)
#define	SAB_CCR1_CM_7		(SAB_CCR1_CM2|SAB_CCR1_CM1|SAB_CCR1_CM0)

/* SAB_CCR2: channel configuration register 2, depends on clock mode above */
/* clock mode 0a, 1, 4, 5 */
#define	SAB_CCR2_SOC1	0x80	/* special output 1, below */
#define	SAB_CCR2_SOC0	0x40	/* special output 0, below */
#define	SAB_CCR2_SOC_MASK	(SAB_CCR2_SOC1|SAB_CCR2_SOC0)
#define	SAB_CCR2_SOC_RTSHIGH	(SAB_CCR2_SOC1)
#define	SAB_CCR2_SOC_RTSNORM	(0)
#define	SAB_CCR2_SOC_RTSRX	(SAB_CCR2_SOC1|SAB_CCR2_SOC0)
/* clock mode 0b, 2, 3, 6, 7 */
#define	SAB_CCR2_BR9	0x80	/* baud rate bit 9 */
#define	SAB_CCR2_BR8	0x40	/* baud rate bit 8 */
#define	SAB_CCR2_BDF	0x20	/* baud rate division factor: 0:1: 1:BRG */
#define	SAB_CCR2_SSEL	0x10	/* clock source select */
/* clock mode 5 */
#define	SAB_CCR2_XCS0	0x20	/* tx clock shift, bit 0 */
#define	SAB_CCR2_RCS0	0x10	/* rx clock shift, bit 0 */
/* clock mode 0b, 2, 3, 4, 5, 6, 7 */
#define	SAB_CCR2_TOE	0x08	/* tx clock output enable */
/* clock mode 0a, 0b, 1, 2, 3, 4, 5, 6, 7 */
#define	SAB_CCR2_RWX	0x04	/* read/write exchange (dma mode only) */
#define	SAB_CCR2_DIV	0x01	/* data inversion (nrz) */

/* SAB_CCR3: channel configuration register 3 (v2 or greater) */
#define	SAB_CCR3_PSD	0x01	/* dpll phase shift disable (nrz/nrzi) */

/* SAB_TSAX: time-slot assignment register transmit (clock mode 5 only) */
#define	SAB_TSAX_TSNX	0xfc	/* time-slot number transmit */
#define	SAB_TSAX_XCS2	0x02	/* transmit clock shift bit 2 */
#define	SAB_TSAX_XCS1	0x01	/* transmit clock shift bit 1 */

/* SAB_TSAR: time-slot assignment register receive (clock mode 5 only) */
#define	SAB_TSAR_TSNR	0xfc	/* time-slot number receive */
#define	SAB_TSAR_RCS2	0x02	/* receive clock shift bit 2 */
#define	SAB_TSAR_RCS1	0x01	/* receive clock shift bit 1 */

/* SAB_VSTR: version status register */
#define	SAB_VSTR_CD	0x80	/* carrier detect status */
#define	SAB_VSTR_DPLA	0x40	/* dpll asynchronous */
#define	SAB_VSTR_VMASK	0x0f	/* chip version mask: */
#define	SAB_VSTR_V_1	0x00	/*   version 1 */
#define	SAB_VSTR_V_2	0x01	/*   version 2 */
#define	SAB_VSTR_V_32	0x02	/*   version 3.2 */

/* SAB_GIS: global interrupt status register */
#define	SAB_GIS_PI	0x80	/* universal port interrupt */
#define	SAB_GIS_ISA1	0x08	/* interrupt status a1 */
#define	SAB_GIS_ISA0	0x04	/* interrupt status a0 */
#define	SAB_GIS_ISB1	0x02	/* interrupt status b1 */
#define	SAB_GIS_ISB0	0x01	/* interrupt status b0 */

/* SAB_IVA: interrupt vector address */
#define	SAB_IVA_MASK	0xf8	/* interrupt vector address mask */

/* SAB_IPC: interrupt port configuration */
#define	SAB_IPC_VIS	0x80	/* masked interrupt bits visible */
#define	SAB_IPC_SLAMASK	0x18	/* slave address mask */
#define	SAB_IPC_CASM	0x04	/* cascading mode */
#define	SAB_IPC_ICMASK	0x03	/* port config mask: */
#define	SAB_IPC_ICOD	0x00	/*   open drain output */
#define	SAB_IPC_ICPL	0x01	/*   push/pull active low output */
#define	SAB_IPC_ICPH	0x03	/*   push/pull active high output */

/* SAB_ISR0: interrupt status 0 */
#define	SAB_ISR0_TCD	0x80	/* termination character detected */
#define	SAB_ISR0_TIME	0x40	/* time-out limit exceeded */
#define	SAB_ISR0_PERR	0x20	/* parity error */
#define	SAB_ISR0_FERR	0x10	/* framing error */
#define	SAB_ISR0_PLLA	0x08	/* dpll asynchronous */
#define	SAB_ISR0_CDSC	0x04	/* carrier detect status change */
#define	SAB_ISR0_RFO	0x02	/* rfifo overflow */
#define	SAB_ISR0_RPF	0x01	/* receive pool full */

/* SAB_ISR1: interrupt status 1 */
#define	SAB_ISR1_BRK	0x80	/* break detected */
#define	SAB_ISR1_BRKT	0x40	/* break terminated */
#define	SAB_ISR1_ALLS	0x20	/* all sent */
#define	SAB_ISR1_XOFF	0x10	/* xoff detected */
#define	SAB_ISR1_TIN	0x08	/* timer interrupt */
#define	SAB_ISR1_CSC	0x04	/* clear to send status change */
#define	SAB_ISR1_XON	0x02	/* xon detected */
#define	SAB_ISR1_XPR	0x01	/* transmit pool ready */

/* SAB_IMR0: interrupt mask 0 */
#define	SAB_IMR0_TCD	0x80	/* termination character detected */
#define	SAB_IMR0_TIME	0x40	/* time-out limit exceeded */
#define	SAB_IMR0_PERR	0x20	/* parity error */
#define	SAB_IMR0_FERR	0x10	/* framing error */
#define	SAB_IMR0_PLLA	0x08	/* dpll asynchronous */
#define	SAB_IMR0_CDSC	0x04	/* carrier detect status change */
#define	SAB_IMR0_RFO	0x02	/* rfifo overflow */
#define	SAB_IMR0_RPF	0x01	/* receive pool full */

/* SAB_ISR1: interrupt mask 1 */
#define	SAB_IMR1_BRK	0x80	/* break detected */
#define	SAB_IMR1_BRKT	0x40	/* break terminated */
#define	SAB_IMR1_ALLS	0x20	/* all sent */
#define	SAB_IMR1_XDU	0x10	/* xoff detected */
#define	SAB_IMR1_TIN	0x08	/* timer interrupt */
#define	SAB_IMR1_CSC	0x04	/* clear to send status change */
#define	SAB_IMR1_XMR	0x02	/* xon detected */
#define	SAB_IMR1_XPR	0x01	/* transmit pool ready */

/* SAB_PVR: port value register */
#define	SAB_PVR_DSR_A	0x01	/* port A DSR */
#define	SAB_PVR_DTR_A	0x02	/* port A DTR */
#define	SAB_PVR_DTR_B	0x04	/* port B DTR */
#define	SAB_PVR_DSR_B	0x08	/* port B DSR */
#define	SAB_PVR_MAGIC	0x10	/* dunno... */

/* SAB_CCR4: channel configuration register 4 */
#define	SAB_CCR4_MCK4	0x80	/* master clock divide by 4 */
#define	SAB_CCR4_EBRG	0x40	/* enhanced baud rate generator mode */
#define	SAB_CCR4_TST1	0x20	/* test pin */
#define	SAB_CCR4_ICD	0x10	/* invert polarity of carrier detect */

/* Receive status byte */
#define	SAB_RSTAT_PE	0x80	/* parity error */
#define	SAB_RSTAT_FE	0x40	/* framing error */
#define	SAB_RSTAT_PAR	0x01	/* parity bit */

#define RD_DS_PORT   GPIO_PORT_D
#define RD_DS_PIN    GPIO_PIN_6
   
#define WR_R_RW_PORT GPIO_PORT_D
#define WR_R_RW_PIN  GPIO_PIN_7

#define ALE_PORT     GPIO_PORT_E
#define ALE_PIN      GPIO_PIN_1  


#define RD_DS_LINE    ((gpio_obj_t){RD_DS_PORT,RD_DS_PIN,GPIO_LVL_HIGH})
#define WR_R_RW_LINE  ((gpio_obj_t){WR_R_RW_PORT,WR_R_RW_PIN,GPIO_LVL_HIGH})
#define ALE_LINE      ((gpio_obj_t){ALE_PORT,ALE_PIN,GPIO_LVL_HIGH})

#define ADDR_DATA0_PORT  GPIO_PORT_A
#define ADDR_DATA0_PIN   GPIO_PIN_0

#define ADDR_DATA1_PORT  GPIO_PORT_A
#define ADDR_DATA1_PIN   GPIO_PIN_1

#define ADDR_DATA2_PORT  GPIO_PORT_A
#define ADDR_DATA2_PIN   GPIO_PIN_2

#define ADDR_DATA3_PORT  GPIO_PORT_A
#define ADDR_DATA3_PIN   GPIO_PIN_3

#define ADDR_DATA4_PORT  GPIO_PORT_A
#define ADDR_DATA4_PIN   GPIO_PIN_4

#define ADDR_DATA5_PORT  GPIO_PORT_A
#define ADDR_DATA5_PIN   GPIO_PIN_5

#define ADDR_DATA6_PORT  GPIO_PORT_A
#define ADDR_DATA6_PIN   GPIO_PIN_6

#define ADDR_DATA7_PORT  GPIO_PORT_A
#define ADDR_DATA7_PIN   GPIO_PIN_7


#define ADDR_DATA_LINE0 	((gpio_obj_t){ADDR_DATA0_PORT,ADDR_DATA0_PIN,GPIO_LVL_HIGH})
#define ADDR_DATA_LINE1 	((gpio_obj_t){ADDR_DATA1_PORT,ADDR_DATA1_PIN,GPIO_LVL_HIGH})
#define ADDR_DATA_LINE2 	((gpio_obj_t){ADDR_DATA2_PORT,ADDR_DATA2_PIN,GPIO_LVL_HIGH})
#define ADDR_DATA_LINE3 	((gpio_obj_t){ADDR_DATA3_PORT,ADDR_DATA3_PIN,GPIO_LVL_HIGH})
#define ADDR_DATA_LINE4 	((gpio_obj_t){ADDR_DATA4_PORT,ADDR_DATA4_PIN,GPIO_LVL_HIGH})
#define ADDR_DATA_LINE5 	((gpio_obj_t){ADDR_DATA5_PORT,ADDR_DATA5_PIN,GPIO_LVL_HIGH})
#define ADDR_DATA_LINE6 	((gpio_obj_t){ADDR_DATA6_PORT,ADDR_DATA6_PIN,GPIO_LVL_HIGH})
#define ADDR_DATA_LINE7 	((gpio_obj_t){ADDR_DATA7_PORT,ADDR_DATA7_PIN,GPIO_LVL_HIGH})
	
#define SAB82532_MAX_TEC_TIMEOUT 200000	
#define SAB82532_MAX_CEC_TIMEOUT  50000	
	
typedef union {
	struct
	{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}b;
	
	struct
	{
		uint8_t n0:4;
		uint8_t n1:4;
	}n;
	
	uint8_t byte;
	
}addr_data_reg_t;	

typedef struct {
	gpio_obj_t a0;
	gpio_obj_t a1;
	gpio_obj_t a2;
	gpio_obj_t a3;
	gpio_obj_t a4;
	gpio_obj_t a5;
	gpio_obj_t a6;
	gpio_obj_t a7;
	}sab82532_addr_data_lines_t;
	
typedef struct {
	
  gpio_obj_t rd_ds;  // low -> read enable
  gpio_obj_t wrr_rw; // low -> write enable
  gpio_obj_t ale;    // high -> latch address

  sab82532_addr_data_lines_t line;
  
}sab82532_obj_t;

extern sab82532_obj_t sab82532Obj;

void SAB82532_Initialize( sab82532_obj_t *sab);
uint8_t SAB82532_ReadReg(sab82532_obj_t *sab,uint8_t reg);

#endif /* SAB82532_H_ */