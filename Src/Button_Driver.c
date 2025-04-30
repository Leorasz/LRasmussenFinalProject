/*
 * Button_Driver.c
 *
 *  Created on: Apr 20, 2025
 *      Author: leo
 */
#include "Button_Driver.h"

void Button_Init() {
	GPIO_InitTypeDef button;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	button.Pin = GPIO_PIN_0;
	button.Mode = GPIO_MODE_IT_RISING;
	button.Speed = GPIO_SPEED_FREQ_MEDIUM;
	button.Pull = GPIO_NOPULL;
	button.Alternate = 0;

	HAL_GPIO_Init(GPIOA, &button);
	NVIC_EnableIRQ(EXTI0_IRQn);

}
