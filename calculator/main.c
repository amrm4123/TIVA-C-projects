#include "Tiva_DIO.h"
#include "LCD_Driver.h"
#include "keyPad_Driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Corrected include
#include <ctype.h>
#include"calculator.h"


//#define MAX_STACK_SIZE 16


// main function
int main(void) {
    calc_Initpins();
    LCD_SetCursor(0, 1);
    LCD_WriteString("HELLO...");
    _delay_ms(2000);
    LCD_Clear();
    KeyPad_Init_INT();
    __asm(" CPSIE  I");
    int i = 0;

    while (1) {
        Index_Row++;
        Index_Position++;
        KeyPad_Read_INT();
        if (key != DEFAULT_K) {
            if (key == '=') {
                // Calculate and display the result
                calculateAndDisplayResult();
            } else {
                // Handle other key presses
                LCD_WriteChar(key);
                str_arr[i++] = key;
                _delay_us(50);
            }
            key = DEFAULT_K;
            Index_Position++;
            if (Index_Position > 15 && Index_Row == 0) {
                Index_Row = 1;
                Index_Position = 0;
            }
            if (Index_Position > 15 && Index_Row == 1) {
                LCD_Clear();
                Index_Row = 0;
                Index_Position = 0;
            }
        }
    }
    return 0;
}
