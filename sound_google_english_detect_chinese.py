import pyaudio
import speech_recognition as sr

r=sr.Recognizer()
#r.recognize_google(audio,language='zh-tw')
r.energy_threshold=4000

with sr.Microphone() as source:
   audio=r.listen(source)

try:
   print("Speech was:" + r.recognize_google(audio,language='zh-tw'))
except LookupError:
   print('Speech not understood')