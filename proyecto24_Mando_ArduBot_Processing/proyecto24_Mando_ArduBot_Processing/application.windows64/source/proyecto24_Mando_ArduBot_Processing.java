import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class proyecto24_Mando_ArduBot_Processing extends PApplet {



Serial myPort;

public void setup(){
 println(Serial.list()); 
 myPort = new Serial(this,Serial.list()[3],9600);
}

public void draw(){
  
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "proyecto24_Mando_ArduBot_Processing" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
