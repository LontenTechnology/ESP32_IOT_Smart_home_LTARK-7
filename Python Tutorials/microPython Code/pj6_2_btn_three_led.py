from machine import PWM,Pin
import time

button1 = Pin(16, Pin.IN, Pin.PULL_UP)
button2 = Pin(4, Pin.IN, Pin.PULL_UP)
count = 0

#Define the number of pin and LEDs
red_pin = PWM(Pin(14))
green_pin = PWM(Pin(27))
blue_pin = PWM(Pin(15))

#Nest two for loops to make the module repeatedly display five states of red, green, blue, white and OFF.    
while True:
    btnVal1 = button1.value()  # Reads the value of button 1
    #print("button1 =",btnVal1)  #Print it out in the shell
    if(btnVal1 == 0):
        time.sleep(0.01)
        while(btnVal1 == 0):
            btnVal1 = button1.value()
            if(btnVal1 == 1):
                if(count <= 0):
                    count = 0
                else:
                    count = count - 1
                print(count)
    btnVal2 = button2.value()        
    if(btnVal2 == 0):
        time.sleep(0.01)
        while(btnVal2 == 0):
            btnVal2 = button2.value()
            if(btnVal2 == 1):
                count = count + 1
                if(count >= 4):
                    count = 4
                print(count)
    if(count == 0):
        red_pin.duty(0)
        green_pin.duty(0)
        blue_pin.duty(0)
    elif(count == 1):
        red_pin.duty(100)
        green_pin.duty(0)
        blue_pin.duty(0)
    elif(count == 2):
        red_pin.duty(0)
        green_pin.duty(100)
        blue_pin.duty(0)
    elif(count == 3):
        red_pin.duty(0)
        green_pin.duty(0)
        blue_pin.duty(100)
    elif(count == 4):
        red_pin.duty(100)
        green_pin.duty(100)
        blue_pin.duty(100)



