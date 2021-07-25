from threading import Thread
import time
import RPi.GPIO as GPIO
#import queue

#GPIO.cleanup()

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

TRIG = 17
ECHO = 27
LTRIG = 6
LECHO = 13
GPIO.setup(LTRIG,GPIO.OUT)
GPIO.setup(LECHO,GPIO.IN)
GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)
#GPIO.output(TRIG, False)
IsMotorRunning = False
isLeftMotorRunning = False
leftTurnCounter = 0

safeDistance = 15

# Front distance sensor
def frontMotionThread0(i): 
    
    #print ('working')
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
    distance = round(distance, 2)
    #q.put(distance)
    #print(distance)
    #print (distance)

    return distance

# Front distance sensor
def leftMotionThread1(i): 
    
    #print ('working')
    time.sleep(0.1)        
    GPIO.output(LTRIG, True)
    time.sleep(0.00001)
    GPIO.output(LTRIG, False)    

    while GPIO.input(LECHO)==0:
        pulse_start = time.time()

    while GPIO.input(LECHO)==1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance =  pulse_duration * 17150
    distance = round(distance, 2)
    #q.put(distance)
    #print(distance)
    #print (distance)

    return distance

'''
# light sensor
def lightSensorThread1(j):
    level =0 
    #print('Thread started')
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(pin_to_c, GPIO.OUT)
    GPIO.output(pin_to_c, GPIO.LOW)
    time.sleep(0.1)
    GPIO.setup(pin_to_c, GPIO.IN)
    while (GPIO.input(pin_to_c) == GPIO.LOW):
        level+= 1           
    return level
'''
def leftMotor():    
    GPIO.setup(25,GPIO.OUT)
    GPIO.output(25,GPIO.HIGH)
    
def stopLeftMotor():
    GPIO.output(25,GPIO.LOW)


def motor(): 
    GPIO.setup(23,GPIO.OUT)
    GPIO.output(23,GPIO.HIGH)    

def stopMotor():
    GPIO.output(23,GPIO.LOW)    

def rightMotor():    
    GPIO.setup(16,GPIO.OUT)
    GPIO.output(16,GPIO.HIGH)
    
def stopRightMotor():
    GPIO.output(16,GPIO.LOW)

# program start from here
# do not use
#myQueue = queue.Queue()
#t0 = Thread(target=frontMotorThread0(myQueue), daemon=True)      # argument is first parameter to target function
#t0.start()
#t0.join()

for i in range(2):
    if i== 0:
       #time.sleep(1)       
       t0 = Thread(target=frontMotionThread0, args=(i)).start()      # argument is first parameter to target function
       #t0.join()
    elif i== 1:
       #time.sleep(1)       
       t1 = Thread(target=leftMotionThread1, args=(i)).start()      # argument is first parameter to target function
       #t0.join()
        
    #elif i==1:
     #   t1 = Thread(target=lightSensorThread1, args=(i,))  # argument is first parameter to target function
      #  t1.start()
    else:
        print('out of thread')


'''    
for j in range(1):
    p = Thread(target=lightSensorThread2, args=(j,))  # argument is first parameter to target function
    p.start()
'''


#super  important code, control     
try:
    while True:
        #print(frontMotorThread0(0))
        #print(i)
        #myQueue.task_done()
        #print(frontMotorThread0(0))
        #print(myQueue.get())
        
        #print(frontMotionThread0(0) )
        #print(leftMotionThread1(1) )
        
        if frontMotionThread0(0) == 0:
            print('Starting')
        elif frontMotionThread0(0) >= safeDistance:
            if isLeftMotorRunning:
                stopLeftMotor()
                isLeftMotorRunning = False
                print('Left motor stop')
                motor()
                IsMotorRunning = True
            else:
                motor()
                IsMotorRunning = True
        
        elif frontMotionThread0(0) < safeDistance:
            
            if IsMotorRunning:
                if not isLeftMotorRunning:
                    stopMotor()
                    IsMotorRunning = False
                else:
                    motor()
                    IsMotorRunning = True
            elif isLeftMotorRunning:   # left moter is running
                    motor()
                    IsMotorRunning = True
            else:
                pass
            
                     
            if leftMotionThread1(1) >= safeDistance:
                leftMotor()
                isLeftMotorRunning = True
                print("leftmotor")
        
        '''
                elif leftMotionThread1(1) < safeDistance:
                    stopLeftMotor()
                    isLeftMotorRunning = False
                    print("stopleftmotor")
                '''
                
            #break        
        #print(i , IsMotorRunning)
        #i = i + 1
        
        '''
        while (lightSensorThread0(1) >= 0 ) or (lightSensorThread1(1) >= 0):
                #print (lightSensorThread(1))
                #motor()
                #stopMotor()
            
            if lightSensorThread0(1) >= 100:
                motor()            
            else: #lightSensorThread0(1) <100:
                stopMotor()
            
            if lightSensorThread1(1) < 1:
                rightMotor()            
            else: #lightSensorThread1(1) <= 1: 
                stopRightMotor()
           '''     
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
    
    
