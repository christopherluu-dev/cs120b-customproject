#ifndef ULTRASONICSENS_H
#define ULTRASONICSENS_H

#define TRIGGER PA0

unsigned int TimerOverflow = 0;

ISR(TIMER1_OVF_vect){
    TimerOverflow++;
}



#endif