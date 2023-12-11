/*
 * calculator.h
 *
 *  Created on: 23 Aug 2023
 *      Author: Amr Al-Kayal
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_


#include "Tiva_DIO.h"
#include "LCD_Driver.h"
#include "keyPad_Driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Corrected include
#include <ctype.h>


// Define constants for clarity



#define MAX_STACK_SIZE 16
 extern char key;
 extern short Index_Position;
 extern short Index_Row;
 extern char num_temp[16];  // Array of integers
 extern char str_arr[17];  // Buffer String
 extern char op_arr[MAX_STACK_SIZE];  // Operation String
 extern int num_stack[MAX_STACK_SIZE];  // Number Stack
 extern int opStackTop;  // Operator Stack Top




char isOP(char ptr);
int OP_priority(char ptr);
void pushOperator(char op);
char popOperator();
void pushNumber(int num);
int popNumber();
void calculateAndDisplayResult();
void GPIOC_Handler(void);

void calc_Initpins(void);




#endif /* CALCULATOR_H_ */
