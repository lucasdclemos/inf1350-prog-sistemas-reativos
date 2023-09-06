#include <TimerOne.h>                     
#include <Wire.h>                         
#include <MultiFuncShield.h>
#include "mini-projeto.h"
#include "app.h"
#include "pindefs.h"

int jogo[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
int linha = 1;
int coluna = 1;
int dimensao = 1; // dimensao que esta sendo escolhida
int jogador = 1;
char texto[5]; 
int acabou = 0;
int jogadas = 0;

void appinit () {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  Timer1.initialize();
  MFS.initialize(&Timer1);
  Serial.begin(9600);
  button_listen(KEY1);
  button_listen(KEY3);
  muda_jogador();
  muda_display();
}

void reseta () {
  linha = 1;
  coluna = 1;
  dimensao = 1;
  jogador = 1;
  acabou = 0;  
  jogadas = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      jogo[i][j] = 0;
    }
  }
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  muda_jogador();
  muda_display();
}

void muda_display () {
   if (dimensao == 1) {
    sprintf(texto, "LIN.%d", linha);
  } else {
    sprintf(texto, "COL.%d", coluna);
  }
  MFS.write(texto);
}

void muda_jogador () {
  if (acabou == 0) {
    if (jogador == 1) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    } else {
      digitalWrite(LED2, LOW);
      digitalWrite(LED1, HIGH);
    }
  }
}

void verifica_matriz (int numero) {
  jogadas++;
  if (jogo[0][0] == numero && jogo[0][1] == numero && jogo[0][2] == numero) {
    acabou = 1;
  }
  else if (jogo[0][0] == numero && jogo[1][0] == numero && jogo[2][0] == numero) {
    acabou = 1;
  }
  else if (jogo[1][0] == numero && jogo[1][1] == numero && jogo[1][2] == numero) {
    acabou = 1;
  }
  else if (jogo[2][0] == numero && jogo[2][1] == numero && jogo[2][2] == numero) {
    acabou = 1;
  }
  else if (jogo[0][1] == numero && jogo[1][1] == numero && jogo[2][1] == numero) {
    acabou = 1;
  }
  else if (jogo[0][2] == numero && jogo[1][2] == numero && jogo[2][2] == numero) {
    acabou = 1;
  }
  else if (jogo[0][0] == numero && jogo[1][1] == numero && jogo[2][2] == numero) {
    acabou = 1;
  }
  else if (jogo[0][2] == numero && jogo[1][1] == numero && jogo[2][0] == numero) {
    acabou = 1;
  }
  if (jogadas == 9 && acabou == 0) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    button_unlisten(KEY2);
    button_unlisten(KEY1);
    button_listen(KEY3);
    MFS.write(0000);
    acabou = 2;
  }
}

void marca_matriz () {
  if (jogo[linha-1][coluna-1] != 1 && jogo[linha-1][coluna-1] != 2){
    jogo[linha-1][coluna-1] = jogador;
    verifica_matriz(jogo[linha-1][coluna-1]);
    linha = 1;
    coluna = 1;
    if (acabou != 1) {
      if (jogador == 1) {
        jogador = 2;
      } else {
        jogador = 1;
      }
      muda_jogador(); 
    } else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      button_unlisten(KEY2);
      button_unlisten(KEY1);
      button_listen(KEY3);
      MFS.write(jogador);
    } 
  }
}

void button_changed (int pin, int v) {
  if (pin == KEY1) {
    if (linha == 3) {
      linha = 1;
    } else {
      linha++;
    }
    muda_display();
  }
  else if (pin == KEY2) {
    if (coluna == 3) {
      coluna = 1;
    } else {
      coluna++;
    }
    muda_display();
  }
  else {
    if (acabou != 0) {
      reseta();
    } else {
      if (dimensao == 1) {
        dimensao = 2;
        button_unlisten(KEY1);
        button_listen(KEY2);
      } else {
        dimensao = 1;
        button_unlisten(KEY2);
        button_listen(KEY1);
        marca_matriz ();
      }
      if (acabou == 0) {
        muda_display();
      }
    } 
  }
  
}
