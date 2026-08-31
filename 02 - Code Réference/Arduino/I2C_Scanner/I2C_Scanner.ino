#include <Wire.h>
// NE PAS OUBLIER LES 2 RESISTANCES DE 4,7KOHMS ENTRE SDA ET +5V ET ENTRE SLC ET +5V 
 
void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.print("Scanning");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // La valeur de retour de Wire.endTransmission() 
    // est false (0) si le peripherique existe a cette adresse
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    Serial.print(".");
 
    if (error == 0)
    {
      Serial.println(""); 
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !"); 
      nDevices++;
      break; // commenter cette ligne si plusieurs peripheriques I2C coexistent sur le bus
             // sinon le test s'arrete des le premier trouve
    }
    else if (error==4)
    {
      Serial.println(""); 
      Serial.print("Unknow error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }  
    delay(50);
  }
  if (nDevices == 0)
  {
    Serial.println(""); 
    Serial.println("No I2C devices found\n");
  }
  else
    Serial.println("done\n");
 
  delay(3000);           // on attend 3 secondes et on recommence
}
