from machine import PWM,Pin
import time

#Define the number of pin and LEDs
red_pin = PWM(Pin(14))
green_pin = PWM(Pin(27))
blue_pin = PWM(Pin(15))

#Nest two for loops to make the module repeatedly display five states of red, green, blue, white and OFF.    
while True:
    #red
    red_pin.duty(100)
    green_pin.duty(0)
    blue_pin.duty(0)
    time.sleep_ms(500)
    #green
    red_pin.duty(0)
    green_pin.duty(100)
    blue_pin.duty(0)
    time.sleep_ms(500)
    #blue
    red_pin.duty(0)
    green_pin.duty(0)
    blue_pin.duty(100)
    time.sleep_ms(500)
    #white
    red_pin.duty(100)
    green_pin.duty(100)
    blue_pin.duty(100)
    time.sleep_ms(500)
    #close
    red_pin.duty(0)
    green_pin.duty(0)
    blue_pin.duty(0)
    time.sleep_ms(500)
