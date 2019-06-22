

#include "ATmega32A_T0.h"
#define ROUND_FACTOR (0.5)

void T0_Init(
				T0_Clock Clk,
				T0_Mode Mode,
				T0_CmpMode OutCmp,
				T0_interrupt int_state)
		{
			TCCR0 = 0x00;
			TIMSK &= 0xFC;
			
			TCCR0 |= Clk | Mode | OutCmp;
			TIMSK |= int_state;
	
		}
		
		
		void T0_CTC_WaveGenerate(
									float64 F_OC0,
									float64 F_Timer)
		{
			OCR0 = ((F_Timer / (2*F_OC0))-1)+ ROUND_FACTOR;
			
			Output_Config(
						PORTB_DIRREG_ADDRESS,
						PORTB_OUTBLOCK_ADDRESS,
						OUTPUT_PASS,3);
		}
		
									
void T0_FreqDividor(float32 Factor)
					{
						OCR0 = (Factor / 2.0) -1;
						Output_Config(
						PORTB_DIRREG_ADDRESS,
						PORTB_OUTBLOCK_ADDRESS,
						OUTPUT_PASS,3);
					}
					
					
void T0_PWM_OC0(float32 DutyCycle,T0_Mode Mode,T0_CmpMode Cmp_Mode )
{
	switch (Mode)
	{
		case PWMFAST:
						switch(Cmp_Mode)
						{
							case PWMFAST_INVERT:
													OCR0= (((100-DutyCycle)/100.0) * 255)+ROUND_FACTOR;
													break;
							case PWMFAST_NONIVERT:
													OCR0= ((DutyCycle/100.0) * 255)+ROUND_FACTOR; 
													break;
							default:
									return;
						}
					break;
		case  PWMPHC:
							break;
		default:
					return;
	}
}