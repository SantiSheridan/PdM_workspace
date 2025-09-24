/*
 * api_debounce.h
 *
 *  Created on: Sep 23, 2025
 *      Author: santiago-sheridan
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "main.h"

#if defined(PUNTO) && (PUNTO == 2)
#include <stdint.h>
#include <stdbool.h>

#define INCLUDE_API_DEBOUNCE
#define DEBOUNCE_DELAY_MS 50
#define BUTTON_PRESSED  false
#define BUTTON_RELEASED true

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
}debounceState_t;

void debounceFSM_init(void);
void debounceFSM_update(void);

bool readKey(void);

#endif // PUNTO == 2
#endif /* API_INC_API_DEBOUNCE_H_ */
