#include <Ultrasonic.h>
#include <Servo.h>

Ultrasonic ultrasonic(5,4); // (Trig PIN,Echo PIN)
Servo myServo;
int angle = 90;
int distancia;

void setup() {
  Serial.begin(9600); 
  myServo.attach(11);
  myServo.write(90);
}

void loop()
{
  distancia = ultrasonic.Ranging(CM);
  Serial.print(ultrasonic.Ranging(CM)); // CM or INC
  Serial.println(" cm" );
  if(distancia < 15){
    if(angle == 90){
      myServo.write(175);
      angle = 175;
    }else if(angle == 175){
      myServo.write(5);
      angle = 5;
    }else if(angle == 5){
      myServo.write(90);
      angle = 90;
    }
  }
  Serial.println(angle);
  delay(100);
}
