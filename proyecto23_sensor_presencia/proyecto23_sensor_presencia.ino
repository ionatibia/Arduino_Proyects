int ledPin = 12;
int sensorPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(sensorPin,INPUT);
  delay(2000);
  digitalWrite(ledPin,HIGH);
  delay(500);
  digitalWrite(ledPin,LOW);
}

void loop() {
  Serial.println(digitalRead(sensorPin));
  if(digitalRead(sensorPin) == HIGH){
    digitalWrite(ledPin,HIGH);
    
  }else{
    digitalWrite(ledPin,LOW);
  }

}
