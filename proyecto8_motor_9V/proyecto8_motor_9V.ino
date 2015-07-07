const int switchPin = 2;
const int motorPin = 9;
int swtchState = 0;
int const potPin = A0;
int potVal;
int potencia;

void setup() {
  pinMode(motorPin,OUTPUT);
  pinMode(switchPin,INPUT);

}

void loop() {
//leer potenciometro (0-1023)
  potVal = analogRead(potPin);
  swtchState = digitalRead(switchPin);
  potencia = map(potVal, 0, 1023, 0, 255);
  if (swtchState == HIGH)
  {
  	analogWrite(9,potencia);
  }else{
  	digitalWrite(motorPin,LOW);
  }
}
