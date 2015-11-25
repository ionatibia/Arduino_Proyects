int ledPin = 9;

void setup(){
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(ledPin,HIGH);
  Serial.println("encendido");
  delay(1000);
  digitalWrite(ledPin,LOW);
  Serial.println("apagado");
  delay(1000);
}
