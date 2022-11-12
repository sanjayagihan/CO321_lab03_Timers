#include <avr/io.h>
#include <util/delay.h>

volatile unsigned char tot1_overflow;

void timer1_init(){
    TCCR1A = 0x00;
    TCCR1B = 0x04; // 256 prescaler
    TCNT1 = 3036; // initial value
    TIMSK1 |= (1<<0); // enable overflow interrupt
    sei(); // enable global interrupt
    tot1_overflow = 0; // initialize overflow counter variable
}

ISR(TIMER1_OVF_vect){
    // keep a track of number of overflows
    tot1_overflow++;
}

#define BLINK_DELAY_MS 1000         //define blink delay

int main(){
    DDRB = 0xFF;                    //initialize data direction register
    DDRC |= (1<<0);                 // set PC0 as output
    short int var = 0;              //initialize variable to count
    short int direction = 1;        //initialize a variable to identify the direction
    timer1_init();                  //initialize timer1
    while(1){
        PORTB = PORTB | (1<<var);   //turn high each pin of port B
        _delay_ms(BLINK_DELAY_MS);  //provide a delay
        PORTB = PORTB &~(1<<var);   //turn low each pin of port B
        if(direction && var<4){     //if direction is 1 and count is less than 4 light bulbs in one direction
            var++;
            if(var>3){
                var = 2,
                direction = 0;
            }
        }else{                      //else light bulbs in other direction
            var--;
            if(var<0){
                direction = 1;
                var = 1;
            }
        }
        if(tot1_overflow>=1){       //if timer1 overflows
            PORTC ^= (1<<0);        //toggle PC0
            TCNT1 = 3036;          //reset counter
            tot1_overflow = 0;      //reset overflow counter
        }
    }
}
