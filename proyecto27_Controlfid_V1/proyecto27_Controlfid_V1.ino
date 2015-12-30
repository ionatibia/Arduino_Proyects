/*
*	Libraries
*/
#include <SPI.h>
#include <RFID.h>
#include <Ethernet.h>

/*
*	Objects
*/
RFID rfid(10,9);
EthernetClient client;

/*
*	Arguments
*/
String tarjeta = "";
String result = "";
String url = "";
String room = "101";
int veces = 0;
byte mac[] = {
	0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
char server[] = "controlfid.zubirimanteoweb.com";

/*
*	Setup
*/
void setup()
{
	Serial.begin(9600);
	SPI.begin();
	rfid.init();

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
          if (rfid.readCardSerial()) { 
                 for(int i=0; i<=4; i++){
                     tarjeta+=String(rfid.serNum[i]);
                 }
                 if(client.connect(server,80)){
                     Serial.println("Connected successfull");
                     client.println("GET /presencia?idT="+tarjeta+"&time=08:00:00&room="+room);
                     client.println("Host: controlfid.zubirimanteoweb.com\r\n");
                     Serial.println("GET /presencia?idT="+tarjeta+"&time=08:00:00&room="+room);
                     delay(1000);
                     tarjeta="";

                 }else{
                 	Serial.println("Connection failed");
                 }//if client.connect
          }
    }  
    rfid.halt();

    if(client.available()){
        char c = client.read();
        Serial.print(c);
        if(c == '\n'){
        	veces+=1;
        }
        if(veces == 9){
            if(c == 'o'){
           		Serial.println("Ha devuelto ok");
			}else if(c == 'k'){
           		Serial.println("Ha devuelto ko");
        	}
        }
    }




    /*
    *	Check
    */
	  // if the server's disconnected, stop the client:
	if (!client.connected()) {
    	Serial.println();
    	Serial.println("disconnecting.");
    	client.stop();
    // do nothing forevermore:
    while (true);
  	}//if !client.connected()

/*	switch (Ethernet.maintain())
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