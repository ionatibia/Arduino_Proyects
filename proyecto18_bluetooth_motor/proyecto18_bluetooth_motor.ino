#include <SoftwareSerial.h>
#include <Ultrasonido.h>
char rec;
SoftwareSerial blue(2,3);//tx, rx
Ultrasonido ultrasonic(11,12,100); // (Trig PIN,Echo PIN)
int distancia;
int led = 4;
//Motor derecha
int IN1 = 6;
int IN2 = 7;
int ENA = 5;
//Motor izquierda
int IN3 = 8;
int IN4 = 9;
int ENB = 10;
void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  blue.begin(9600);
  blue.println("Conectado");
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
}
void loop() {
  distancia = ultrasonic.Distancia();
 Serial.println(distancia);
  if(blue.available()){
    rec=blue.read();
    switch(rec){
      case '0':
        digitalWrite(led,LOW);
        delay(500);
        blue.println("Led off");
        analogWrite(ENA,0);
        analogWrite(ENB,0);
        break;
      case '1':
        digitalWrite(led,HIGH);
        delay(500);
        blue.println("Led on");
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        while(distancia > 15){
         analogWrite(ENA,200);
         analogWrite(ENB,200);
         distancia = ultrasonic.Distancia();
        }
        analogWrite(ENA,0);
        analogWrite(ENB,0);
        break;
       case '2':
        digitalWrite(led,HIGH);
        delay(500);
        blue.println("Led on");
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        analogWrite(ENA,255);
        analogWrite(ENB,255);
        delay(1000);
        analogWrite(ENA,0);
        analogWrite(ENB,0);
        break;
      default:
        delay(500);
        blue.print(rec);
        blue.println(" no es una orden valida. Introduzca 0 o 1");
    }
  }
}
