//importar librería servomotores
#include <Servo.h>

//crear objeto de tipo Servo
Servo myServo;

//variables
int const potPin = A0;
int potVal;
int angle;

void setup() {
  //definir Pin del servo
  myServo.attach(9);

  Serial.begin(9600);

}

void loop() {
  //leer potenciometro (0-1023)
  potVal = analogRead(potPin);
  //Imprimir en consola valor potenciometro
  Serial.print("\npotVal= ");
  Serial.print(potVal);
  //Calcular el angulo map(valorPotenciometro, min-pote, max-pote, min-servo, max-servo
  angle = map(potVal, 0, 1023, 0, 179);
  //Imprimir en consola
  Serial.print("\nangle= ");
  Serial.print(angle);

  //Mover el servo
  myServo.write(angle);
  delay(15);

}
