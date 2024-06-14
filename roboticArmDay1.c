#include <xc.h>
#include <pic16f886.h>
#include <stdio.h>
#include <stdlib.h>
#include "digits.h"

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF              // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF             // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON              // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF                // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF               // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON              // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON               // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON              // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF               // Low Voltage Programming Enable bit (RB3/PGM pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V          // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF               // Flash Program Memory Self Write Enable bits (Write protection off)

// CONFIG3
#define SELECT_A PORTBbits.RB0
#define SELECT_B PORTBbits.RB1
#define SELECT_C PORTBbits.RB2

// CONFIG4
#define SOLENOID_1 0x00
#define SOLENOID_2 0x01
#define SOLENOID_3 0x02
#define SOLENOID_4 0x03
#define SOLENOID_5 0x04
#define SOLENOID_6 0x05
#define SOLENOID_7 0x06
#define SOLENOID_8 0x07
#define SOLENOID_9 0x08
#define SOLENOID_10 0x09
#define SOLENOID_11 0x10
#define SOLENOID_12 0x11
#define SOLENOID_13 0x12
#define SOLENOID_14 0x13
#define SOLENOID_15 0x14

// MAIN CODE

void select_solenoid(unsigned char solenoid) {
    SELECT_A = (solenoid & 0x01) >> 0;
    SELECT_B = (solenoid & 0x02) >> 1;
    SELECT_C = (solenoid & 0x04) >> 2;
}

// 3 input signal, 3-8 decoder
    #define SELECT_A = solvalA
    #define SELECT_B = solvalB
    #define SELECT_C = solvalC



// CODE FOR TESTING SOLENOIDS
void main(void) {
    OSCCON = 0x70; // Set up internal oscillator for 8MHz operation (CAN CHANGE LATER FOR OPTIMIZATION)
    ANSEL = 0x00; // Configure all I/O pins as digital
    ANSELH = 0x00;
    TRISB = 0x00; // Set all PORTB pins as outputs

// move sequentially with input
// 3 input signals (A,B,C) 3-8 decoder, max: 8 solenoid, 5V-> microcontroller
// 0011, 0100, 0101, 0110, 0111, 1000
// decoder: 1x3:8 

    while(1) {
        for (unsigned char i = 0; i < 8; i++) {
            select_solenoid(i);
            __delay_ms(1500); // Delay for 1.5 seconds
        }
    }

// Define movement functions

// Define solenoid constants
#define SOLENOID_UP 0x01
#define SOLENOID_DOWN 0x02
#define SOLENOID_FORWARD 0x04
#define SOLENOID_BACKWARD 0x08
#define SOLENOID_LEFT 0x16
#define SOLENOID_RIGHT 0x32

 while (1) {
        // Implement movement sequence
        move_up();
        move_down();
        move_forward();
        move_backward();
        move_left();
        move_right();
    }

    return 0;

void select_solenoid(unsigned char solenoid) {
    SELECT_A = (solenoid & 0x01) >> 0;
    SELECT_B = (solenoid & 0x02) >> 1;
    SELECT_C = (solenoid & 0x04) >> 2;
}
// Function to move solenoid
void move_solenoid(enum direction dir) {
    printf("Moving solenoid in %s direction\n", get_direction_string(dir));
}

// function to get the directions string
char* get_direction_string(enum direction dir) {
    switch (dir) }
        case UP: return

int main(void) {
    // Initialize solenoids
    TRISB = 0x00; // Set all PORTB pins as outputs

void move_up(void) {
    // Set solenoids to move up
    select_solenoid(SOLENOID_UP);
    __delay_ms(500); // Hold for 500ms
}

void move_down(void) {
    // Set solenoids to move down
    select_solenoid(SOLENOID_DOWN);
    __delay_ms(500); // Hold for 500ms
}

void move_left(void) {
    // set solenoids to move left
    select_solenoid(SOLENOID_LEFT);
    __delay_ms(500); // Hold for 500ms
}

void move_right(void) {
    // set solenoids to move right
    select_solenoid(SOLENOID_RIGHT);
    __delay_ms(500); // Hold for 500ms
}

void move_forward(void) {
    // Set solenoids to move forward
    select_solenoid(SOLENOID_FORWARD);
    __delay_ms(500); // Hold for 500ms
}

void move_backward(void) {
    // Set solenoids to move backward
    select_solenoid(SOLENOID_BACKWARD);
    __delay_ms(500); // Hold for 500ms
}

   
}
//Define solenoid control pins
#define SOLENOID_UP    PORTBbits.RB3
#define SOLENOID_DOWN  PORTBbits.RB4
#define SOLENOID_FORWARD PORTBbits.RB5
#define SOLENOID_BACKWARD PORTBbits.RB6
#define SOLENOID_LEFT PORTBbits.RB7
#define SOLENOID_RIGHT PORTBbits.RB8

// Function to convert user input to solenoid movement
void move_solenoid(unsigned int input) {
    // Convert input to binary
    unsigned int bin_input = input;

// Extract each digit of the binary input
    unsigned int digit1 = (bin_input >> 3) & 0x01;
    unsigned int digit2 = (bin_input >> 2) & 0x01;
    unsigned int digit3 = (bin_input >> 1) & 0x01;
    unsigned int digit4 = bin_input & 0x01;
    
    //sequential order
    
    typedef enum {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FORWARD,
        BACKWARD
    } Direction;
    

    char* get_direction_string(enum direction dir) {
    switch (dir) {
        case UP: return "up";
        case DOWN: return "down";
        case LEFT: return "left";
        case RIGHT: return "right";
        case FORWARD: return "forward";
        case BACKWARD: return "backward";
        default: return "unknown";
    }
    int main() {
        // Assume digit1, digit2, digit3, and digit4 are defined and set accordingly

    if (digit1) {
        enum direction dir = determine_direction(); // implement this function
        // Delay for 500ms
        usleep(500000); // 500,000 microseconds
        move_solenoid(dir);
    }

    if (digit2) {
       enum direction dir2 = determine_direction_digit2(); // implement this function
        // Delay for 500ms
        usleep(500000); //500,000 microseconds
        move_solenoid(dir2);
    }

    if (digit3) {
        enum direction dir3 = determine_direction_digit3(); // implement this function
        // Delay for 500ms
        usleep(500000); //500,000 microseconds
        move_solenoid(dir3);
    }

    if (digit4) {
        enum direction dir4 = determine_direction_digit4(); // implement this function
        // Delay for 500ms
        usleep(500000); //500,000 microseconds
        move_solenoid(dir4);
    }
    return 0;
}
}

int main(void) {
    // Initialize solenoid control pins as outputs
    TRISB = 0x00;

    // Get 4-digit user input
    unsigned int input;
    printf("Enter a 4-digit number: ");
    scanf("%d", &input);

    // Convert user input to solenoid movement
    move_solenoid(input);

    return 0;
}