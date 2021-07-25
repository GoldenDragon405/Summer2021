# import required packages

from gpiozero import LED,RGBLED,Button
import time
import os
import sys


# define variable for LED
ledR = LED(16)
ledY = LED(20)
ledG = LED(21)
RGB = RGBLED(22,27,17)
btn = Button(26)


# main street lights function
# it runs continuously unless interpted 
def runlights():
    # walking light
    RGB.color = (1,0,0)
    # car lights
    ledR.off()
    ledG.on()
    time.sleep(4)
    ledG.off()
    ledY.on()
    time.sleep(2)
    ledY.off()
    ledR.on()
    time.sleep(4)
# end of main light function

# setting up global variables which required for both functions to work together    
def safecrossing():
    global pedestrian
    pedestrian = True
    
# once button is pressed for walking, the below function will kick off

def allowpedestrian():
    y = ('you may cross')
    #print (y)
    y = y.replace(" ","_")
    os.system(tts_engine + ' ' + y)
    # walking light set to green
    RGB.color = (0,1,0)
    time.sleep(3)
    
    x = ('hurry up cars are coming')
    print (x)
    x = x.replace(" ","_")
    os.system(tts_engine + ' ' + x)
    RGB.color = (0,0,0)
    time.sleep(0.5)
    RGB.color = (1,0,0)
    time.sleep(0.5)
    
btn.when_pressed = safecrossing

cnt = 0

while cnt <= 5: #True:
    pedestrian = False
    runlights()
    if pedestrian == True:
        allowpedestrian()
    cnt = cnt + 1