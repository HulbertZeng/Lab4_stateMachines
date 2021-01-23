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

enum SW_States { SW_SMStart, SW_On, SW_Off } SW_State;

void TickFct() {
    switch(SW_State) {
        case SW_SMStart:
            SW_State = SW_On;
            break;
        case SW_On:
            if((PINA & 0x01) == 1) {
                SW_State = SW_Off;
            } else {
                SW_State = SW_On;
            }
            break;
        case SW_Off:
            if((PINA & 0x01) == 1) {
                SW_State = SW_On;
            } else {
                SW_State = SW_Off;
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
        case SW_On:
            PORTB = 0x01;
            break;
        case SW_Off:
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
