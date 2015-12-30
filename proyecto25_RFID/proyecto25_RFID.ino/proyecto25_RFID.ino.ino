#include <SPI.h>
#include <RFID.h>

RFID rfid(10,9);
String tarjeta = "";

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init(); 
  
}

void loop()
{ 
    if (rfid.isCard()) {
          if (rfid.readCardSerial()) { 
                 for(int i=0; i<=4; i++){
                     tarjeta+=String(rfid.serNum[i]);
                 }
                 Serial.println("GET /presencia?idT="+tarjeta+"&time=08:00:00&room=101 HTTP/1.0");
                 tarjeta = "";
                 delay(1000);
          }
    }  
    rfid.halt();
}
