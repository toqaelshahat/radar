


#ifndef MICROCONTROLLERCONIFG_H_
#define MICROCONTROLLERCONIFG_H_

	#define F_CPU (1000000U)
	#include <util/delay.h>
	#include <stdio.h>
	#include "STD_TYPES.h"
	#include "MACROS.h"
	typedef uint8  IO_size;
	
	
	/* ------------- CPU Register Address -----------*/
	
	#define  MCU_CONTROL_REG_ADDRESS				((volatile IO_size *)0x55)
	#define  MCU_CONTROL_STATE_REG_ADDRESS			((volatile IO_size *)0x54)
	#define  MCU_EX_INTERRUPTCONTROL_REG_ADDRESS	((volatile IO_size *)0x5B)
	#define  MCU_STATE_REG_ADDRESS					((volatile IO_size *)0x5F)
	#define SFIOR_ADDRESS							((volatile IO_size *) 0x50)
	#define TIMSK_ADDRESS							((volatile IO_size *) 0x59)
	#define TIFR_ADDRESS							((volatile IO_size *) 0x58)
	
	
	#define TIMSK									(*TIMSK_ADDRESS)
	#define TIFR									(*TIFR_ADDRESS)
	#define SFIOR									(*(SFIOR_ADDRESS))
	#define  MCU_CONTROL_REG				(*(MCU_CONTROL_REG_ADDRESS))
	#define  MCU_CONTROL_STATE_REG			(*(MCU_CONTROL_STATE_REG_ADDRESS))
	#define  MCU_EX_INTERRUPTCONTROL_REG	(*(MCU_EX_INTERRUPTCONTROL_REG_ADDRESS))
	#define  MCU_STATE_REG					(*(MCU_STATE_REG_ADDRESS))
	
	
	
	/* ------------ GPIO Address -------------*/ 
	#define PORTA_OUTPUTREG_ADDRESS ((uint8 *)0x3B)
	#define PORTA_DIRREG_ADDRESS ((uint8 *)0x3A)
	#define PORTA_INPUTREG_ADDRESS ((uint8 *)0x39)
	#define PORTA_OUTBLOCK_ADDRESS ((uint8 *)0x39)
	#define PORTA_INPUTMODE_ADDRESS ((uint8 *)0x3B)
	
	
	#define PORTB_OUTPUTREG_ADDRESS ((uint8 *)0x38)
	#define PORTB_DIRREG_ADDRESS ((uint8 *)0x37)
	#define PORTB_INPUTREG_ADDRESS ((uint8 *)0x36)
	/* this Register Controls Whether The Output is passed or the pin will stay in float Mode */ 
	#define PORTB_OUTBLOCK_ADDRESS ((uint8 *)0x36)
	/* This Register Selects the Input Mode */
	#define PORTB_INPUTMODE_ADDRESS ((uint8 *)0x38)
	
	#define PORTC_OUTPUTREG_ADDRESS ((uint8 *)0x35)
	#define PORTC_DIRREG_ADDRESS ((uint8 *)0x34)
	#define PORTC_INPUTREG_ADDRESS ((uint8 *)0x33)
	#define PORTC_OUTBLOCK_ADDRESS ((uint8 *)0x33)
	#define PORTC_INPUTMODE_ADDRESS ((uint8 *)0x35)
	
	#define PORTD_OUTPUTREG_ADDRESS ((uint8 *)0x32)
	#define PORTD_DIRREG_ADDRESS ((uint8 *)0x31)
	#define PORTD_INPUTREG_ADDRESS ((uint8 *)0x30)
	#define PORTD_OUTBLOCK_ADDRESS ((uint8 *)0x30)
	#define PORTD_INPUTMODE_ADDRESS ((uint8 *)0x32)
	
	#define PORTA_OUTPUTREG  (* (volatile uint8 * )PORTA_OUTPUTREG_ADDRESS )
	#define PORTA_DIRREG  (* (volatile uint8 * )PORTA_DIRREG_ADDRESS )
	#define PORTA_INPUTREG  (* (volatile uint8 * )PORTA_INPUTREG_ADDRESS )

	#define PORTB_OUTPUTREG  (* (volatile uint8 * )PORTB_OUTPUTREG_ADDRESS )
	#define PORTB_DIRREG  (* (volatile uint8 * )PORTB_DIRREG_ADDRESS )
	#define PORTB_INPUTREG  (* (volatile uint8 * )PORTB_INPUTREG_ADDRESS )
	
	#define PORTC_OUTPUTREG  (* (volatile uint8 * )PORTC_OUTPUTREG_ADDRESS )
	#define PORTC_DIRREG  (* (volatile uint8 * )PORTC_DIRREG_ADDRESS )
	#define PORTC_INPUTREG  (* (volatile uint8 * )PORTC_INPUTREG_ADDRESS )
	
	#define PORTD_OUTPUTREG  (* (volatile uint8 * )PORTD_OUTPUTREG_ADDRESS )
	#define PORTD_DIRREG	 (*(volatile uint8 * )PORTD_DIRREG_ADDRESS )
	#define PORTD_INPUTREG   (*(volatile uint8 * )PORTD_INPUTREG_ADDRESS )
	
	
	typedef enum  {
					INPUT=0,
					OUTPUT=1,
				  }IO_Type;
	typedef enum {
					FLOAT_MODE=0,
					PULLUP_MODE=1,
				 }Input_Mode;	
				 
	typedef enum {
					OUTPUT_PASS=0,
					OUTPUT_BLOCK=1,
				 }Output_Mode;
	
	typedef enum{
					LOW=0,
					HIGH=1,
				}Digital_State;
				
	void Input_Config(
					  volatile IO_size * DIR_Reg ,
					  volatile IO_size * InpuT_ModeReg,
					  Input_Mode Mode,
					  uint8 pin_Number);
					  
	void Output_Config(
						volatile IO_size * DIR_Reg,
						volatile IO_size * Output_ModeReg,
						Output_Mode Mode,
						uint8 pin_Number
						);
						
	void Output_Handle(volatile IO_size * OutReg ,
						uint8 pin_Number,
						Digital_State State);
	Digital_State Input_Handle(volatile IO_size * Input_reg,
								uint8 pin_Number);		
#endif /* MICROCONTROLLERCONIFG_H_ */