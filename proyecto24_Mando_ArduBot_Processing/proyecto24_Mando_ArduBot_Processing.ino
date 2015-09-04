char inChar;
//librerias
#include <SoftwareSerial.h>

//Objetos
SoftwareSerial BT(3,4);//tx,rx

void setup() {
  BT.begin(9600);
}

void loop() {
  while (BT.available()){
    inChar = (char)(BT.read());
  }
}
