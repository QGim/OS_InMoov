
#define IN_AUDIO_ANALOG A3
int voice_value;

void setup() {
  Serial.begin(115200);
}

void loop() {
   voice_value = analogRead(IN_AUDIO_ANALOG);
  Serial.println(voice_value);
  delay(1);        
}
