//Librería creada por Antony García, de www.panamahitek.com
//Sígueme en facebook, twitter y en mi canal de youtube

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Ultrasonido.h"

Ultrasonido::Ultrasonido(int pinEmisor, int pinEco, int MaxDist)
{
   pinMode(pinEmisor,OUTPUT);
   pinMode(pinEco,INPUT);
   Trigger=pinEmisor;
   Echo=pinEco;
   TimeOut=MaxDist*58;  
}


long Ultrasonido::Tiempo()
{
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  duracion = pulseIn(Echo,HIGH,TimeOut);
  if ( duracion == 0 ) {duracion = TimeOut;}
  return duracion;
}

long Ultrasonido::Distancia()
{
  Tiempo();

  dist = duracion / 29 / 2 ;
  return dist;

}