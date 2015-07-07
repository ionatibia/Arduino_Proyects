const int switchPin = 8;

//Sin signo long de 0 hasta máximo, con signo, el máximo entre 2
unsigned long previousTime = 0;

int switchState = 0;
int prevSwitchState =0;

int led = 2;

long interval = 600000;

void setup() {
  for (int i = 2; i < 8; ++i)
  {
  	pinMode(i,OUTPUT);
  }

  pinMode(switchPin,INPUT);
}//setup

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime > interval)
  {
  	previousTime = currentTime;
  	digitalWrite(led, HIGH);
  	led++;

  	if (led == 7)
  	{
  		while(millis() < 10000){
  			tone(12,262);		
  		}
  	}
  }//if

  switchState = digitalRead(switchPin);

  if(switchState != prevSwitchState){
  	for (int x = 2; x < 8; x++)
  	{
  		digitalWrite(x,LOW);
  	}
  	led = 2;
  	previousTime = currentTime;
  }//if

  prevSwitchState = switchState;
}//loop