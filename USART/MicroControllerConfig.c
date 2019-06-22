


	#include "MicroControllerConifg.h"
	
	void Input_Config(
	volatile IO_size * DIR_Reg ,volatile IO_size * InpuT_ModeReg,
	Input_Mode Mode,uint8 pin_Number)
	{
		 CLEAR_BIT(*DIR_Reg , pin_Number);
		*DIR_Reg |= (INPUT << pin_Number);
		
		CLEAR_BIT(*InpuT_ModeReg , pin_Number);
		*InpuT_ModeReg |= (Mode << pin_Number);
	}
	
	void Output_Config(
	volatile IO_size * DIR_Reg,volatile IO_size * Output_ModeReg,
	Output_Mode Mode,uint8 pin_Number)
	{
		CLEAR_BIT(*DIR_Reg , pin_Number);
		*DIR_Reg |= (OUTPUT << pin_Number);
		
		CLEAR_BIT(*Output_ModeReg , pin_Number);
		*Output_ModeReg |= (Mode << pin_Number);
	}
	void Output_Handle(volatile IO_size * OutReg ,
		 uint8 pin_Number,Digital_State State)
		 {
			CLEAR_BIT(*OutReg , pin_Number);
			*OutReg |= (State<<pin_Number); 
		 }
	Digital_State Input_Handle(volatile IO_size * Input_reg,
							   uint8 pin_Number)
		{
			if(IS_BIT_SET(*Input_reg , pin_Number))
			{
				return HIGH;
			}
			return LOW;
		}