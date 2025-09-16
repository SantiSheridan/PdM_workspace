/*
 * API_delay.c
 *
 *  Created on: Sep 11, 2025
 *      Author: W10-PC
 */
#include "api_delay.h"

void delayInit(delay_t *delay, tick_t duration)
{
	if (delay == NULL) return;

	/* Inicializo struct */
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead(delay_t *delay)
{
	if (delay == NULL) return false;

	tick_t curr_time = HAL_GetTick();

	/* Si no hay duracion de delay, dar por terminado*/
	if (delay->duration == 0) return true;

	/* Si esta corriendo */
	if (delay->running){
		/* Comprobar si el tiempo se cumplio */
		if ((curr_time - delay->startTime) >= delay->duration) {
			delay->running = false;
			return true;
		}
		/* El tiempo no se cumplio */
		return false;
	/* Si no esta corriendo el tiempo, empezarlo */
	} else {
		delay->startTime = curr_time;
		delay->running = true;
		return false;
	}

}

void delayWrite(delay_t *delay, tick_t duration)
{
	if (delay == NULL) return;
	/* Actualizar struct con nuevo tiempo de delay */
	delay->duration = duration;
}

bool_t delayIsRunning(delay_t *delay)
{
	if (delay == NULL) return;
	return delay->running;
}
