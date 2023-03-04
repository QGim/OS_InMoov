#!/usr/bin/env python3.7
# -*- coding: utf-8 -*-
#Lancé dans autostart avec ShutD.sh
#Bouton appuyé au moins 3 Secondes
#Ventilateur en PWM
 
import os
import time
import RPi.GPIO as GPIO
from threading import Thread
 
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#Ventilateur sur GPIO18 en PWM à 10 Hz
pwm=18
GPIO.setup(pwm,GPIO.OUT,initial=GPIO.LOW)
fan=GPIO.PWM(pwm,10)

temp_ref=[40,45,53]
vit_ref=[70,80,100]

waitFAN=30

def Ventil():
	while True:
		temp = os.popen("vcgencmd measure_temp").readline()
		temp = temp.replace("temp=","")
		temp = int(float(temp.replace("'C","")))
		if temp < temp_ref[0]:
			fan.stop()
		else:
			fan.start(0)
			if temp < temp_ref[1] and temp >= temp_ref[0]:
				fan.ChangeDutyCycle(vit_ref[0])
				time.sleep(0.01)
				#print (str(temp) + " V1")
			elif temp < temp_ref[2] and temp >= temp_ref[1]:
				fan.ChangeDutyCycle(vit_ref[1])
				time.sleep(0.01)
				#print (str(temp) + " V2")
			else:
				fan.ChangeDutyCycle(vit_ref[2])
				time.sleep(0.01)
				#print (str(temp) + " V3")
		time.sleep(waitFAN)
 
	fan.stop()
	GPIO.cleaup()
try:
	t1= Thread(target = Ventil)
	t1.start()
except:
	t1.stop()
	GPIO.cleanup()
