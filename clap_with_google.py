import slowclap as sc
feed = sc.MicrophoneFeed()
import time

from win32com.client import constants
import win32com.client

import speech_recognition as sr
import pyaudio

detector = sc.AmplitudeDetector(feed, threshold=17000000)
lastTS = time.time() - 5


def askGoogle():
    r=sr.Recognizer()
    r.energy_threshold=4000
    
    with sr.Microphone() as source:
        audio=r.listen(source)

    try:
        #speaktext = #,language='zh-tw'
        print(r.recognize_google(audio))
        #print("Speech was:" + speaktext)
        #speaker.Speak(speaktext)
    except LookupError:
        print('Speech not understood')
        speaker.Speak("Speech not understood")


for clap in detector:
    nowTS = time.time()
    if nowTS - lastTS > 5:
        lastTS = nowTS
        print(lastTS)
        speaker = win32com.client.Dispatch("SAPI.SpVoice")
        speaker.Speak("what's matter?")
        print("speak your word")
        askGoogle()