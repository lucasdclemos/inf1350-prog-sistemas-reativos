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

int estado_botao1 = 0; 
int estado_botao2 = 0; 
bool ledOn = false;
unsigned long millis_anterior = 0;
unsigned long botao1_apertou = 0;
unsigned long botao2_apertou = 0;
const long intervalo = 1000;

void setup() {
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
}

void loop() {
  if (digitalRead(KEY1) == LOW) {
    estado_botao1 = 1;
    botao1_apertou = millis();
  }

  if (digitalRead(KEY2) == LOW) {
    estado_botao2 = 1;
    botao2_apertou = millis();
  }

  if (estado_botao1 && estado_botao2) {
    if (botao1_apertou - botao2_apertou <= 500 || botao2_apertou - botao1_apertou <= 500) {
      ledOn = !ledOn;
    }
    estado_botao1 = 0;
    estado_botao2 = 0;
  }

  unsigned long millis_atual = millis();

  if (ledOn && millis_atual - millis_anterior >= intervalo) {
    millis_anterior = millis_atual;

    if (digitalRead(LED1) == HIGH) {
      digitalWrite(LED1, LOW);

    } else {
      digitalWrite(LED1, HIGH);
    }
  } else if (!ledOn) {
    digitalWrite(LED1, HIGH); 
  }
}
