#include<avr/io.h>
#include<avr/interrupt.h>

volatile unsigned char tot_overflow;

void timer0_init(){
    TCCR0A = 0x00;
    TCCR0B = 0x04; // 256 prescaler
    TCNT0 = 0; // initial value
    TIMSK0 |= (1<<0); // enable overflow interrupt
    sei(); // enable global interrupt
    tot_overflow = 0; // initialize overflow counter variable
}

// Timer0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect){
    // keep a track of number of overflows
    tot_overflow++;
}

int main(){
    DDRC |= (1<<0); // set PC0 as output
    timer0_init(); // initialize timer0
    while(1){
        if(tot_overflow>=24){
            if(TCNT0 >= 106){
                PORTC ^= (1<<0); // toggle PC0
                TCNT0 = 0; // reset counter
                tot_overflow = 0; // reset overflow counter
            }
        }
    }
}