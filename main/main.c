#include <util/delay.h>
#include <avr/io.h>


int main(void) {
    PORTA.DIR |= PIN2_bm;
    PORTA.DIR |= PIN1_bm;

    /* Main loop */
    for (;;) {
        PORTA.OUT |= PIN2_bm;
        PORTA.OUT |= PIN1_bm;
        _delay_ms(500);
        PORTA.OUT &= ~PIN2_bm;
        PORTA.OUT &= ~PIN1_bm;
        _delay_ms(500);
    }
}