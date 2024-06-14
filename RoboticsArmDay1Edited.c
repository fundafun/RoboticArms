/*
 * File:   main.c
 * Author: sarangp
 *
 * Created on 12 June, 2024, 6:27 PM
 */


//

#include <xc.h>
#include <pic16f886.h>
#include <stdio.h>
#include <stdlib.h>

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


unsigned int Delay1=0, Delay2=0;

// MAIN CODE

void select_solenoid(unsigned char solenoid) {
    SELECT_A = (solenoid & 0x01) >> 0;
    SELECT_B = (solenoid & 0x02) >> 1;
    SELECT_C = (solenoid & 0x04) >> 2;
// 3 input signal, 3-8 decoder
}

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
            //__delay_ms(1500); // Delay for 1.5 seconds
            for(Delay1=0;Delay1<100; Delay1++){
                for(Delay2=0;Delay2<100; Delay2++);
            }
        }
    }
}