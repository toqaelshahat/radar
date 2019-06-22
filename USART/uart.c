

#include "uart.h"
 
void UART_init(USART_Mode Mode,USART_Interrupts Interrupt_State,USART_ControlFrame Controls ,USART_DATAFRAME  Data_width,USART_BUADRATE Buad)
{
	UCSRA=0;
	UCSRB=0;
	UCSRC=0;
	
	UCSRA |= (Mode & 0x02) ;
	UCSRB |= (Mode & 0x18) | (Interrupt_State & 0xE0);
	UCSRC |= (Mode & 0x41) | (Controls & 0x38) | (Data_width & 0x06);
	
	if(Data_width == USART_NINE_BITS_DATA)
	  {SET_BIT(UCSRB,UCSZ2);}
	
	switch(Mode)
	{
		case UART_DOUBLESPEEDMODE_RX_ENABLED:
		case UART_DOUBLESPEEDMODE_TX_ENABLED:
		case UART_DOUBLESPEEDMODE_TX_RX_ENABLED:
		UBRRH= ((uint8)(F_CPU/(8.0*Buad) - 1) >>8);
		UBRRL= (uint8)(F_CPU/(8.0*Buad) - 1);
		break;
	                         
											
		
	}
}
	
void UART_sendByte(const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	UDR = data;
	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/	
}

uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	   will be cleared after read this data */	 
    return UDR;		
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************/
}

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}
