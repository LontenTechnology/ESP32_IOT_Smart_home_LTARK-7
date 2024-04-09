import mfrc522
from os import uname
import time
from machine import Pin,PWM,I2C

pwm = PWM(Pin(13))
pwm.freq(50)
button1 = Pin(16, Pin.IN, Pin.PULL_UP)

#i2c config
rdr = mfrc522.MFRC522(18, 23, 19, 17, 5)
index = True
card_id=0
try:
    while True:
        btnVal1=button1.value()
        if(btnVal1 == 0):
            pwm.duty(25)
            print("close")
        (stat, tag_type) = rdr.request(rdr.REQIDL)
        if stat == rdr.OK:
            (stat, raw_uid) = rdr.anticoll()
            if stat == rdr.OK:
                print("Card UID: ")
                card_id="0x%02x%02x%02x%02x" % (raw_uid[0], raw_uid[1], raw_uid[2], raw_uid[3])
                print(card_id)
                if(card_id == "0xf3c66f1a"):
                    pwm.duty(128)
                    print("open")
                else:
                    print("error")
                card_id=0
                index = False
except KeyboardInterrupt:
    print("Bye")


