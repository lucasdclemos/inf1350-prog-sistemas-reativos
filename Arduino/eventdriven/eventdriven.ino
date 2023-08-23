#include "pindefs.h"
#include "eventdriven.h"
#include "app.h"

int botoes[3] = {0, 0, 0};
unsigned long intervalo = 200;
unsigned long millis_botoes[3] = {0, 0, 0};

int timers_ativos[3] = {0, 0, 0};
int timers[3] = {0, 0, 0};
unsigned long millis_inicial = 0;

void button_listen (int pin) {
  if (pin == KEY1) {
    botoes[0] = 1;
  } else if (pin == KEY2) {
    botoes[1] = 1;
  } else if (pin == KEY3) {
    botoes[2] = 1;
  }
}

void timer_set (int t, int ms) {
  timers_ativos[t] = 1;
  timers[t] = ms;
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  appinnit();
}

void loop() {
  unsigned long millis_atual = millis();

  if (millis_atual - millis_botoes[0] >= intervalo) {
    if (botoes[0] == 1 && digitalRead(KEY1) == LOW) {
      millis_botoes[0] = millis_atual;
      button_changed(KEY1, digitalRead(KEY1));
    }
  }

  if (millis_atual - millis_botoes[1] >= intervalo) {
    if (botoes[1] == 1 && digitalRead(KEY2) == LOW) {
      millis_botoes[1] = millis_atual;
      button_changed(KEY2, digitalRead(KEY2));
    }
  }

  if (millis_atual - millis_botoes[2] >= intervalo) {
    if (botoes[2] == 1 && digitalRead(KEY3) == LOW) {
      millis_botoes[2] = millis_atual;
      button_changed(KEY3, digitalRead(KEY3));
    }
  }

  for (int i = 0; i < 3; i++) {
    if (timers_ativos[i] == 1) {
      timers[i] -= millis_atual - millis_anterior;
      if (timers[i] <= 0) {
        timers_ativos[i] = 0;
        timers[i] = 0;
        timer_expired(i);
      }
    }
  }

  millis_anterior = millis_atual;
}



















