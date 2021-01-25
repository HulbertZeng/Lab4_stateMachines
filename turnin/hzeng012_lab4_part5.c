/*	Author: lab
 *  Partner(s) Name: Hulbert Zeng
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #5
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
int counter = 0;

unsigned char verifyPass(unsigned char p[], unsigned char i) {
    if((p[i] & PINA) == 1) {
        return 2;
    } else if(PINA == 0x00) {
        return 1;
    }

    return 0;
}

void TickFct() {
    //unsigned char x = PINA & 0x01;
    //unsigned char y = PINA & 0x02;
    //unsigned char pound = PINA & 0x04;
    unsigned char inside = PINA & 0x80;
    unsigned char password[4] = {0x04, 0x01, 0x02, 0x01};
    unsigned char passflag = verifyPass(password, counter);
    if(passflag == 2) {
        ++counter;
    }
    if(passflag != 1) {
        counter = 0;
    }

    switch(DL_State) {
        case DL_SMStart:
            DL_State = DL_S0;
            break;
        case DL_S0:
            if(counter == 4) {
                DL_State = DL_S1;
            } else {
                DL_State = DL_S0;
            }
            break;
        case DL_S1:
            if(inside || counter == 4) {
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
