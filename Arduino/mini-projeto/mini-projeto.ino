#include <TimerOne.h>                     
#include <Wire.h>                         
#include <MultiFuncShield.h>
#include "pindefs.h"
#include "mini-projeto.h"
#include "app.h"

int botoes[3] = {0, 0, 0};
unsigned long intervalo = 200;
unsigned long millis_botoes[3] = {0, 0, 0};

void button_listen (int pin) {
  if (pin == KEY1) {
    botoes[0] = 1;
  } else if (pin == KEY2) {
    botoes[1] = 1;
  } else if (pin == KEY3) {
    botoes[2] = 1;
  }
}

void button_unlisten (int pin) {
  if (pin == KEY1) {
    botoes[0] = 0;
  } else if (pin == KEY2) {
    botoes[1] = 0;
  } else if (pin == KEY3) {
    botoes[2] = 0;
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);
  appinit();
}

void loop() {
  // put your main code here, to run repeatedly:
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

}
