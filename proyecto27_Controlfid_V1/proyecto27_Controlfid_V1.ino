/*
*	Libraries
*/
#include <SPI.h>
#include <RFID.h>
#include <Ethernet.h>

/*
*	Objects
*/
RFID rfid(7,9);
EthernetClient client;

/*
*	Arguments
*/
int ledVerde = 2;
int ledAmarillo = 3;
int ledRojo = 4;
String tarjeta = "";
String url = "";
String room = "9";
String respuesta = "";
int veces = 0;
boolean result;
byte mac[] = {
	0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
char server[] = "controlfid.zubirimanteoweb.com";


/*
*	Setup
*/
void setup()
{
  pinMode(ledVerde,OUTPUT);
  pinMode(ledAmarillo,OUTPUT);
  pinMode(ledRojo,OUTPUT);
	Serial.begin(9600);
	SPI.begin();
	rfid.init();
  digitalWrite(ledVerde,LOW);
  digitalWrite(ledAmarillo,LOW);
  digitalWrite(ledRojo,LOW);

	//Start Ethernet connection
	if(Ethernet.begin(mac) == 0){
	    Serial.println("Failed to configure Ethernet using DHCP");
	    for(;;)
	    	;
	}//if Ethernet.begin

	printIPAddress();


}//setup

/*
*	Loop
*/
void loop()
{
	if (rfid.isCard()) {
    digitalWrite(ledAmarillo,HIGH);
          if (rfid.readCardSerial()) { 
                 for(int i=0; i<=4; i++){
                     tarjeta+=String(rfid.serNum[i]);
                 }
                 rfid.halt();
                 if(client.connect(server,80)){
                     Serial.println("Connected successfull");
                     client.println("GET /presencia?idT="+tarjeta+"&time=08:00:00&room="+room+" HTTP/1.0");
                     client.println("Host: controlfid.zubirimanteoweb.com\r\n");
                     Serial.println("GET /presencia?idT="+tarjeta+"&time=08:00:00&room="+room);
                     delay(1000);
                     tarjeta="";
                     result = false;
                     respuesta = "";

                 }else{
                 	Serial.println("Connection failed");
                   digitalWrite(ledAmarillo,LOW);
                   digitalWrite(ledRojo,HIGH);
                   delay(1000);
                   digitalWrite(ledRojo,LOW);
                  tarjeta="";
                 }//if client.connect
          }
    }  
    

    if(client.available()){
        char c = client.read();
        Serial.print(c);
        if(c == '\n'){
        	veces+=1;
        }
        if(veces == 9){
          if(!result){
            if(c == 'o'){
              digitalWrite(ledAmarillo,LOW);
              digitalWrite(ledVerde,HIGH);
              Serial.println("Ha devuelto ok");
              result = true;
              client.stop();
              veces = 0;
              delay(1000);
              digitalWrite(ledVerde,LOW);
            }else if(c == 'k'){
              digitalWrite(ledAmarillo,LOW);
              digitalWrite(ledRojo,HIGH);
              Serial.println("Ha devuelto ko");
              result = true;
              client.stop();
              veces = 0;
              delay(1000);
              digitalWrite(ledRojo,LOW);
            }
          }
        }
    }




    /*
    *	Check
    */

	switch (Ethernet.maintain())
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");

      //print your local IP address:
      printIPAddress();
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");

      //print your local IP address:
      printIPAddress();
      break;

    default:
      //nothing happened
      break;

  }//Ethernet.maintain*/
}//loop


void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}//printIPAddress
