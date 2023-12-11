/*
 * calculator.c
 *
 *
 */


#include "calculator.h"
char key = DEFAULT_K;
short Index_Position = 0;
short Index_Row = 0;
char num_temp[16] = {0};  // Array of integers
char str_arr[17] = {'\0'};  // Buffer String
char op_arr[MAX_STACK_SIZE] = {'\0'};  // Operation String
int num_stack[MAX_STACK_SIZE] = {0};  // Number Stack
int opStackTop = -1;  // Operator Stack Top



void calc_Initpins(void)
{
    PORT_Init(PORTA);
    PORT_Init(PORTB);
    PORT_Init(PORTE);
    PORT_Init(PORTC);
    DIO_InitPin(RS, OUTPUT);
    DIO_InitPin(RW, OUTPUT);
    DIO_InitPin(EN, OUTPUT);
    DIO_InitPin(D7, OUTPUT);
    DIO_InitPin(D6, OUTPUT);
    DIO_InitPin(D5, OUTPUT);
    DIO_InitPin(D4, OUTPUT);
    LCD_Init();
}








// Function to check if a character is an operator
char isOP(char ptr) {
    return (ptr == '+' || ptr == '-' || ptr == '*' || ptr == '/');
}

// Function to get the priority of an operator
int OP_priority(char ptr) {
    if (ptr == '*' || ptr == '/') {
        return 2;
    } else if (ptr == '+' || ptr == '-') {
        return 1;
    }
    return 0;
}

// Function to push an operator onto the operator stack
void pushOperator(char op) {
    if (opStackTop < MAX_STACK_SIZE - 1) {
        opStackTop++;
        op_arr[opStackTop] = op;
    }
}

// Function to pop an operator from the operator stack
char popOperator() {
    if (opStackTop >= 0) {
        char op = op_arr[opStackTop];
        opStackTop--;
        return op;
    }
    return '\0';  // Return null character for empty stack
}

// Function to push a number onto the number stack
void pushNumber(int num) {
    if (Index_Position < MAX_STACK_SIZE) {
        num_stack[Index_Position] = num;
        Index_Position++;
    }
}

// Function to pop a number from the number stack
int popNumber() {
    if (Index_Position > 0) {
        Index_Position--;
        return num_stack[Index_Position];
    }
    return 0;  // Return 0 for empty stack
}

// Function to perform calculations and display the result
void calculateAndDisplayResult() {
    // Reset stacks and positions
    opStackTop = -1;
    Index_Position = 0;
    int i = 0;

    while (str_arr[i] != '\0') {
        if (isdigit(str_arr[i])) {
            // If the character is a digit, extract the number
            int num = 0;
            while (isdigit(str_arr[i])) {
                num = num * 10 + (str_arr[i] - '0');
                i++;
            }
            pushNumber(num);
        } else if (isOP(str_arr[i])) {
            // If the character is an operator, handle operator precedence
            while (opStackTop >= 0 && OP_priority(op_arr[opStackTop]) >= OP_priority(str_arr[i])) {
                int y = popNumber();
                int x = popNumber();
                char op = popOperator();
                int result;
                switch (op) {
                    case '+':
                        result = x + y;
                        break;
                    case '-':
                        result = x - y;
                        break;
                    case '*':
                        result = x * y;
                        break;
                    case '/':
                        if (y == 0) {
                            // Handle division by zero
                            LCD_GoTo(1, 0);
                            LCD_WriteString("Error: Division by Zero");
                            return;
                        } else {
                            result = x / y;
                        }
                        break;
                }
                pushNumber(result);
            }
            pushOperator(str_arr[i]);
            i++;
        } else {
            i++;  // Ignore other characters
        }
    }

    // Perform remaining calculations
    while (opStackTop >= 0) {
        int y = popNumber();
        int x = popNumber();
        char op = popOperator();
        int result;
        switch (op) {
            case '+':
                result = x + y;
                break;
            case '-':
                result = x - y;
                break;
            case '*':
                result = x * y;
                break;
            case '/':
                if (y == 0) {
                    // Handle division by zero
                    LCD_GoTo(1, 0);
                    LCD_WriteString("Error: Division by Zero");
                    return;
                } else {
                    result = x / y;
                }
                break;
        }
        pushNumber(result);
    }

    // Display the result on the LCD
    int finalResult = popNumber();
//    LCD_Clear();
    LCD_GoTo(1, 0);
    LCD_WriteNumber(finalResult);
}

// GPIOB Interrupt handler
void GPIOC_Handler(void) {
    int r;
    for (r = 0; r < 4; r++) {
        if (!DIO_ReadPin(R_PORT, KP_R1 + r)) {
            while (!READ_BIT(GPIO_PORTC_DATA_R, 4));
            if (GPIO_PORTC_MIS_R & 0x10) /* check if interrupt caused by PC4 */ {
                key = symbol[r][0];
                GPIO_PORTC_ICR_R |= (0x10);
            }
            while (!READ_BIT(GPIO_PORTC_DATA_R, 5));
            if (GPIO_PORTC_MIS_R & 0x20) /* check if interrupt caused by PC5 */ {
                key = symbol[r][1];
                GPIO_PORTC_ICR_R |= (0x20);
            }
            while (!READ_BIT(GPIO_PORTC_DATA_R, 6));
            if (GPIO_PORTC_MIS_R & 0x40) /* check if interrupt caused by PC6 */ {
                key = symbol[r][2];
                GPIO_PORTC_ICR_R |= (0x40);
            }
            while (!READ_BIT(GPIO_PORTC_DATA_R, 7));
            if (GPIO_PORTC_MIS_R & 0x80) /* check if interrupt caused by PC7 */ {
                key = symbol[r][3];
                GPIO_PORTC_ICR_R |= (0x80);
            }
        }
        DIO_WritePin(R_PORT, KP_R1 + r, HIGH);
    }
}




