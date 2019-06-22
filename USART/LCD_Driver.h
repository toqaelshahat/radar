/*
 * LCD_Driver.h
 *
 * Created: 24/04/2019 05:27:05 م
 *  Author: Azazi
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

	#include "MicroControllerConifg.h"
	#include "STD_TYPES.h"
	#include "MACROS.h"
	
#define	EIGHT_DATABIT_MODE	0		/* 1 for eight bit mode , 0 for four bit mode*/
#define UPPER_DATA_PORT		1		/* 1 for upper 4 pins , 0 for lower 4 pins */

#define RS		0
#define RW		1
#define EN		2

#define LCD_CONTROL_REG_DIRECTION	PORTA_DIRREG
#define LCD_CONTROL_REG_WRITE		PORTA_OUTPUTREG
#define	LCD_DATA_REG_DIRECTION		PORTA_DIRREG
#define LCD_DATA_REG_WRITE			PORTA_OUTPUTREG

/*List of Commands Code*/
#define CLEAR_DISPLAY				0x01
#define RETURN_HOME					0x02
#define DECREMENT_CURSOR			0x04
#define INCREMENT_CURSOR			0x06
#define SHIFT_DISPLAY_RIGHT			0x05
#define SHIFT_DISPLAY_LEFT			0x07
#define	DISPLAY_OFF					0x08
#define DISPLAY_ON_CURSOR_OFF		0x0C
#define DISPLAY_ON_CURSOR_ON		0x0E
#define DISPLAY_ON_CURSOR_BLINK		0x0F
#define SHIFT_ENTIRE_DISPLAY_LEFT	0x18
#define SHIFT_ENTIRE_DISPLAY_RIGHT	0x1C
#define BIT_MODE_4					0x28
#define BIT_MODE_8					0x38
#define DDRAM_CONSTANT				0x80

/*functions*/
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_clearScreen(void);
void LCD_shiftEntireLeft(void);
void LCD_shiftEntireRight(void);
void LCD_goToRowColumn(uint8 row,uint8 column);
void LCD_displayChar(uint8 character);
void LCD_displayString(char *str);
void LCD_displayInt(sint32 number);

#endif /* LCD_DRIVER_H_ */