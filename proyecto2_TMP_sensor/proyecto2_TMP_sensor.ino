const int sensorPin = A0;
const float baselineTemp = 26.0; //controlar la temperatura ambiente

void setup() {
  Serial.begin(9600); //abrir puerto en serie

  for(int pinNumber = 2; pinNumber<5; pinNumber++){
    pinMode(pinNumber,OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}//setup

void loop() {
  //imprimir el valor del sensor en el puerto serie
 int sensorVal = analogRead(sensorPin);
 Serial.print("Sensor value: ");
 Serial.print(sensorVal);

 //Convertir la lectura del sensor a voltaje
 //el sensor envía entre 0 - 1023 equivalente a 0 - 5 V
 float voltage = (sensorVal/1024.0) * 5.0;

 //Imprimir valores de voltaje calculados
 Serial.print(" , Volts: ");
 Serial.print(voltage);

 Serial.print(" , degrees C: ");
 //Convertir de voltaje a grados centígrados (ver datos del componente)
 float temperature = (voltage - .5) * 100;
 Serial.print(temperature);

 if(temperature < baselineTemp){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
 }else if(temperature >= baselineTemp+2 && temperature < baselineTemp+4){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
 }else if(temperature >= baselineTemp+4 && temperature < baselineTemp+6){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
 }else if(temperature >= baselineTemp+6){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
 }

 delay(1500);

}//loop
