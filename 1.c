/*
Question 02
using just the prescalar this cannot be done. But by using prescalar , counter register and timer overflow interrupt we can do it.

Question 03
XTAL = 16MHz that means 1 cycle = 1/16MHz = 62.5ns
with prescalar 1024 that means 1 cycle = 1/16MHz * 1024 = 64us
largest interval that can be achieved is 64us * 256 = 16.384ms
we can get 16.384ms by using prescalar 1024
(without using conter register and timer overflow interrupt)
*/

#include<avr/io.h>

void delay_timer(){
  TCNT0 = 131;                  // preload timer 0 counter register
  TCCR0A = 0x00;                // set entire TCCR0A register to 0
  TCCR0B = 0x04;                // set prescalar
  while((TIFR0 & 0x01)==0);     // wait for timer 0 to overflow 
  TCCR0A = 0x00;                // reset
  TCCR0B = 0x00;                // reset
  TIFR0 = 0x01;                 // reset   
}

int main(){
  DDRB = DDRB | (1<<5);         // set PB5 as output
  while(1){
    PORTB = PORTB | (1<<5);     // LED ON
    delay_timer();              // 2ms delay
    PORTB = PORTB & ~(1<<5);    // LED OFF
    delay_timer();              // 2ms delay
  }
}