import controlP5.*;
import processing.serial.*;

Serial ardu_port;
ControlP5 control;

void setup()
{
  size(500,500);
  ardu_port = new Serial(this,"COM15",115200);
  control = new ControlP5(this);
  
  control.addSlider("Pouce")
    .setPosition(125,20)
    .setSize(50,250)
    .setRange(0,255)
    .setValue(125)
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

void Pouce(int value)
{
  ardu_port.write(value);
}
