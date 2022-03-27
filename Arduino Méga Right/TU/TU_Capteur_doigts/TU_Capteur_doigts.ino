/*
TU Capeur sensoriel main droite

Pouce : A14
Index : A13
Majeur: A12
Annu  : A11
Auri  : A10
*/

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(A14);
  Serial.println(sensorValue);
  delay(1);        
}
