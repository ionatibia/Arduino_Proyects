#include <CapacitiveSensor.h>
//donde esta conectado el sensor (pin con la resistencia de 1M, el otro)
CapacitiveSensor capSensor = CapacitiveSensor(4,2);

//al tocar subira el valor, éste es el umbral
int threshold = 1000;
const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(30);
  Serial.println(sensorValue);

  if (sensorValue > threshold)
  {
  	digitalWrite(ledPin,HIGH);
  }else{
  	digitalWrite(ledPin,LOW);
  }

  delay(10);
}
