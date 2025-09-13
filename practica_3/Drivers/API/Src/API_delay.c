/*
 * API_delay.c
 *
 *  Created on: Sep 11, 2025
 *      Author: W10-PC
 */
#include "API_delay.h"

void delayInit(delay_t *delay, tick_t duration)
{
	/* Inicializo struct */
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead(delay_t *delay)
{

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
	/* Actualizar struct con nuevo tiempo de delay */
	delay->duration = duration;
}

bool_t delayIsRunning(delay_t *delay)
{
	return delay->running;
}
