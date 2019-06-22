/*
 * LCD_Driver.c
 *
 * Created: 24/04/2019 11:31:11 م
 *  Author: Azazi
 */ 

#include "LCD_Driver.h"
#include <stdlib.h>
#include <util/delay.h>

void LCD_init(void){
	LCD_CONTROL_REG_DIRECTION |= (1<<EN) | (1<<RS) | (1<<RW);
	#if EIGHT_DATABIT_MODE
		LCD_DATA_REG_DIRECTION = 0xFF;
		LCD_sendCommand(BIT_MODE_8);
	#else
		#if UPPER_DATA_PORT
			LCD_DATA_REG_DIRECTION |= 0xF0;
		#else
			LCD_DATA_REG_DIRECTION |= 0x0F;
		#endif
		LCD_sendCommand(0x33);	//initialization for 4-bit operation
		LCD_sendCommand(0x32);	//initialization for 4-bit operation
		LCD_sendCommand(BIT_MODE_4);
	#endif
	LCD_sendCommand(RETURN_HOME);
	LCD_sendCommand(CLEAR_DISPLAY);
	LCD_sendCommand(DISPLAY_ON_CURSOR_ON);
}

void LCD_sendCommand(uint8 command){
	CLEAR_BIT(LCD_CONTROL_REG_WRITE,RS);
	CLEAR_BIT(LCD_CONTROL_REG_WRITE,RW);
	_delay_ms(1);
	SET_BIT(LCD_CONTROL_REG_WRITE,EN);
	_delay_ms(1);
	#if EIGHT_DATABIT_MODE
		LCD_DATA_REG_WRITE=command;
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_REG_WRITE,EN);
		_delay_ms(1); 
	#else
		#if UPPER_DATA_PORT
			/* clear previous command */
			LCD_DATA_REG_WRITE &= 0x0F;
			LCD_DATA_REG_WRITE |= (command & 0xF0);
		#else
			LCD_DATA_REG_WRITE &= 0xF0;
			LCD_DATA_REG_WRITE |= (command >> 4);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_REG_WRITE,EN);
		_delay_ms(1);
		SET_BIT(LCD_CONTROL_REG_WRITE,EN);
		_delay_ms(1);
		#if UPPER_DATA_PORT
			LCD_DATA_REG_WRITE &= 0x0F;
			LCD_DATA_REG_WRITE |= ((command << 4) & 0xF0);
		#else
			LCD_DATA_REG_WRITE &= 0xF0;
			LCD_DATA_REG_WRITE |= (command & 0x0F);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_REG_WRITE,EN);
		_delay_ms(1);
	#endif
}
void LCD_displayChar(uint8 character){
	SET_BIT(LCD_CONTROL_REG_WRITE,RS);
	CLEAR_BIT(LCD_CONTROL_REG_WRITE,RW);
	SET_BIT(LCD_CONTROL_REG_WRITE,EN);
	_delay_ms(1);
	#if EIGHT_DATABIT_MODE
		LCD_DATA_REG_WRITE=character;
	#else
		#if UPPER_DATA_PORT
			/* clear the Previous Data */
			LCD_DATA_REG_WRITE &= 0x0F;
			/* Send MSB (4-bits )*/
			LCD_DATA_REG_WRITE |= (character & 0xF0);
	
		#else /* Lower Port */
			/* clear the Previous Data */
			LCD_DATA_REG_WRITE &= 0xF0;
			/* Send MSB (4-bits )*/
			LCD_DATA_REG_WRITE |= ((character >> 4) & 0x0F); // try not using & 0x0F
		#endif
		_delay_ms(1);
		/* disable LCD E=0 */
		CLEAR_BIT(LCD_CONTROL_REG_WRITE,EN);
		/* Data Hold delay Th = 10ns */
		_delay_ms(1);
		/* Enable LCD E=1 */
		SET_BIT(LCD_CONTROL_REG_WRITE,EN);
		#if UPPER_DATA_PORT
			/* clear the Previous Data */
			LCD_DATA_REG_WRITE &=0x0F;
			LCD_DATA_REG_WRITE |= ((character <<4) & 0xF0);
			/* delay for processing PW min 450ns */
			_delay_ms(1);
		#else	/* Lower Port */
			/* clear the Previous Data */
			LCD_DATA_REG_WRITE &=0xF0;
			LCD_DATA_REG_WRITE |= ((character) & 0x0F);
		#endif
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CONTROL_REG_WRITE,EN);
	_delay_ms(1);
}

void LCD_displayString(char *str){
	while(*str != '\0'){
		LCD_displayChar(*str);
		str++;
	}
}

void LCD_displayInt(sint32 number){
	char value [16];
	itoa(number,value,10);
	LCD_displayString(value);	
}

void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_DISPLAY);
}

void LCD_shiftEntireLeft(void){
	LCD_sendCommand(SHIFT_ENTIRE_DISPLAY_LEFT);
}

void LCD_shiftEntireRight(void){
	LCD_sendCommand(SHIFT_ENTIRE_DISPLAY_RIGHT);
}


void LCD_goToRowColumn(uint8 row,uint8 column){
	uint8 address = 0;
	switch (row){
		case 0:
			address=column|0x00;
			break;
		case 1:
			address=column|0x40;
			break;
	}
	LCD_sendCommand(DDRAM_CONSTANT|address);
}