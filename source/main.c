/*	Author: christopherluu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Custom Project
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#include "scheduler.h"
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES {START, INIT, ON, OFF, RELEASE} state;
unsigned char input;

void ButtonTick(){
    switch(state){
        //input = (~PINB & 0x03);
        case START:
            state = INIT;
            break;
        case INIT:
            if((~PINB & 0x03) == 1){
                state = ON;
            }
            else if((~PINB & 0x03) == 2){
                state = OFF;
            }
            else{
                state = INIT;
            }
            break;
        case ON:
            break;
        case OFF:
            break;
        case RELEASE:
            if((~PINB & 0x03) == 0){
                state = INIT;
            }
            break;
        default:
            state = START;
            break;
    }

    switch(state){
        case START:
            break;
        case INIT:
            break;
        case ON:
            OCR1A = 300;
            state = RELEASE;
            break;
        case OFF:
            OCR1A = 175;
            state = RELEASE;
            break;
        case RELEASE:
            break;
        default:
            state = START;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0x00; PORTB = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    TCNT1 = 0;
    ICR1 = 2499;
    /* Insert your solution below */
    //unsigned short angle;
    TCCR1A = (1<<WGM11) | (1<<COM1A1);
    TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS10) | (1<<CS11);
    state = START;
    while (1) {
        ButtonTick();
    }
    return 1;
}
