#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // led
  PORTA.DIRSET |= PIN2_bm;
  // SEL
  PORTA.DIRSET |= PIN7_bm;
  // OUT-LIV
  PORTA.DIRSET |= PIN1_bm;

  int i;
  for (i = 0; i < 30; i++) {
    PORTA.OUT |= PIN2_bm;
    _delay_ms(250);
    PORTA.OUT &= ~PIN2_bm;
    _delay_ms(250);
  }

  PORTA.OUT |= PIN2_bm;

  for (;;) {
    // set SEL = 0
    PORTA.OUT &= ~PIN7_bm;
    // waits 1 sec then change SEL to 1
    _delay_ms(2000);
    // set SEL = 1
    PORTA.OUT |= PIN7_bm;
    // waits 1 sec then check IN-LIV PA6
    _delay_ms(2000);

    // if there's h2o
    if (PORTA.IN & PIN6_bm) {
      PORTA.OUT |= PIN1_bm;
    } else {
      PORTA.OUT &= ~PIN1_bm;
    }
  }
}
