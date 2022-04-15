/*
 * boot.c
 *
 * Created: 12-04-2022 10:43:23
 *  Author: HP
 */ 

#include "boot.h"

boot_frame_t bootFrame;
	
void BootInitialize(void) {
	
	BootInterfaceRxCallbackSet(BootRxHandler);
	BootInterfaceInitialize(9600);
}
void BootRxHandler(uint8_t data) {
	
	if(bootFrame.pending_frame)
		return;
		
	if(data == ';' && !bootFrame.start_rec){
	  
	  bootFrame.start_rec = 1;
	  bootFrame.buffer.bytes[ bootFrame.size++ ] = data;
	  
	}else if( bootFrame.start_rec ) {
		
		bootFrame.buffer.bytes[ bootFrame.size++ ] = data;
		
		uint8_t getLen = bootFrame.buffer.data.len;
		
		if( data == ':' && (getLen == bootFrame.size)) {
			 bootFrame.start_rec = 0;
			 bootFrame.size = 0;
			 bootFrame.rx_completed  = 1;
			 bootFrame.pending_frame = 1;
			 BootProccessFrame(&bootFrame);
		}
		
	} 
	
}
void BootTxHandler(uint8_t data) {
	
}

void boot_program_page (uint32_t page, uint8_t *buf)
{
	uint16_t i;
	uint8_t sreg;
	// Disable interrupts.
	//sreg = SREG;
	cli();
	eeprom_busy_wait ();
	boot_page_erase (page);
	boot_spm_busy_wait ();     
	for (i=0; i<SPM_PAGESIZE; i+=2)
	{
		// Set up little-endian word.
		uint16_t w = *buf++;
		w += (*buf++) << 8;
		
		boot_page_fill (page + i, w);
	}
	boot_page_write (page);    
	boot_spm_busy_wait();
	boot_rww_enable ();
	
	//SREG = sreg;
}

uint16_t flash_bytes_count;
boot_frame_t txFrame = {0};
void BootProccessFrame(boot_frame_t *frame) {
	
	switch (frame->buffer.data.cmd)
	{
		case 'H':
		
		PORTB = 0x01;
		
		
			
		txFrame.buffer.data.start = ';';
		txFrame.buffer.data.len = 11;
		txFrame.buffer.data.cmd = 'H';
		
		txFrame.buffer.data.data_end[0] = 'A';
		txFrame.buffer.data.data_end[1] = 'T';
		txFrame.buffer.data.data_end[2] = 'M';
		txFrame.buffer.data.data_end[3] = 'E';
		txFrame.buffer.data.data_end[4] = 'G';
		txFrame.buffer.data.data_end[5] = 'A';
		txFrame.buffer.data.data_end[6]	= '8';
		txFrame.buffer.data.data_end[7]	= ':';
		
		for(int i = 0; i < txFrame.buffer.data.len; i++)
			BootInterfaceTx(txFrame.buffer.bytes[i]);
		break;
		
		case 'D':
		      
			  txFrame.buffer.data.start = ';';
			  txFrame.buffer.data.len = 4;
			  
			  
			  
			  if(flash_bytes_count > 512) {
				  
				  txFrame.buffer.data.cmd = 'C';
				  txFrame.buffer.data.data_end[0] = ':';
				  
				  for(int i = 0; i < txFrame.buffer.data.len; i++)
					BootInterfaceTx(txFrame.buffer.bytes[i]);
					
				  flash_bytes_count = 0;
				  return;
			  }
			  
		      for (int i = flash_bytes_count; i < 64; i ++ )
			  {
				  
					 txFrame.buffer.data.data_end[i] = pgm_read_byte ( i );
					 txFrame.buffer.data.len++;
			  }
			 flash_bytes_count += 64;
			 txFrame.buffer.data.cmd = 'D';
			 txFrame.buffer.data.data_end[64] = ':';
			  
			 for(int i = 0; i < txFrame.buffer.data.len; i++)
			 BootInterfaceTx(txFrame.buffer.bytes[i]);
			  
		break;
		
		case 'R':
		PORTB = 0x02;
		for(int i = 0; i < frame->buffer.data.len; i++)
			BootInterfaceTx(frame->buffer.bytes[i]);
		break;
		default:
		frame->buffer.data.cmd = 'N';
		for(int i = 0; i < frame->buffer.data.len; i++)
			BootInterfaceTx(frame->buffer.bytes[i]);
		break;
	}
	
	
	frame->rx_completed  = 0;
	frame->pending_frame = 0;
}