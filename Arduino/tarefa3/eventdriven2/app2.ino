// Lucas Demarco Cambraia Lemos - 2110013
// Natalia Passini Grossmann - 2110456

#include "eventdriven.h"
#include "app.h"
#include "pindefs.h"

int state = LOW;
int intervalo_piscada = 1000;
bool ledOn = true;
unsigned long millis_botao1 = 0;
unsigned long millis_botao2 = 0;

void appinnit () {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  Serial.begin(9600);
  button_listen(KEY1);
  button_listen(KEY2);
  button_listen(KEY3);
  timer_set(1, intervalo_piscada);
}

void button_changed (int pin, int v) {
  if (pin == KEY1) {
    intervalo_piscada /= 2;
    millis_botao1 = millis();
  } 
  else if (pin == KEY2) {
    intervalo_piscada *=2;
    millis_botao2 = millis();
  } 
  if (millis_botao2 - millis_botao1 <= 500 || millis_botao1 - millis_botao2 <= 500) {
    ledOn = !ledOn;
    Serial.println(ledOn);
  }
}

void timer_expired (int t) {
  if (ledOn) {
    state = !state;
    digitalWrite(LED1, state);
    timer_set(1, intervalo_piscada);
  } else {
    digitalWrite(LED1, HIGH);
    Serial.println("apaga");
    exit(1);
  }

}
