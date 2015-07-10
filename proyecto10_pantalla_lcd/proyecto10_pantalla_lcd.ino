//importar librería de pantalla LCD
#include <LiquidCrystal.h>

//Crear objeto de tipo LiquidCerystal(pines a utilizar)
LiquidCrystal lcd(12,11,5,4,3,2);

//variables y constantes
const int switchPin = 6;

int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
	//configurar tipo de pantalla. 16 columnas 2 filas
  lcd.begin(16,2);
  pinMode(switchPin,INPUT);
  //definir la posición del cursor
  lcd.setCursor(0,0);
  //hacer que el cursor parpadee
  lcd.blink();
  //array de char con una frase
  char caracteres[25] = "Hola esto es un programa";
  //mostrar 1 por 1 todos los char de la frase con 0,5 seg de retraso
  for(int x = 0; x < 24; x++){
    //si ha escrito 15 caracteres, scroll hacia la derecha
    //mueve la pantalla hacia la izquierda para ver los char de la derecha
    if(x > 15){
      lcd.scrollDisplayLeft();
    }
    lcd.print(caracteres[x]);
    delay(500); 
  }
  //quitar el parpadeo
  lcd.noBlink();
  //limpiar la pantalla
  lcd.clear();
  //definir la posición del cursor
  lcd.setCursor(0,0);
  
  lcd.print("Ke ladras?");
  lcd.setCursor(0,1);
  lcd.print("Pregunta algo...");
}//setup

void loop() {
  switchState = digitalRead(switchPin);

  if (switchState != prevSwitchState)
  {
  	if (switchState == LOW)
  	{
  		reply = random(8);
  		lcd.clear();
  		lcd.setCursor(0,0);
  		lcd.print("La respuesta:");
  		lcd.setCursor(0,1);
     lcd.blink();
     delay(3000);
     lcd.noBlink();

  		switch(reply){
  			case 0:
  				lcd.print("Si");
  				break;
  			case 1:
  				lcd.print("Probablemente");
  				break;
  			case 2:
  				lcd.print("Desde luego");
  				break;
  			case 3:
  				lcd.print("Tiene buena pinta");
  				break;
  			case 4:
  				lcd.print("No estoy seguro");
  				break;
  			case 5:
  				lcd.print("Vuelve a preguntar");
  				break;
  			case 6:
  				lcd.print("Tengo dudas");
  				break;
  			case 7:
  				lcd.print("No");
  				break;
  		}
  	}
  }
  prevSwitchState = switchState;

}
