/*	Author: lab
 *  Partner(s) Name: Hulbert Zeng
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SW_States { SW_SMStart, SW_On1, SW_Off1, SW_On2, SW_Off2 } SW_State;

void TickFct() {
    switch(SW_State) {
        case SW_SMStart:
            SW_State = SW_On1;
            break;
        case SW_On1:
            if((PINA & 0x01) == 0) {
                SW_State = SW_On2;
            } else if((PINA & 0x01) == 1) {
                SW_State = SW_On1;
            } else {
                SW_State = SW_On1;
            }
            break;
        case SW_Off1:
            if((PINA & 0x01) == 0) {
                SW_State = SW_Off2;
            } else if((PINA & 0x01) == 1) {
                SW_State = SW_Off1;
            } else {
                SW_State = SW_Off1;
            }
            break;
        case SW_On2:
            if((PINA & 0x01) == 1) {
                SW_State = SW_Off1;
            } else if((PINA & 0x01) == 0) {
                SW_State = SW_On2;
            } else {
                SW_State = SW_On2;
            }
            break;
        case SW_Off2:
            if((PINA & 0x01) == 1) {
                SW_State = SW_On1;
            } else if((PINA & 0x01) == 0) {
                SW_State = SW_Off2;
            } else {
                SW_State = SW_Off2;
            }
            break;
        default:
            SW_State = SW_SMStart;
            break;
    }

    switch(SW_State) {
        case SW_SMStart:
            PORTB = 0x01;
            break;
        case SW_On1:
            PORTB = 0x01;
            break;
        case SW_Off1:
            PORTB = 0x02;
            break;
        case SW_On2:
            PORTB = 0x01;
            break;
        case SW_Off2:
            PORTB = 0x02;
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    SW_State = SW_SMStart;
    /* Insert your solution below */
    while (1) {
        TickFct();
    }
    return 1;
}
