
/*#define IN_AUDIO_ANALOG A3
int voice_value;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(115200);
}

void loop() {
   voice_value = analogRead(IN_AUDIO_ANALOG);
  Serial.println(voice_value);
  delay(1);        
}*/


// HARDWARE MOUTHCONTROL
//
// dedicated arduino
// Read voltage value from speaker and move jaw
// First POC version, need to be calibrated and fixed :
// If you want test it please read Analog values when you have NO SOUND and enter MIN , min is the value when robot speak
// I use AREF 1 volt and sound come from unamplified jack, from PC
//
// To do : 
// Webkit : shutdown microphone when speak

#include <Servo.h> 
#define servoPin      6
#define HPpin         A3    // analog speaker input

Servo myservo;                 

int     MIN = 400; //value when sound is detected
int     MAX = 1000;  //max value when sound is detected
int     SecondDetection = 2; 
int     val = 0;    
int     i = 0;
int     posMax = 145;    
int     posMin = 65;
int     pos = posMin;
int     BoucheStatus = 0;
int     ActionBouche = 0;
int     Repos = 0;
int     CompteurRepos = 0;
String  dbg;

void setup() 
{ 
      
  analogReference(INTERNAL);
  //Serial.begin(9600);  
  //Serial.println("--- Start DEBUG ---");
  myservo.attach(servoPin);
  myservo.write(posMin);
} 
 
void loop()  
{ 
   val = analogRead(HPpin);
   pos=map(val, MIN, MAX, posMin, posMax); 
  
if (val > MIN ) // if values detected : speaker voltage
  
     {
     i++;
     }
     else  
     {
     BoucheStatus = 1; // closed mouth
     }
  
     if (i>=SecondDetection)
      {
       i=0;
       BoucheStatus = 0;
      }

      if (BoucheStatus == 0 && ActionBouche == 0)

      {
           if (Repos==0)
        {
        //myservo.attach(servoPin);
        delay(1);
        }
      Serial.println(val);
      ActionBouche = 1;
      myservo.write(pos);
      CompteurRepos=0;
      delay(1);
      
      }
      if (BoucheStatus == 1 && ActionBouche == 1)
      {
       
       Repos = 0;
       CompteurRepos = 0;
       ActionBouche =0;
      
      }

      if (CompteurRepos == 100 && Repos == 0)
      {
       myservo.write(posMin); 
      // myservo.detach(); 
       Repos=1;
      }

CompteurRepos+=1;    
delay(1);
 
}
