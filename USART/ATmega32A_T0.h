

#ifndef ATMEGA32A_T0_H_
#define ATMEGA32A_T0_H_

		#include "MicroControllerConifg.h"
		#include "STD_TYPES.h"
		#include "MACROS.h"
		
		#define TCCR0_ADDRESS ((volatile uint8 *)0x53)
		#define TCNT0_ADDRESS ((volatile uint8 *)0x52)
		#define OCR0_ADDRESS  ((volatile uint8 *)0x5C)
		
		#define TCCR0		  (* TCCR0_ADDRESS)
		#define TCNT0		  (* TCNT0_ADDRESS)
		#define OCR0		  (* OCR0_ADDRESS)
	typedef enum
	{
		NORMALMODE=0x00,
		CTC=0x08,
		PWMFAST=0x48,
		PWMPHC=0x40,
	}T0_Mode;


	typedef enum
	{
		OC0_DISCONNECT=0x00,
		NONPWM_CLEAR=0x20,
		NONPWM_SET=0x30,
		NONPWM_TOGGLE=0x10,
		PWMFAST_NONIVERT=0x20,
		PWMFAST_INVERT=0x30,
		PWMPHC_CLR_UPCOUNT=0x20,
		PWMPHC_SET_UPCOUNT=0x30,
	}T0_CmpMode;
	
	typedef enum 
	{
		NO_CLOCK,
		F_CPU_PRESCALE_1,
		F_CPU_PRESCALE_8,
		F_CPU_PRESCALE_64,
		F_CPU_PRESCALE_256,
		F_CPU_PRESCALE_1024,
		EXT_CLOCK_SFALLING,
		EXT_CLOCK_SRISING,
	}T0_Clock;
	
typedef enum
	{
		INT_DISABLED,
		OVF_ENABLE,
		OUTCMP_ENABLE,
		OUTCMP_OVF_ENABLE,
	}T0_interrupt;
	
	void T0_Init(
					T0_Clock Clk,
					T0_Mode Mode,
					T0_CmpMode OutCmp,
					T0_interrupt int_state
				  );
				  
	void T0_CTC_WaveGenerate(
								float64 F_OC0,
								float64 F_Timer);
								
	void T0_FreqDividor(float32 Factor);
	
	
	void T0_PWM_OC0(
					float32 DutyCycle,
					T0_Mode Mode,
					T0_CmpMode Cmp_Mode );
					
#endif /* ATMEGA32A_T0_H_ */