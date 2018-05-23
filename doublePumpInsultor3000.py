import platform
import serial
from random import randint

isWindows = platform.system() == "Windows"

insults = [
    "FUCK",
    "FUCK, damn snipers!",
    "BITCH ASS MOTHERFUCKER",
    "EAT DIRT SCUMBAG"
]

if(isWindows):
    print("loaded windows setup")
    from win32com.client import Dispatch
    speak = Dispatch("SAPI.SpVoice")
else:
    print("loaded darwin setup...")
    from os import system

def insult():
    text = insults[randint(0,len(insults)-1)]
    print("saying: " + text)

    if(isWindows):
        speak.Speak(text)
    else:
        system('say '+ text)


s = serial.Serial(port='/dev/cu.usbmodemHIDP1', baudrate=9600)


while True:
    try:
        input = s.readline()
        insult()
    except KeyboardInterrupt:
        print("Stopping...")
        s.close()