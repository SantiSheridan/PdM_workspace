/*
 * api_debounce.c
 *
 *  Created on: Sep 23, 2025
 *      Author: santiago-sheridan
 */

#include "api_debounce.h"
#if defined(PUNTO) && (PUNTO == 2)
#include "api_delay.h"
#include "stm32f4xx_hal.h"

static debounceState_t debounce_state = BUTTON_UP;
static delay_t debounce_delay;
static bool key_pressed = false;

static bool get_button(void) {
	/* false -> apretado */
	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	if (state == GPIO_PIN_SET){
		return BUTTON_RELEASED;
	}
	return BUTTON_PRESSED;
}

void debounceFSM_init(void)
{
	/* Inicializamos delay antirebote y maquina de estados */
	delayInit(&debounce_delay, DEBOUNCE_DELAY_MS);
	debounce_state = BUTTON_UP;
}

void debounceFSM_update(void)
{	
	/* Actualizacion de la maquina de estados con retardo DEBOUNCE_DELAY_MS */

	if (!delayRead(&debounce_delay)) return;

	switch (debounce_state)
	{
		case BUTTON_UP:
			if (get_button() == BUTTON_PRESSED)
			{
				debounce_state = BUTTON_FALLING;
			}
			break;
		case BUTTON_FALLING:
			if (get_button() == BUTTON_PRESSED)
			{
				debounce_state = BUTTON_DOWN;
				key_pressed = true;
			} else {
				debounce_state = BUTTON_UP;
			}
			break;
		case BUTTON_DOWN:
			if (get_button() == BUTTON_RELEASED)
			{
				debounce_state = BUTTON_RISING;
			}
			break;
		case BUTTON_RISING:
			if (get_button() == BUTTON_RELEASED)
			{
				debounce_state = BUTTON_UP;
			} else {
				debounce_state = BUTTON_DOWN;
			}
			break;
		default:
			break;
	}
}

bool readKey(void)
{
	/* retornamos true si el boton fue presionado y reiniciamos valor a false */
	if (key_pressed)
	{
		key_pressed = false;
		return true;
	}
	return false;
}
#endif // PUNTO == 2
