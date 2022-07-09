#include <Servo.h>

#define INPUT_ANALOGIC A3
#define ANGLE_BOUCHE_MIN 58
#define ANGLE_BOUCHE_MAX 145

#define AmpMax (1024 / 2)
#define MicSamples (1024*2)

long signalAvg = 0;
long signalMax = 0;
long signalMin = 1024;

int servo_angle = ANGLE_BOUCHE_MIN;

Servo test;

void setup()
{
  Serial.begin(115200);
  analogReference(DEFAULT);
  test.attach(6);
}

void loop()
{
  for (int i = 0; i < MicSamples; i++)
  {
    int k = analogRead(INPUT_ANALOGIC);
    signalAvg += k;
  }
  signalAvg /= MicSamples;
  signalMin = min(signalMin, signalAvg);
  signalMax = max(signalMax, signalAvg);
  Serial.print(" Avg: " + String(signalAvg));
  Serial.print(" Min: " + String(signalMin));
  Serial.println(" Max: " + String(signalMax));

 servo_angle =  map(signalAvg,signalMin,signalMax,ANGLE_BOUCHE_MIN,ANGLE_BOUCHE_MAX);

  Serial.println(" Angle Servo: " + String(servo_angle));

  test.write(servo_angle);
}
