import sys
from win32com.client import constants
import win32com.client
speaker = win32com.client.Dispatch("SAPI.SpVoice")
speaker.Speak("你們")
while 1:
	try:
		s = input('put your world here!')
		if s == "exit speaker":
			break
		speaker.Speak(s)
	except:
		if sys.exc_type is EOFError:
			sys.exit()
