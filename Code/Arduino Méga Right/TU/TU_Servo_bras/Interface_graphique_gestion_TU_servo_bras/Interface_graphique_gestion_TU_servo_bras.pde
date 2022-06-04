import controlP5.*;
import processing.serial.*;

Serial arduino;
ControlP5 Bicep;
ControlP5 Rotate;
ControlP5 Epaule;
ControlP5 Omoplate;


void setup()
{
  size(600,400);
  println(Serial.list());
  arduino = new Serial(this, Serial.list()[3], 115200);
  Bicep = new ControlP5(this);
  Rotate = new ControlP5(this);
  Epaule = new ControlP5(this);
  Omoplate = new ControlP5(this);
  
  Bicep.addSlider("Bicep")
    .setPosition(40,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Rotate.addSlider("Rotate")
    .setPosition(120,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Epaule.addSlider("Epaule")
    .setPosition(200,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Omoplate.addSlider("Omoplate")
    .setPosition(280,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
}
    
void draw()
{
  background(0,0,0);
}
    
void controlEvent(ControlEvent event)
{
  if(event.isController()) 
  {
    
  print("Evenement en provenance de: "+event.controller().getName());
  println(", valeur : "+event.controller().getValue());
  
     if(event.controller().getName()=="Bicep")
     {
       int val1 = int(event.getController().getValue());
       arduino.write("a" + val1);
     }
     
     if(event.controller().getName()=="Rotate")
     {
       int val2 = int(event.getController().getValue());
       arduino.write("b" + val2);  
    }
    
    if(event.controller().getName()=="Epaule")
     {
       int val3 = int(event.getController().getValue());
       arduino.write("c" + val3);  
    }
    
    if(event.controller().getName()=="Omoplate")
     {
       int val4 = int(event.getController().getValue());
       arduino.write("d" + val4);  
    }
  }
}
