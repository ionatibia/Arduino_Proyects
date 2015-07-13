 #include <SoftwareSerial.h>
 #include <Servo.h>
 Servo myServo;
char rec;
SoftwareSerial blue(2,3);//tx, rx
void setup(){
  myServo.attach(11);
  myServo.write(90);
  pinMode(13,OUTPUT);
  blue.begin(9600);
  blue.println("Conectado");
}
void loop() {
  if(blue.available()){
    rec=blue.read();
    switch(rec){
      case '0':
        digitalWrite(13,LOW);
        delay(500);
        blue.println("Led off");
        myServo.write(5);
        delay(500);
        break;
      case '1':
        digitalWrite(13,HIGH);
        delay(500);
        blue.println("Led on");
        myServo.write(175);
        delay(500);
        break;
      default:
        delay(500);
        blue.print(rec);
        blue.println(" no es una orden valida. Introduzca 0 o 1");
        myServo.write(90);
        delay(500);
    }
  }
}
