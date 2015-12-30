//Librería creada por Antony García, de www.panamahitek.com
//Sígueme en facebook, twitter y en mi canal de youtube

#ifndef Ultrasonido_h
#define Ultrasonido_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define CM 1
#define INC 0

class Ultrasonido
{
  public:
    Ultrasonido(int pinEmisor, int pinEco, int MaxDist);
	
    long Tiempo();
    long Distancia();

  private:
    int Trigger;
    int Echo;
	long TimeOut;
    long duracion,dist;
};

#endif