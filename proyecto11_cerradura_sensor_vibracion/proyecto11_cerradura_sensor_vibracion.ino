#include <Servo.h>
Servo myServo;

const int piezo = 0;
const int switchPin = 2;
const int yellowLed = 3;
const int greenled = 4;
const int redLed = 5;

int knockVal;
int switchVal;

const int quietKnock =5;
const int loudKnock = 10;

boolean locked = false;
int numberOfKnocks = 0;

void setup() {
  myServo.attach(9);
  pinMode(yellowLed,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(switchPin,INPUT);

  Serial.begin(9600);

  digitalWrite(greenled,HIGH);
  myServo.write(5);
}//setup

void loop() {
  if (locked == false)
  {
  	switchVal = digitalRead(switchPin);

  	if (switchVal == HIGH)
  	{
  		locked = true;
  		digitalWrite(greenled,LOW);
  		digitalWrite(redLed,HIGH);
  		myServo.write(95);
  		delay(1000);
  	}
  }

  if (locked == true)
  {
  	knockVal = analogRead(piezo);

  	if (numberOfKnocks < 3 && knockVal > 0)
  	{
  		if (checkForKnock(knockVal) == true)
  		{
  			numberOfKnocks++;
  		}
  		Serial.print("Numero de golpes validos: ");
  		Serial.print(numberOfKnocks);
  	}

  	if (numberOfKnocks >=3)
  	{
  		locked = false;
  		myServo.write(5);
  		delay(20);
  		digitalWrite(greenled,HIGH);
  		digitalWrite(redLed,LOW);
     numberOfKnocks = 0;
  	}
  }
}

boolean checkForKnock(int value){
  
	if (value > quietKnock && value < loudKnock)
	{
		digitalWrite(yellowLed,HIGH);
		delay(50);
		digitalWrite(yellowLed,LOW);
		Serial.print("\nValor del sensor: ");
		Serial.print(value);
		return true;
	}else{
		Serial.print("\nNNNNNNNNNNNNNNNNNNNValor NO valido: ");
		Serial.print(value);
		return false;
	}
}
