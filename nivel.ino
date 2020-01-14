/*
* Programa para medir o nível de água com três sensores.
* Sensor 1 100% de água na caixa.
* Sensor 2 75% de água na caixa.
* Sensor 3 50% de água na caixa.
* Quando os três sensores apresentarem estado falso a caixa tem menos de 50% de água e o led de alerta é aceso.
* Autor: Elias Gonçalves
* Email: falarcomelias@gmail.com
*/

#define LED_100 13   // Verde
#define LED_75 12    // Azul
#define LED_50 11     // Amarelo
#define LED_ALERTA 10 // Vermelho
#define BUZZER 9

#define BOIA_100 7
#define BOIA_75 6
#define BOIA_50 5

void alarme();

float seno;
int frequencia;

void setup() {  
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_100, OUTPUT);
  pinMode(LED_75, OUTPUT);
  pinMode(LED_50, OUTPUT);
  pinMode(LED_ALERTA, OUTPUT);
  pinMode(BOIA_100, INPUT);
  pinMode(BOIA_75, INPUT);
  pinMode(BOIA_50, INPUT);
}

void loop() {
  boolean estado_100 = digitalRead(BOIA_100);
  boolean estado_75 = digitalRead(BOIA_75);
  boolean estado_50 = digitalRead(BOIA_50);

  if (estado_100 && estado_75 && estado_50) {
    digitalWrite(LED_100, HIGH);
    digitalWrite(LED_75, LOW);
    digitalWrite(LED_50, LOW);
    digitalWrite(LED_ALERTA, LOW);
    alarme(); // Sinaliza que a caixa está cheia e precisa desligar a bomba. 
              // Por decisão do cliente o ato de ligar e desligar a bomba permanece manual.
  }

  else if (estado_75 && estado_50) {
    digitalWrite(LED_100, LOW);
    digitalWrite(LED_75, HIGH);
    digitalWrite(LED_50, LOW);
    digitalWrite(LED_ALERTA, LOW);  
  }

  else if (estado_50) {
    digitalWrite(LED_100, LOW);
    digitalWrite(LED_75, LOW);
    digitalWrite(LED_50, HIGH);
    digitalWrite(LED_ALERTA, LOW);
  }
  
  else {
    digitalWrite(LED_100, LOW);
    digitalWrite(LED_75, LOW);
    digitalWrite(LED_50, LOW);
    digitalWrite(LED_ALERTA, HIGH);
  }
  noTone(BUZZER);
}


void alarme() {
  for (int i = 0; i < 180; i++) {
    seno = (sin(i * 3.1416 / 180));
    frequencia = 2000 + (int(seno * 1000));
    tone(BUZZER, frequencia);
    delay(2);
  }
}
