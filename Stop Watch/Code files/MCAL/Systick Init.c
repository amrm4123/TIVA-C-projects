



#include "Systick Init.h"



void Systick_Init(void) {
    NVIC_ST_RELOAD_R = 16000000 - 1; // Reload =  (require delay / clock tim_period) - 1
    NVIC_ST_CURRENT_R = 0; // to clear any current value
    NVIC_ST_CTRL_R |= (1 << 0); // Enable the Timer
    NVIC_ST_CTRL_R |= (1 << 2); // System clock
}



void Systick_Init_intruppt(void) {
    NVIC_ST_RELOAD_R = 16000000 - 1; // Reload =  (require delay / clock tim_period) - 1
    NVIC_ST_CURRENT_R = 0; // to clear any current value
    NVIC_ST_CTRL_R |= (1 << 0); // Enable the Timer
    NVIC_ST_CTRL_R |= (1 << 1); // Enable the INT
    NVIC_ST_CTRL_R |= (1 << 2); // System clock
}


void Systick_DisEN(void)
{
    NVIC_ST_CTRL_R &=~(1 << 0); // Disable the Timer
//    NVIC_ST_CTRL_R &=~(1 << 1); // Disable the INT
}


void stop_Systick_Timer(void)
{
    Systick_DisEN();
}

void SYstick_continue(void)
{
    NVIC_ST_CTRL_R |= (1 << 0); // Enable the Timer
//    NVIC_ST_CTRL_R |= (1 << 1); // Disable the INT


}




