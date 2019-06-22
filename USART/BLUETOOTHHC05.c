

#include <avr/io.h>
#include <avr/interrupt.h>

#include "MACROS.h"
#include "STDTYPES.h"
#include "MICROCONIFG.h"
#include "uart.h"
#include "MicroControllerConifg.h"




#include "ATmega32A_T0.h"
#include "STD_TYPES.h"
#include "LCD_Driver.h"


static volatile uint32 pulse =0;
static volatile uint8 i=0 ;


#define		_165_POSTION	13.75
#define		_15_POSTION		1.25
void Servo_Control_OC0(uint8 Deg);



ISR(INT0_vect)
{
	if(i==1)
	{
		TCCR1B =0;
		pulse =TCNT1;
		TCNT1=0;
		i=0;
	}
	if(i==0)
	{
		TCCR1B |= 1<<CS10;
		i=1;
	}
}


//char *a;
int main(void)
{
	UART_init(UART_DOUBLESPEEDMODE_TX_RX_ENABLED,UART_intterupt_Disabled,USART_PARITY_DISABLED_1STOP,USART_SEVEN_BITS_DATA,9600);
	T0_Init(F_CPU_PRESCALE_64,PWMFAST,PWMFAST_NONIVERT,INT_DISABLED);
	Output_Config(PORTB_DIRREG_ADDRESS,PORTB_OUTBLOCK_ADDRESS,OUTPUT_PASS,3);
	_delay_ms(100);
	DDRB=0X0F;
	
	LCD_init();
	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF);

	uint8 i = 15;
	
	DDRD = 0x0B;
	_delay_ms(50);
	GICR |=1<<INT0 ;
	MCUCR |= 1<<ISC00;
	int16_t count_a = 0;

	sei();
	while (1)
	{
		
		for(i=15;i<=165;i++)
		{
			_delay_ms(50);
			PORTD |=1<<PIND3;
			_delay_us(15);
			PORTD &= ~(1<<PIND3);
			count_a = pulse/58;
			
			Servo_Control_OC0(i);
			LCD_clearScreen();
			LCD_displayInt(i);
			LCD_goToRowColumn(1,0);
			LCD_displayInt(count_a);
			UART_sendByte(200);
			UART_sendByte(i);
			UART_sendByte(count_a);
		}
		
		for(i=165;i>15;i--)
		{
			_delay_ms(50);
			PORTD |=1<<PIND3;
			_delay_us(15);
			PORTD &= ~(1<<PIND3);
			count_a = pulse/58;
			
			Servo_Control_OC0(i);
			LCD_clearScreen();
			LCD_displayInt(i);
			LCD_goToRowColumn(1,0);
			LCD_displayInt(count_a);
			UART_sendByte(200);
			UART_sendByte(i);
			UART_sendByte(count_a);
		}
	}
	
	//UART_init(UART_DOUBLESPEEDMODE_TX_RX_ENABLED,UART_intterupt_Disabled,USART_PARITY_DISABLED_1STOP,USART_SEVEN_BITS_DATA,9600);
   
	}
		//UART_sendByte(50);
			
    

void Servo_Control_OC0(uint8 Deg)
{
	float64 Duty=0;
	Duty = (_15_POSTION) + (Deg/180.0) * (_165_POSTION - _15_POSTION) ;
	T0_PWM_OC0(Duty,PWMFAST,PWMFAST_NONIVERT);
}