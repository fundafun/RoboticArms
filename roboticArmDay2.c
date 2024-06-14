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

// PIN DEFINITIONS
#define SELECT_A PORTBbits.RB0
#define SELECT_B PORTBbits.RB1
#define SELECT_C PORTBbits.RB2

// PIN DEFINITION DEFINITIONS
//#define SELECT_A = solvalA
//#define SELECT_B = solvalB
//#define SELECT_C = solvalC

// SOLENOIDS DEFINITIONS
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

// SOLENOID DIRECTIONS
#define SOLENOID_UP 0x01
#define SOLENOID_DOWN 0x02
#define SOLENOID_FORWARD 0x04
#define SOLENOID_BACKWARD 0x08
#define SOLENOID_LEFT 0x16
#define SOLENOID_RIGHT 0x32

// SOLENOID PIN DEFINITIONS
#define SOLENOID_UP_PIN PORTBbits.RB3
#define SOLENOID_DOWN_PIN PORTBbits.RB4
#define SOLENOID_FORWARD_PIN PORTBbits.RB5
#define SOLENOID_BACKWARD_PIN PORTBbits.RB6
#define SOLENOID_LEFT_PIN PORTBbits.RB7
#define SOLENOID_RIGHT_PIN PORTBAits.RA0

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD
} Direction;

char* get_direction_string(Direction dir) {
    switch (dir) {
        case UP: return "up";
        case DOWN: return "down";
        case LEFT: return "left";
        case RIGHT: return "right";
        case FORWARD: return "forward";
        case BACKWARD: return "backward";
        default: return "unknown";
    }
}

Direction determine_direction_digit(unsigned int digit) {
    switch (digit) {
        case 1: return UP;
        case 2: return DOWN;
        case 3: return LEFT;
        case 4: return RIGHT;
        case 5: return FORWARD;
        case 6: return BACKWARD;
        default: return UP;
    }
}

void move_solenoid(Direction dir) {
    switch (dir) {
        case UP: move_up(); break;
        case DOWN: move_down(); break;
        case LEFT: move_left(); break;
        case RIGHT: move_right(); break;
        case FORWARD: move_forward(); break;
        case BACKWARD: move_backward(); break;
        default: break;
    }
}


// CONVERT USER INPUT TO SOLENOID MOVEMENT
void move_solenoid(unsigned int input) {
    // Convert input to binary
    unsigned int bin_input = input;


// Extract each digit of the binary input
    unsigned int digit1 = (bin_input >> 3) & 0x01;
    unsigned int digit2 = (bin_input >> 2) & 0x01;
    unsigned int digit3 = (bin_input >> 1) & 0x01;
    unsigned int digit4 = bin_input & 0x01;

 // Move solenoid based on digit values
    move_solenoid(determine_direction_digit(digit1));
    move_solenoid(determine_direction_digit(digit2));
    move_solenoid(determine_direction_digit(digit3));
    move_solenoid(determine_direction_digit(digit4));
}

// FUNCTION PROTOTYPES
void select_solenoid(unsigned char solenoid) {
    SELECT_A = (solenoid & 0x01) >> 0;
    SELECT_B = (solenoid & 0x02) >> 1;
    SELECT_C = (solenoid & 0x04) >> 2;
}

void move_solenoid(Direction Dir);
void move_up(void) {
    select_solenoid(SOLENOID_UP);
    __delay_ms(500); }
void move_down(void) {
    select_solenoid(SOLENOID_DOWN);
    __delay_ms(500);}
void move_left(void) {
    select_solenoid(SOLENOID_LEFT);
    __delay_ms(500); }
void move_right(void) {
    select_solenoid(SOLENOID_RIGHT);
    __delay_ms(500); }
void move_forward(void) {
    select_solenoid(SOLENOID_FORWARD);
    __delay_ms(500); }
void move_backward(void) {
    select_solenoid(SOLENOID_BACKWARD);
    __delay_ms(500); }
char* get_direction_string(Direction dir);
Direction determine_direction_digit(unsigned int digit);

void main(void) {
    // SETTING UP SOLENOID TESTING
    
    OSCCON = 0x70; // Set up internal oscillator for 8MHz operation (CAN CHANGE LATER FOR OPTIMIZATION)
    ANSEL = 0x00; // Configure all I/O pins as digital
    ANSELH = 0x00;
    TRISB = 0x00; // Set all PORTB pins as outputs
    TRISA = 0x00; //reassigned to valid pin number

   //SEQUENTIALLY
    while(1) {
        for (unsigned char i = 0; i < 8; i++) {
            select_solenoid(i);
            __delay_ms(1500); // Delay for 1.5 seconds
        }
    }

    // Movement sequence
    move_up();
    __delay_ms(1500);
    move_down();
     __delay_ms(1500);
    move_forward();
     __delay_ms(1500);
    move_backward();
     __delay_ms(1500);
    move_left();
     __delay_ms(1500);
    move_right();
     __delay_ms(1500);

        
  
    TRISB = 0x00;

    // Get 4-digit user input
    unsigned int input;
    printf("Enter a 4-digit number: ");
    scanf("%d", &input);

    // Convert user input to solenoid movement
    move_solenoid(input);

    return 0;
}