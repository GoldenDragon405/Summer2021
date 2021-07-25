from threading import Thread
import time
import RPi.GPIO as GPIO
#time.sleep(30)
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
TRIG = 17  
ECHO = 27
x = 1
i = 0
GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)

def frontMotionThread0():
    while True:
        time.sleep(0.1)        
        GPIO.output(TRIG, True)
        time.sleep(0.00001)
        GPIO.output(TRIG, False)    

        while GPIO.input(ECHO)==0:
            pulse_start = time.time()

        while GPIO.input(ECHO)==1:
            pulse_end = time.time()

        pulse_duration = pulse_end - pulse_start
        distance =  pulse_duration * 17150
        distance = round(distance)
        print (distance)
        global x
        if distance <= 25:
            x = 0
        else:
            x = 1
            pass
        
def motor(): 
    GPIO.setup(25,GPIO.OUT)
    global p 
    p = GPIO.PWM(25,207)
    p.start(0)
    p.ChangeDutyCycle(100)    

def stopMotor():
    p.stop()    

def backMotor(): 
    GPIO.setup(16,GPIO.OUT)
    global t
    t = GPIO.PWM(16,207)
    t.start(0)
    t.ChangeDutyCycle(100)
def stopBackMotor():
    t.stop()
global motorcounter
motorcounter = 0   
def killcode():
    if motorcounter == 1:
        stopMotor()
    if motorcounter == 2:
        stopBackMotor()
    GPIO.cleanup()
    exit()
def codekillerthread0():
    while True:
        if x == 0:
            killcode()
        else:
            pass

for i in range(1):       
    Thread(target=frontMotionThread0).start()
    Thread(target=codekillerthread0).start()

try:
    while True :
        motorcounter = 1
        motor()
        time.sleep(1)
        stopMotor()
        backMotor()
        motorcounter = 2
        time.sleep(2.25)
        stopBackMotor()
        motor()
        motorcounter = 1
        time.sleep(1)
        #i = i+1
        
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
