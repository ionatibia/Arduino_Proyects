//constantes para los pines
const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin =5;
const int potPin = A0;

//variables para los sensores
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {
  //definir los pines de salida y de entrada
  pinMode(directionSwitchPin,INPUT);
  pinMode(onOffSwitchStateSwitchPin,INPUT);
  pinMode(controlPin1,OUTPUT);
  pinMode(controlPin2,OUTPUT);
  pinMode(enablePin,OUTPUT);

  //parar el motor por si acaso
  digitalWrite(enablePin,LOW);
}

void loop() {
  //leer el botón de encendido
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  //leer el btó de cambio de direccion
  directionSwitchState = digitalRead(directionSwitchPin);
  //calcular l velcidad del motor en relación con el potenciómetro
  motorSpeed = analogRead(potPin)/4;

  //Si ha cambiado el estado del botón de encendido
  if (onOffSwitchState != previousOnOffSwitchState)
  {
    //s el estado es encendid
  	if (onOffSwitchState == HIGH)
  	{
      //cambiar el estado del motor
  		motorEnabled = !motorEnabled;
  	}
  }

  //l mism que para la direccion
  if (directionSwitchState != previousDirectionSwitchState)
  {
  	if (directionSwitchState == HIGH)
  	{
  		motorDirection = !motorDirection;
  	}
  }

  //si la dirección es 1 (cambio)
  if (motorDirection == 1)
  {
     //cierra el 1 y abre el 2 (una dirección
  	digitalWrite(controlPin1,HIGH);
  	digitalWrite(controlPin2,LOW);
  }else{
    //cierra el 2 y abre el 1 (otra dirección)
  	digitalWrite(controlPin1,LOW);
  	digitalWrite(controlPin2,HIGH);
  }

  //si el estado de motor es 1
  if (motorEnabled == 1)
  {
    //pone el mtor en marcha cn la velcidad calculada
  	analogWrite(enablePin,motorSpeed);
  }else{
    //si no, lo para
  	analogWrite(enablePin,0);
  }

  //el estado de dirección y de encendido los guardamos en las variables previous
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}
