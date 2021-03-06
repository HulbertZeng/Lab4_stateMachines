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

enum DL_States { DL_SMStart, DL_S0, DL_S1 } DL_State;

bool verifyPass(p) {
    for(unsigned int i < 0; i < p.size(); ++i) {
        if(p.at(i) != PINA & (0x01 << i)) {
            return 0;
        }
    }

    return 1;
}

void TickFct() {
    unsigned char x = PINA & 0x01;
    unsigned char y = PINA & 0x02;
    unsigned char pound = PINA & 0x04;
    unsigned char inside = PINA & 0x80;
    unsigned char password[] = {pound, x, y, x};

    switch(DL_State) {
        case DL_SMStart:
            DL_State = DL_S0;
            break;
        case DL_S0:
            if(inside || verifyPass(password)) {
                DL_State = DL_S1;
            } else {
                DL_State = DL_S0;
            }
            break;
        case DL_S1:
            if(verifyPass(password)) {
                DL_State = DL_S0;
            } else {
                DL_State = DL_S1;
            }
            break;
        default:
            DL_State = DL_SMStart;
            break;
    }

    switch(DL_State) {
        case DL_SMStart:
            break;
        case DL_S0:
            PORTB = 0x00;
            break;
        case DL_S1:
            PORTB = 0x01;
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DL_State = DL_SMStart;
    /* Insert your solution below */
    while (1) {
        TickFct();
    }
    return 1;
}
