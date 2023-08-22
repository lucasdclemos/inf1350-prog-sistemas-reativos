// Lucas Demarco Cambraia Lemos - 2110013

#define LED1       10
#define LED2       11
#define LED3       12
#define LED4       13
#define BUZZ        3
#define KEY1       A1
#define KEY2       A2
#define KEY3       A3
#define POT        A0
#include <stdlib.h>
#include <time.h>

int passo = 0;
int leds[5] = {0, 0, 0, 0, 0};
unsigned long intervalo = 200;
unsigned long millis_anterior = 0;
unsigned long millis_exclusiva = 0;

void setup() {
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  gera_sequencia(leds);
}

void loop() {
  unsigned long millis_atual = millis();

  if (millis_atual - millis_anterior >= intervalo) {
    millis_anterior = millis_atual;
    if (digitalRead(KEY1) == LOW) {
      if (passo > 4) {
        if (digitalRead(LED1) == LOW) {
          digitalWrite(LED1, HIGH);
        }
        if (digitalRead(LED2) == LOW) {
          digitalWrite(LED2, HIGH);
        }
        if (digitalRead(LED3) == LOW) {
          digitalWrite(LED3, HIGH);
        }
        passo = 0;
        gera_sequencia(leds);
      } else {
        if (verifica(1) == 0) {
          digitalWrite(LED1, LOW);
        }
      }
    }
    if (digitalRead(KEY2) == LOW) {
      if (verifica(2) == 0) {
        digitalWrite(LED1, LOW);
      }
    }
    if (digitalRead(KEY3) == LOW) {
      if (verifica(3) == 0) {
        digitalWrite(LED1, LOW);
      }
    }
  }
  if (passo == 5) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
}

int verifica (int botao) {
  if (leds[passo] == botao) {
    passo++;
    return 1;
  } else {
    passo = 6;
    return 0;
  }
}

void gera_sequencia (int* leds) {
  int r;
  for (int i = 0; i < 5; i ++) {
    r = (rand() % 3) + 1 ;
    leds[i] = r;
    if (r == 1) {
      digitalWrite(LED1, LOW);
      delay(1000);
      digitalWrite(LED1, HIGH);
      delay(1000);
    } else if (r == 2) {
      digitalWrite(LED2, LOW);
      delay(1000);
      digitalWrite(LED2, HIGH);
      delay(1000);
    } else {
      digitalWrite(LED3, LOW);
      delay(1000);
      digitalWrite(LED3, HIGH);
      delay(1000);
    }
  }
}
