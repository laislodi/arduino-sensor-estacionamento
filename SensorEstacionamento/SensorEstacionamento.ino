// inclusao das bibliotecas que serao utilizadas no projeto
#include <LiquidCrystal.h>
#include "Ultrasonic.h"

// definicao dos pinos digitais
#define displayData7 51
#define displayData6 50
#define displayData5 49
#define displayData4 48
#define displayEnable 47 // porta 6 ligada ao pino E do LCD
#define displayRS 46     // porta 7 ligada ao pino RS do LCD
#define buzzer 52        // porta 8 ligada no catodo do buzzer. Anodo ligado ao GND do arduino
#define trigger 44       // porta 9 ligada ao trigger do sensor ultrasonico
#define echo 45          // porta 10 ligada ao echo do sensor ultrasonico
#define ledVermelho 42   // led em serie com um resistor de 1K
#define ledVerde 43     // led em serie com um resistor de 1K

// criando objeto ultrasonic e definindo as portas digitais do Trigger e Echo
Ultrasonic ultrasonic(trigger, echo);

// Configura o display LCD
LiquidCrystal lcd(displayRS, displayEnable, displayData4, displayData5, displayData6, displayData7); //Configura os pinos do Arduino para se comunicar com o LCD

// inicializacao das variaveis
long microsec = 0;
float distanciaCM = 0;

// configuracoes iniciais
void setup() {
  // configura o lcd com o numero de linhas e colunas, respectivamente
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("  Distancia:");
  pinMode(buzzer,OUTPUT); // Definindo pino digital 8 como saida

  pinMode(ledVermelho,OUTPUT); // Definindo pino digital 11 como saida.
  pinMode(ledVerde,OUTPUT);  //Definindo pino digital 13 como saida.
}

// configuracoes do funcionamento do circuito
void loop() {  
  microsec = ultrasonic.timing(); //Lendo o sensor ultrasonico
  distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM); //Convertendo a distÃ¢ncia em CM

  ledDistancia(); // funcao definida abaixo

  Serial.print("Distancia: ");
  Serial.println(distanciaCM);
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.print(distanciaCM);
  lcd.print(" cm      ");
}


void ledDistancia() {
  // Acendendo o led adequado para a distancia lida no sensor
  if (distanciaCM <= 150 and distanciaCM > 70) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
  }

  if (distanciaCM <= 70 and distanciaCM > 30) {
    digitalWrite(ledVermelho,LOW);
    
    digitalWrite(ledVerde, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(150);
    digitalWrite(ledVerde, LOW);
    digitalWrite(buzzer, LOW);
    delay(150);
  }

  if (distanciaCM <= 30 and distanciaCM > 5) {
    digitalWrite(ledVerde,LOW);
    
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
    delay(100);
  }
  if (distanciaCM <= 5) {
    digitalWrite(ledVerde,LOW);
    
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
    delay(50);
  }
}


