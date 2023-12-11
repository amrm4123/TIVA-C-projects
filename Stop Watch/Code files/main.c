#include"tm4c123gh6pm.h"
#include "DIO_INTRFACE.h"
#include "LCD.h"
#include"Utils.h"
#include"stdTypes.h"
#include"delay.h"
#include "Systick Init.h"

#define LED_RED (1<<1U)
#define LED_BLUE (1<<2U)
#define LED_GREEN (1<<3U)
#define SW1 0
#define SW2 4

volatile char sec=0;
volatile char H=0;
volatile char M=0;
volatile char Running = 1;
void Initpins_project(void)
{

    DIO_Initpin(PINA5, OUTPUT);
    DIO_Initpin(PINA6, OUTPUT);
    DIO_Initpin(PINA7, OUTPUT);
    DIO_Initpin(PINB6, OUTPUT);
    DIO_Initpin(PINA4, OUTPUT);
    DIO_Initpin(PINA3, OUTPUT);
    DIO_Initpin(PINA2, OUTPUT);
    LCD_Init();
}


void LCD_Display()
{
    LCD_GoTo(0,0);
    LCD_WriteNumber_2D(sec);
    LCD_GoTo(0,2);
    LCD_WriteChar(':');
    LCD_GoTo(0,3);
    LCD_WriteNumber_2D(M);
    LCD_GoTo(0,5);
    LCD_WriteChar(':');
    LCD_GoTo(0,6);
    LCD_WriteNumber_2D(H);
}

void SysTick_Handler()
{
            sec++;
            if(sec==60)
            {
                sec=0;
                M++;
            }
            if(M==60)
            {
                M=0;
                H++;
            }


}

void hamada(void){
    if(READ_BIT(GPIO_PORTF_RIS_R,0)){// Resume the stop watch
            DIO_WritePin(PINF2,LOW);
            DIO_WritePin(PINF3,HIGH);
            DIO_WritePin(PINF1,LOW);
                Running = 1;
                SYstick_continue();
            SET_BIT(GPIO_PORTF_ICR_R,0);

            }
            else if(READ_BIT(GPIO_PORTF_RIS_R,4)) // Pause the stop watch
            {// check if interrupt causes by SW2
                Running = 0;
                Systick_DisEN();
                DIO_WritePin(PINF2,LOW);
                DIO_WritePin(PINF1,HIGH);
                DIO_WritePin(PINF3,LOW);
                SET_BIT(GPIO_PORTF_ICR_R,4);

            }

}
void Interrupt_Init(){

    NVIC_EN0_R |=(1<<30); // enable interrupt in vector table
   GPIO_PORTF_IS_R  &= ~(1<<0) | ~(1<<4); // configure the interrupt for SW1 & SW2 to be EDGE
   GPIO_PORTF_IBE_R &= ~(1<<0) | ~(1<<4); //Interrupt generation is controlled by the GPIO Interrupt Event

   GPIO_PORTF_IEV_R &= ~(1<<0) | ~(1<<4); //SW1 & SW2 pins generate interrupt with the falling edge
   GPIO_PORTF_IM_R  |=  (1<<0) | (1<<4); //The interrupt from the corresponding pin is sent to the interrupt controller.

}
void PORTF_Init(){
    SYSCTL_RCGCGPIO_R |=0x00000020; // Enabling Clock for PORTf
    while((SYSCTL_RCGCGPIO_R & 0x00000020 ) == 0){}; // waiting till the clock is activated
    GPIO_PORTF_LOCK_R = 0x4C4F434B; //
    GPIO_PORTF_CR_R = 0x1F; // Make Portf Configuerable
    GPIO_PORTF_DIR_R = 0x0E; // make the three leds outputs
    GPIO_PORTF_PUR_R = 0x11; // PULL UP ENABLED
    GPIO_PORTF_DEN_R = 0x1F; // Enable the Switches and the leds in PORTF

}


void Interrupt_Init(void);


int main(void)
{
    Initpins_project();
    PORTF_Init();
    Interrupt_Init();




    DIO_WritePin(PINF2,HIGH);
    LCD_WriteString("Amr AL-Kayal");
    LCD_GoTo(1, 0);
    LCD_WriteString("MUhammed Sayed");
    _delay_ms(800);
    LCD_Clear();
    LCD_WriteString("***stop watch***");
    _delay_ms(800);
    LCD_Clear();
    Systick_Init_intruppt();
    while(1)

    {
        if(Running){
        LCD_Display();
        }
        else{

            }

    }
    return 0;
}

