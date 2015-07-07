//constante para pin del sensor
const int switchPin = 8;

//Sin signo long de 0 hasta máximo, con signo, el máximo entre 2
unsigned long previousTime = 0;

//creamos variable y damos valor 0 al estado y anterior estado
int switchState = 0;
int prevSwitchState =0;

//damos valor 2 (primer led) 
int led = 2;

//intervalo, cada cuanto tiempo se encenderán las luces
long interval = 6000;

void setup() {
  //set output 2-7 pins
  for (int i = 2; i < 8; i++)
  {
    pinMode(i,OUTPUT);
  }
  pinMode(switchPin,INPUT);
}//setup

void loop() {
  //cojer en variable el tiempo desde encendido
  unsigned long currentTime = millis();

  //cuando la diferencia entre el tiempo anterior y el ahora sea mayor que el intervalo
  if (currentTime - previousTime > interval)
  {
    previousTime = currentTime;
    digitalWrite(led, HIGH);
    //Si el led encendido es el último
    if (led == 7)
    {
        tone(12,262);   
    }
    led++;
  //en el siguiente encendido apagar el sonido
    if (led == 8){
      noTone(12);
    }
  }//if
//leer el estado del sensor
  switchState = digitalRead(switchPin);
//si cambia resetear el reloj
  if(switchState != prevSwitchState){
    for (int x = 2; x < 8; x++)
    {
      digitalWrite(x,LOW);
    }
    led = 2;
    previousTime = currentTime;
  }//if

  prevSwitchState = switchState;
}//loop
