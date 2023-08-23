#include "event_driven.h"
#include "app.h"
#include "pindefs.h"

int state = LOW;

void appinnit () {
  digitalWrite(LED1, HIGH);
  //digitalWrite(LED2, HIGH);
  //digitalWrite(LED3, HIGH);
  button_listen(KEY1);
  timer_set(1, 1000);
}

void button_changed (int pin, int v) {
  digitalWrite(LED1, LOW);
  exit(1);
}

void timer_expired (int t) {
  state = !state;
  digitalWrite(LED1, state);
  timer_set(1, 1000);
}