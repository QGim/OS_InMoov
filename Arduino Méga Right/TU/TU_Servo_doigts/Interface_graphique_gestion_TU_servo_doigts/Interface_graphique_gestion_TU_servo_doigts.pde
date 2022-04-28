import controlP5.*;
import processing.serial.*;

Serial arduino;
ControlP5 Pouce;
ControlP5 Index;
ControlP5 Majeur;
ControlP5 Annu;
ControlP5 Auri;
ControlP5 Poignet;

void setup()
{
  size(600,400);
  println(Serial.list());
  arduino = new Serial(this, Serial.list()[3], 9600);
  Pouce = new ControlP5(this);
  Index = new ControlP5(this);
  Majeur = new ControlP5(this);
  Annu = new ControlP5(this);
  Auri = new ControlP5(this);
  Poignet = new ControlP5(this);
  
  Pouce.addSlider("Pouce")
    .setPosition(40,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Index.addSlider("Index")
    .setPosition(120,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Majeur.addSlider("Majeur")
    .setPosition(200,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Annu.addSlider("Annu")
    .setPosition(280,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Auri.addSlider("Auri")
    .setPosition(360,40)
    .setSize(50,250)
    .setRange(0,180)
    .setValue(90)
    .setColorBackground(color(0,0,255))
    .setColorForeground(color(0,255,0))
    .setColorValue(color(255,255,255))
    .setColorActive(color(255,0,0))
    ;
    
    Poignet.addSlider("Poignet")
    .setPosition(440,40)
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
  
     if(event.controller().getName()=="Pouce")
     {
       int val1 = int(event.getController().getValue());
       println("a:" + val1);
       arduino.write("a" + val1);
     }
     
     if(event.controller().getName()=="Index")
     {
       int val2 = int(event.getController().getValue());
       arduino.write("b" + val2);  
    }
    
    if(event.controller().getName()=="Majeur")
     {
       int val3 = int(event.getController().getValue());
       arduino.write("c" + val3);  
    }
    
    if(event.controller().getName()=="Annu")
     {
       int val4 = int(event.getController().getValue());
       arduino.write("d" + val4);  
    }
    
    if(event.controller().getName()=="Auri")
     {
       int val5 = int(event.getController().getValue());
       arduino.write("e" + val5);  
    }
    
    if(event.controller().getName()=="Poignet")
     {
       int val6 = int(event.getController().getValue());
       arduino.write("f" + val6);  
    }
  }
}
