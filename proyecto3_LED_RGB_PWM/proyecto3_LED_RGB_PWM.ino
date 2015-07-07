//Pins del LED RGB
const int greenLEDPin = 9;
const int redLEDPin = 11;
const int blueLEDPin = 10;

//Pins de cada fotocélula
const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

//Variables valores entrada/salida
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup() {
  Serial.begin(9600);

  pinMode(greenLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);
}//Setup

void loop() {
  //leer datos de las células fotovoltáicas
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);

  //Imprimir valores en consola
  Serial.print("Raw Sensor Values \n\tRed: ");
  Serial.print(redSensorValue);
  Serial.print("\n\tGreen: ");
  Serial.print(greenSensorValue);
  Serial.print("\n\tBlue: ");
  Serial.print(blueSensorValue);

  //Dar valor para salida analógica para LED RGB (0-255)
  //Sacamos el valor analógico de color del sensor dividiendo entre 4
  redValue = redSensorValue/4;
  greenValue = greenSensorValue/4;
  blueValue = blueSensorValue/4;

  //Imprimir en consola los valores que se le van a dar al LED RGB
  Serial.print("Mapped Sensor Values \n\tRed: ");
  Serial.print(redValue);
  Serial.print("\n\tGreen: ");
  Serial.print(greenValue);
  Serial.print("\n\tBlue: ");
  Serial.print(blueValue);

  //Dar valores al LED RGB
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}//Loop
