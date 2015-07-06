/**
 * Pin 3 LED verde
 * Pin 4 LED azul
 * Pin 5 LED rojo
 */

int switchState = 0; //estado del Pin 2
void setup() {
  //configuramos los pines para salida o entrada
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  switchState = digitalRead(2); //Leer el estado del pin 2
  if (switchState == LOW){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }else{
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);

    delay(100);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(100);
  }

}
