/*
TU Capeur sensoriel main droite

Pouce : A14
Index : A13
Majeur: A12
Annu  : A11
Auri  : A10
Dispo : A9,A8
*/

#define NB_CAPTEURS 5

int ports_capteurs[NB_CAPTEURS] = {A4,A3,A2,A1,A0};
int value_capteurs[NB_CAPTEURS] = {};
int min_values[NB_CAPTEURS] = {50,50,50,50,50};
int max_values[NB_CAPTEURS] = {50,50,50,50,50};
String spacer = " : ";


void setup() {
  Serial.begin(115200); 
}

void loop() {
  for(int i = 0;i<NB_CAPTEURS;i++)
  {
     value_capteurs[i] = analogRead(ports_capteurs[i]);
  }
 
  Serial.println(value_capteurs[0] + spacer + value_capteurs[1] + spacer +  value_capteurs[2] + spacer + value_capteurs[3]+spacer+value_capteurs[4]);
  delay(1);        
}
