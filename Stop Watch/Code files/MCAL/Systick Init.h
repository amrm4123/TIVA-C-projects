/*
 * Systick Init.h
 *
 *  Created on: 24 Aug 2023
 *      Author: Amr Al-Kayal
 */

#ifndef SYSTICK_INIT_H_
#define SYSTICK_INIT_H_

#include"tm4c123gh6pm.h"
#include "DIO_INTRFACE.h"
#include "stdTypes.h"
void Systick_Init(void);
void Systick_Init_intruppt(void);
void Systick_DisEN(void);
void SYstick_continue(void);
void stop_Systick_Timer(void);


#endif /* SYSTICK_INIT_H_ */
