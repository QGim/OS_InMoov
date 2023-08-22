/*
TU Capeur sensoriel main droite

Pouce : A14
Index : A13
Majeur: A12
Annu  : A11
Auri  : A10
*/

#define Hall_Sensor_Pin A13

void setup() {
  pinMode(Hall_Sensor_Pin,INPUT);
  Serial.begin(9600);
}

void loop() {
  float voltage;
  voltage = analogRead(Hall_Sensor_Pin);
  Serial.println(voltage);
  delay(50);
}
