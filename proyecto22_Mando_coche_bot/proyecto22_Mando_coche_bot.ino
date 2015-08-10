//librerias
#include <SoftwareSerial.h>

//Objetos
SoftwareSerial BT(3,4);//tx,rx

//constantes
const int controlLed = A0;
const int frontLed = A1;
//motores izq
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;
//motores der
const int ENB = 10;
const int IN3 = 8;
const int IN4 = 9;

//variables
char orden;
int potencia = 120;
char estado = 's';

void setup() {
  Serial.begin(9600);
  //comunicación en serie bluetooth (necesario)
  BT.begin(9600);
  pinMode(controlLed,OUTPUT);
  pinMode(frontLed,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(frontLed,LOW);
  digitalWrite(controlLed,HIGH);

}

void loop() {
  Serial.println(orden);
  Serial.println(potencia);
  //si el bluetooth esta disponible
  if(BT.available()){
    //leer orden
    orden = BT.read();
    Serial.println(orden);
    //si la orden es p (cambio de estado del slider)
    if(orden == 'p'){
      //leemos el próximo valor entero
      potencia = BT.parseInt();
      continuar(potencia);
    }

  //switch de ordenes
  switch(orden){
    case 'a':
      adelante(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'a';
    break;

    case 'o':
      adelanteI(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'o';
    break;

    case 'e':
      adelanteD(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'e';
    break;

    case 'b':
      atras(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'b';
    break;

    case 'z':
      atrasI(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'z';
    break;

    case 'x':
      atrasD(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'x';
    break;

    case 'i':
      izquierda(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'i';
    break;

    case 'd':
      derecha(potencia);
      digitalWrite(frontLed,HIGH);
      estado = 'd';
    break;

    case 's':
      stopM();
      digitalWrite(frontLed,LOW);
      estado = 's';
    break;
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

  void adelanteI(int potencia){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENA,potencia);
    analogWrite(ENB,round(potencia/2.5));
  }

  void adelanteD(int potencia){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENA,round(potencia/2.5));
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

  void atrasI(int potencia){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENA,potencia);
    analogWrite(ENB,round(potencia/2.5));
  }

  void atrasD(int potencia){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENA,round(potencia/2.5));
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

  void derecha(int potencia){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENA,potencia);
    analogWrite(ENB,potencia);
  }

  void stopM(){
    analogWrite(ENA,0);
    analogWrite(ENB,0);
  }

  void continuar(int potencia){
    if(estado == 'a'){
      adelante(potencia);
    }else if(estado == 'b'){
      atras(potencia);
    }else if(estado == 'i'){
      izquierda(potencia);
    }else if(estado == 'd'){
      derecha(potencia);
    }else if(estado == 's'){
      stopM();
    }else if(estado == 'o'){
      adelanteI(potencia);
    }else if(estado == 'e'){
      adelanteD(potencia);
    }else if(estado == 'z'){
      atrasI(potencia);
    }else if(estado == 'x'){
      atrasD(potencia);
    }
  }
