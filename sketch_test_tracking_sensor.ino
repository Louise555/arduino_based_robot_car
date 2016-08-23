/*
We will try one sensor at a time. 

product from: 
http://www.elabpeers.com
All rights reserved.
See their great website to see a similar code but used with a comparator.



Wiring:
1.  VCC to 5V pin on Arduino
2.  GND to GND on Arduino
3. A1 to sig

*/

const int IR1Pin = A1; 
void setup()
{
  Serial.begin (9600);
  pinMode(IR1Pin, INPUT); // set IR1Pin as input
}

void loop()
{
  IRRead();
  delay(1000);
}

void IRRead()
{
  float IR1PinValue = 5.*analogRead(IR1Pin)/1024.; //set the reading of IR1Pin as IR1PinValue
  Serial.print("IR1Pin :");
  Serial.println(IR1PinValue);
}
