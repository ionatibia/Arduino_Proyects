int shock = 3;

void setup() {
  Serial.begin(9600);
  pinMode(shock,INPUT);
}

void loop() {
  Serial.println(digitalRead(shock));
}
