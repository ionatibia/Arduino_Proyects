//variables para el sensor
int sensorValue = 0;
int sensorLow = 1023;
int sensorHigh = 0;

//constante led integrado 13
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  //encender el led 13 integrado
  digitalWrite(ledPin, HIGH);

  //while de 5 seg para determinar los valore máximos y mínimos y guardarlos 
  // en caso de ser diferentes de los teóricos
  while (millis() < 5000){
    sensorValue = analogRead(A0);
    if(sensorValue > sensorHigh){
      sensorHigh = sensorValue;
    }
    if(sensorValue < sensorLow){
      sensorLow = sensorValue;
    }
    digitalWrite(ledPin, LOW);
  }//while
}//setup

void loop() {
  //leer valor sensor
  sensorValue = analogRead(A0);

  //guardamos el valor pitch que és según (valorDelSensor, valorMinSensor, ValorMaxSensor, valorMinFrecuencia, valorMaxFrecuencia)
  int pitch = map(sensorValue, sensorLow,sensorHigh,50,4000);

  //1- pin de salida, 2- frecuencia de pulso, 3- Tiempo
  tone(8,pitch,20);
  //Tiempo de espera para reproducir el sonido
  delay(10);

}
