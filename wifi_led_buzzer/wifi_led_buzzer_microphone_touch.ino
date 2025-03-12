#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "max_750_24"
#define STAPSK  "max93731051"
#endif

//about Touch
int touchPin = D7;
int touchVal = HIGH;

//about buzzer
int speakerPin = D6;
char notes[] = "ccggaagffeeddc ";
unsigned long beats[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int length = sizeof(notes);
int tempo = 300;
int isSing = 0;

//about sound detecter
int soundDetectedPin = D5; // Use Pin 10 as our Input
int soundDetectedVal = HIGH; // This is where we record our Sound Measurement
boolean bAlarm = false;
unsigned long lastSoundDetectTime;
int soundAlarmTime = 500;

//abotu wifi
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

//about LED light
const int led = D8;

String mainPanel =  "OK";
//String mainPanel = "test";
void handleRoot() {
  server.send(200, "text/html", mainPanel);
}

void handleNotFound() {
  //digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);


}

void setup(void) {

  //about Touch
  pinMode(touchPin, INPUT);

  //about buzzer
  pinMode(speakerPin, OUTPUT);

  //about sound detecter
  pinMode (soundDetectedPin, INPUT) ; // input from the Sound Detection Module

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  //about wifi
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");

  });

  server.on("/on", []() {
    digitalWrite(led, 1);
    server.send(200, "text/html", mainPanel);
  });

  server.on("/off", []() {
    digitalWrite(led, 0);
    server.send(200, "text/html", mainPanel);
  });

  server.on("/sing", []() {
    isSing = 1;
    String thisMainPanel = mainPanel;
    String thisArg0 = "";
    //melody
    for (uint8_t i = 0; i < server.args(); i++) {
      thisMainPanel += " " + server.argName(i) + ": " + thisArg0 + "\n";
      thisArg0 = server.arg(i) + " ";
      thisArg0.toCharArray(notes, 50);
      length = thisArg0.length();
    }

    server.send(200, "text/html", thisMainPanel);
  });

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();

  //about Touch
  touchVal = digitalRead (touchPin) ;
  if (touchVal == HIGH) // If we hear a sound
  {
    Serial.println("TOUCH");
    delay(500);
    
    isSing = 1;
    String thisArg0 ="aabb ";
    thisArg0.toCharArray(notes, 50);
    length = thisArg0.length();
  }

  //about sound detecter
  soundDetectedVal = digitalRead (soundDetectedPin) ; // read the sound alarm time

  if (soundDetectedVal == LOW) // If we hear a sound
  {

    lastSoundDetectTime = millis(); // record the time of the sound alarm
    // The following is so you don't scroll on the output screen
    if (!bAlarm) {

      Serial.println("LOUD, LOUD");
      delay(1000);

      String thisArg0 ="cd ";
      thisArg0.toCharArray(notes, 50);
      length = thisArg0.length();
      isSing = 1;
      bAlarm = true;
    }
  }
  else
  {
    if ( (millis() - lastSoundDetectTime) > soundAlarmTime  &&  bAlarm) {
      Serial.println("quiet");
      bAlarm = false;
    }
  }

  //about sing
  if (isSing == 1) {
    Serial.println("start melody");
    Serial.println(notes);
    Serial.println(length);
    for (int i = 0; i < length; i++) {
      //Serial.println(notes[i]);
      //Serial.println(beats[i]);
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(speakerPin, notes[i], beats[i] * tempo);
      }
      delay(tempo / 10);
    }
    isSing = 0;
  }

}

void playNote(int OutputPin, char note, unsigned long duration) {

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 261, 294, 330, 349, 392, 440, 494, 523 };
  // 播放音符對應的頻率
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      tone(OutputPin, tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}
