#include<avr/io.h>
#include<avr/interrupt.h>

// 50ms - PC0
// 500ms - PC1
volatile unsigned char tot_overflow;
volatile unsigned char tot1_overflow;

void timer0_init(){
    TCCR0A = 0x00;
    TCCR0B = 0x04; // 256 prescaler
    TCNT0 = 0; // initial value
    TIMSK0 |= (1<<0); // enable overflow interrupt
    sei(); // enable global interrupt
    tot_overflow = 0; // initialize overflow counter variable
}

void timer1_init(){
    TCCR1A = 0x00;
    TCCR1B = 0x04; // 256 prescaler
    TCNT1 = 34286; // initial value
    TIMSK1 |= (1<<0); // enable overflow interrupt
    sei(); // enable global interrupt
    tot1_overflow = 0; // initialize overflow counter variable
}

// Timer0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect){
    // keep a track of number of overflows
    tot_overflow++;
}

// Timer1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_OVF_vect){
    // keep a track of number of overflows
    tot1_overflow++;
}

int main(){
    DDRC |= (1<<0); // set PC0 as output
    DDRC |= (1<<1); // set PC0 as output
    timer0_init(); // initialize timer0
    timer1_init(); // initialize timer1
    while(1){
        if(tot_overflow>=12){
            if(TCNT0 >= 53){
                PORTC ^= (1<<0); // toggle PC0
                TCNT0 = 0; // reset counter
                tot_overflow = 0; // reset overflow counter
            }
        }
        if(tot1_overflow>=1){
            PORTC ^= (1<<1); // toggle PC1
            TCNT1 = 34286; // reset counter
            tot1_overflow = 0; // reset overflow counter
        }
    }
}


