/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "stm32f4xx_hal.h"

#include <stdio.h>
#include "Game_Logic.h"
#include "Button_Driver.h"


#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
void LCD_Visual_Demo(void);

#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1)
void start(void);
void game(void);
void win(int8_t winner);

uint8_t rngAIMove();
uint8_t optimalMove();
uint8_t player_turn();

#endif /* INC_APPLICATIONCODE_H_ */
