/*	Author: lab
 *  Partner(s) Name: Hulbert Zeng
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum AS_States { AS_SMStart, AS_Init, AS_Wait, AS_Increment, AS_Decrement, AS_Reset, AS_Buffer } AS_State;

void TickFct() {
    switch(AS_State) {
        case AS_SMStart:
            AS_State = AS_Init;
            break;
        case AS_Init:
            AS_State = AS_Wait;
            break;
        case AS_Wait:
            if((PINA & 0x03) == 0x01) {
                AS_State = AS_Increment;
            } else if((PINA & 0x03) == 0x02) {
                AS_State = AS_Decrement;
            } else if((PINA & 0x03) == 0x03) {
                AS_State = AS_Reset;
            } else {
                AS_State = AS_Wait;
            }
            break;
        case AS_Increment:
            AS_State = AS_Buffer;
            break;
        case AS_Decrement:
            AS_State = AS_Buffer;
            break;
        case AS_Reset:
            AS_State = AS_Wait;
            break;
        case AS_Buffer:
            if((PINA & 0x03) == 0x03) {
                AS_State = AS_Reset;
            } else if(((PINA & 0x03) == 0x01) || ((PINA & 0x03) == 0x02)) {
                AS_State = AS_Buffer;
            } else {
                AS_State = AS_Wait;
            }
            break;
        default:
            AS_State = AS_SMStart;
            break;
    }

    switch(AS_State) {
        case AS_SMStart:
            break;
        case AS_Init:
            PORTC = 0x07;
            break;
        case AS_Wait:
            break;
        case AS_Increment:
            if(PINC < 9) {
                PORTC = PINC + 1;
            }
            break;
        case AS_Decrement:
            if(PINC > 0) {
                PORTC = PINC - 1;
            }
            break;
        case AS_Reset:
            PORTC = 0;
            break;
        case AS_Buffer:
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    AS_State = AS_SMStart;
    /* Insert your solution below */
    while (1) {
        TickFct();
    }
    return 1;
}
