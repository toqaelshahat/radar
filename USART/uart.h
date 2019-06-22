 

#ifndef UART_H_
#define UART_H_

#include "MICROCONIFG.h"
#include "STDTYPES.h"
#include "MACROS.h"

	typedef  enum {
					USART_PARITY_DISABLED_1STOP=0x00,
					USART_PARITY_DISABLED_2STOP=0x08,
					USART_PARITY_EVEN_1STOP=0x20,
					USART_PARITY_EVEN_2STOP=0x28,
					USART_PARITY_ODD_1STOP=0x10,
					USART_PARITY_ODD_2STOP=0x38,
					}USART_ControlFrame;
	typedef  enum {
				   UART_NORMALMODE_TX_RX_ENABLED=0x18,
				   UART_NORMALMODE_TX_ENABLED=0x18,
				   UART_NORMALMODE_RX_ENABLED=0x10,
				   UART_DOUBLESPEEDMODE_TX_RX_ENABLED=0x1A,
				   UART_DOUBLESPEEDMODE_TX_ENABLED=0x0A,
				   UART_DOUBLESPEEDMODE_RX_ENABLED=0x12,
				   USART_TX_RX_ENABLED_SAMPLE_RISING=0x59,
				   USART_TX_RX_ENABLED_SAMPLE_FALLING=0x58,
				   USART_RX_ENABLED_SAMPLE_RISING=0x51,
				   USART_RX_ENABLED_SAMPLE_FALLING=0x50,
				   USART_TX_ENABLED_SAMPLE_RISING=0x49,
				   USART_TX_ENABLED_SAMPLE_FALLING=0x48,
				   }USART_Mode;
				   
	typedef  enum {
				   UART_intterupt_Disabled=0x00,
				   UART_RX_Comp=0x80,
				   UART_TX_Comp=0x40,
				   UART_DataReg_Empty=0x20,
				   UART_RX_TX_Comp=0xC0,
				   UART_Rx_Comp_DataReg_Empty=0xA0,
				   UART_Tx_Comp_DataReg_Empty=0x60,
				   UART_Rx_TX_Comp_DataReg_Empty=0xE0,
				   }USART_Interrupts;
	typedef enum {
					USART_FIVE_BITS_DATA=0x00,
					USART_SIX_BITS_DATA=0x02,
					USART_SEVEN_BITS_DATA=0x04,
					USART_EIGHT_BITS_DATA=0x06,
					USART_NINE_BITS_DATA=0x06,
				  }USART_DATAFRAME;
			
	typedef enum {
			USART_BAUD_2400=2400,
			USART_BAUD_4800=4800,
			USART_BAUD_9600=9600,
			USART_BAUD_14400=14400,
			USART_BAUD_19200=19200,
			USART_BAUD_28800=28800,
			USART_BAUD_38400=38400,
			USART_BAUD_57600=57600,
			USART_BAUD_76800=76800,
			USART_BAUD_115200=115200,
			USART_BAUD_230400=230400,
			USART_BAUD_250k=250000,
		}USART_BUADRATE;		  
				  
void UART_init(USART_Mode Mode,USART_Interrupts Interrupt_State,USART_ControlFrame Controls ,USART_DATAFRAME  Data_width , USART_BUADRATE Buad);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #


uint8 UART_ErrorCheck(void);
#endif /* UART_H_ */