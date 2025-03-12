const int motorIn1 = 0;
const int motorIn2 =1;
int delaytime=500;
int val;
char ch='w';
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
}

void loop() {

   char ch = Serial.read();
 // Serial.println(ch); // 在 Serial

  if(ch == 'w'){
    Serial.println("直行"); // 在 Serial
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)

  }else if(ch == 's'){
    Serial.println("向後"); // 在 Serial
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
    digitalWrite(6, HIGH);    // turn the LED off by making the voltage LOW 
    digitalWrite(9, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)

  }else if(ch == 'a'){
    Serial.println("向左"); // 在 Serial
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(9, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)

  } else if(ch == 'd'){
    Serial.println("向右"); // 在 Serial
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
    digitalWrite(6, HIGH);    // turn the LED off by making the voltage LOW
    digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)

 } else if(ch == 'z'){ //left
    Serial.println("left"); // 在 Serial
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(9, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
 }

 else if(ch == 'x'){ //stop
    Serial.println("stop"); // 在 Serial
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(9, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
 }

 else if(ch == 'c'){ //right
    Serial.println("right"); // 在 Serial
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(9, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
 }

 ch='p';

}
