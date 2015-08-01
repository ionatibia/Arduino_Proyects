//librerías
#include <SoftwareSerial.h>
#include <Ultrasonic.h>
#include <Servo.h>

//Objetos
SoftwareSerial blue(2,3);//tx,rx
Ultrasonic ultrasonic(5,4);//trig,echo,frecuencia
Servo myServo;

//constantes (IN1,IN2 & ENA = motores D -- IN3,IN4,ENB = motores I
const int controlLed = A0;
const int frontLed = A2;
const int IN1 = A4;
const int IN2 = 7;
const int ENA = 11;
const int IN3 = 8;
const int IN4 = 9;
const int ENB = 10;
const int sensor = A5;

//variables
int distanciaD;
int distanciaB;
char orden;
int potencia = 130;
int obstaculo;
int anguloC = 90;
int anguloI = 0;
int anguloD = 179;

void setup() {
  Serial.begin(9600);
  blue.begin(9600);
  blue.println("Conectado");
  myServo.attach(6);
  myServo.write(anguloC);
  pinMode(sensor,INPUT);
  pinMode(controlLed,OUTPUT);
  pinMode(frontLed,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  digitalWrite(controlLed,LOW);
  digitalWrite(frontLed,HIGH);
  
}

void loop() {
  //comprobar distancia delantera y trasera
  distanciaD = ultrasonic.Ranging(CM);
  distanciaB = analogRead(sensor);
  //si adelante pero false comprobar delante
  if(!comprobarDelante() && digitalRead(IN1) == 0 && digitalRead(IN3) == 0){ 
    stopM();
  }
  //si atras pero false comprobar atras
  if(!comprobarDetras() && digitalRead(IN1) == 1 && digitalRead(IN3) == 1){
    stopM();
  }

  //si el BT esta disponible
  Serial.println(potencia);
  if(blue.available()){
    //leer BT
    orden = blue.read();
    if(orden == 'p'){
      potencia = blue.parseInt();
      continuar(potencia);
    }
    
    switch(orden){
      case 'a':
        if(comprobarDelante()){
          adelante(potencia);
          digitalWrite(controlLed,HIGH);
          blue.println("Adelante");
        }else{
          blue.println("Obstáculo");
        }
       break;

      case 'b':
        if(comprobarDetras()){
          atras(potencia);
          digitalWrite(controlLed,HIGH);
          blue.println("Atrás");
        }else{
          blue.println("Obstáculo");
        }
        break;
        
      case 'i':
          izquierda(potencia);
          digitalWrite(controlLed,HIGH);
          blue.println("Izquierda");
        break;

      case 'd':
          derecha(potencia);
          digitalWrite(controlLed,HIGH);
          blue.println("Derecha");
        break;

      case 's':
      digitalWrite(controlLed,LOW);
          stopM();
          blue.println("Paro");
    }
  }

}

void adelante(int potencia){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENA,potencia);
    analogWrite(ENB,potencia);
}

void atras(int potencia){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENA,potencia);
    analogWrite(ENB,potencia);
}

void derecha(int potencia){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENA,potencia);
    analogWrite(ENB,potencia);
}

void izquierda(int potencia){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENA,potencia);
    analogWrite(ENB,potencia);
}

void stopM(){
    analogWrite(ENA,0);
    analogWrite(ENB,0);
    digitalWrite(controlLed,LOW);
}

boolean comprobarDelante(){
  if(distanciaD > 38){
        return true;
      }else{
        return false;

      }
}

boolean comprobarDetras(){
  if(distanciaB > 50){
    return true;
  }else{
    return false;
  }
}

void continuar(int potencia){
  if(digitalRead(IN1) == 0 && digitalRead(IN3) == 0 && digitalRead(controlLed) == HIGH){
    adelante(potencia);
  }else if(digitalRead(IN1) == 1 && digitalRead(IN3) == 1 && digitalRead(controlLed) == HIGH){
    atras(potencia);
  }else if(digitalRead(IN2) == 0 && digitalRead(controlLed) == HIGH){
    derecha(potencia);
  }else if(digitalRead(controlLed) == LOW){
    stopM();
  }else {
    izquierda(potencia);
  }
}

