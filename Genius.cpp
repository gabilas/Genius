const int NIVEL_MAXIMO = 100;
int SEQUENCIA[NIVEL_MAXIMO];
int SOM[NIVEL_MAXIMO];
int SEQUENCIA_DO_JOGADOR[NIVEL_MAXIMO];
int NIVEL = 1;
int NOTA = 0;
int VELOCIDADE = 1000;

void setup() {
  pinMode(13, OUTPUT); //LED Vermelho
  pinMode(12, OUTPUT); //LED Amarelo
  pinMode(11, OUTPUT); //LED Verde
  pinMode(10, OUTPUT); //LED Azul 

  pinMode(7, INPUT_PULLUP); //Botão Vermelho
  pinMode(6, INPUT_PULLUP); //Botão Amarelo
  pinMode(5, INPUT_PULLUP); //Botão Verde
  pinMode(4, INPUT_PULLUP); //Botão Azul 

  pinMode(3, OUTPUT); //Buzzer
}

void loop() {
  if (NIVEL == 1) {
    GERAR_SEQUENCIA();
    
    for (int i = 13; i >= 10; i--) { //Piscar LEDs antes de começar o jogo

      switch (i) { //Sons para cada cor
      case 10:
        NOTA = 349; //Fá 
        break;
      case 11:
        NOTA = 329; //Mi
        break;
      case 12:
        NOTA = 293; //Ré
        break;
      case 13:
        NOTA = 261; //Dó
        break;
    }

      SOM[i] = NOTA;
      
      digitalWrite(i, HIGH);
      tone(3, SOM[i]);
      delay(330);
      digitalWrite(i, LOW);
      noTone(3);
    }
  }

  if (digitalRead(7) == LOW || NIVEL != 1) { //Começar jogo
    MOSTRAR_SEQUENCIA();
    PEGAR_SEQUENCIA();
  }
}

void GERAR_SEQUENCIA() {
  randomSeed(millis());

  for (int i = 0; i < NIVEL_MAXIMO; i++) { // Piscar LED aleatório
    SEQUENCIA[i] = random(10, 13);

    switch (SEQUENCIA[i]) { //Sons para cada cor
      case 10:
        NOTA = 349; //Fá 
        break;
      case 11:
        NOTA = 329; //Mi
        break;
      case 12:
        NOTA = 293; //Ré
        break;
      case 13:
        NOTA = 261; //Dó
        break;
    }
    SOM[i] = NOTA;
  }
}

void MOSTRAR_SEQUENCIA() {
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);

  for (int i = 0; i < NIVEL; i++) {
    digitalWrite(SEQUENCIA[i], HIGH);
    tone(3, SOM[i]);
    delay(VELOCIDADE);
    digitalWrite(SEQUENCIA[i], LOW);
    noTone(3);
    delay(200);
  }
}

void PEGAR_SEQUENCIA() {
  int SINALIZADOR = 0; //Sinaliza se a sequência está correta

  for (int i = 0; i < NIVEL; i++) {
    SINALIZADOR = 0;

    while (SINALIZADOR == 0) {

      if (digitalRead(7) == LOW) { // Sinalizar se a sequência está correta (LED Vermelho)
        digitalWrite(13, HIGH);
        tone(3, 261); //Dó
        delay(VELOCIDADE);
        noTone(3);
        SEQUENCIA_DO_JOGADOR[i] = 13;
        SINALIZADOR = 1;
        delay(200);

        if (SEQUENCIA_DO_JOGADOR[i] != SEQUENCIA[i]) {
          SEQUENCIA_ERRADA();
          return;
        }
        digitalWrite(13, LOW);
      }

      if (digitalRead(6) == LOW) { // Sinalizar se a sequência está correta (LED Amarelo)
        digitalWrite(12, HIGH);
        tone(3, 293); //Ré
        delay(VELOCIDADE);
        noTone(3);
        SEQUENCIA_DO_JOGADOR[i] = 12;
        SINALIZADOR = 1;
        delay(200);

        if (SEQUENCIA_DO_JOGADOR[i] != SEQUENCIA[i]) {
          SEQUENCIA_ERRADA();
          return;
        }
        digitalWrite(12, LOW);
      }

      if (digitalRead(5) == LOW) { // Sinalizar se a sequência está correta (LED Verde)
        digitalWrite(11, HIGH);
        tone(3, 329); //Mi
        delay(VELOCIDADE);
        noTone(3);
        SEQUENCIA_DO_JOGADOR[i] = 11;
        SINALIZADOR = 1;
        delay(200);

        if (SEQUENCIA_DO_JOGADOR[i] != SEQUENCIA[i]) { 
          SEQUENCIA_ERRADA();
          return;
        }
        digitalWrite(11, LOW);
      }

      if (digitalRead(4) == LOW) { // Sinalizar se a sequência está correta (LED Azul)
        digitalWrite(10, HIGH);
        tone(3, 349); //Fá
        delay(VELOCIDADE);
        noTone(3);
        SEQUENCIA_DO_JOGADOR[i] = 10;
        SINALIZADOR = 1;
        delay(200);

        if (SEQUENCIA_DO_JOGADOR[i] != SEQUENCIA[i]) {
          SEQUENCIA_ERRADA();
          return;
        }
        digitalWrite(10, LOW);
      }
    }
  }
  SEQUENCIA_CERTA();
}

void SEQUENCIA_CERTA() { //Indica se o jogador acertou a sequência
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  tone(3, 262,200);
  delay(250);
  
  noTone(3);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  tone(3, 294,300);
  delay(250);

  noTone(3);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  tone(3, 349,300);
  delay(250);
  
  noTone(3);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  tone(3, 294,300);
  delay(100);
  
  noTone(3);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  tone(3, 349,300);
  delay(500);
  noTone(3);
  delay(250);

  if (NIVEL < NIVEL_MAXIMO) {
    NIVEL++;
  }
  VELOCIDADE -= 50; //Deixa mais rápido, aumentando a dificuldade
}

void SEQUENCIA_ERRADA() { //Indica se o jogador errou a sequência
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    tone(3, 233);
    delay(250);

    noTone(3);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    tone(3, 233);
    delay(250);
    noTone(3);
  }
  NIVEL = 1;
  VELOCIDADE = 1000;
}