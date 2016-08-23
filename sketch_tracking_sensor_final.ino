/*
 * Sketch for the line follower robot. Was midofoed from the code found on website of http://www.elabpeers.com

Test code for 4-Channel IR Sensor
by eLab Peers (C) 2015.

Visit us at:
http://www.elabpeers.com

All rights reserved.

Lab 4 - 4-Channel IR Sensor

Arduino Pins:
1.  Pin A1 to Sig1 (left IR sensor next to left motor)
2.  Pin A2 to Sig2 (middle left)
3.  Pin A3 to Sig3 (middle right)
4.  Pin A4 to Sig4 (right sensor)


 VCC to 5V pin on Arduino
GND to GND on Arduino

*/

const int IR1Pin = A1; // left IR sensor
const int IR2Pin = A2; // the middle left IR sensor
const int IR3Pin = A3; //  the middle right IR sensor
const int IR4Pin = A4; // the right IR sensor

// pins for motor
#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2

#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
byte speed=255; // spin motor

void setup()
{
 setPwmFrequency(E1,256); // this is to set the frequency of the PWM pins to 112Hz. 
 setPwmFrequency(E2,256); // see http://coolkidsrobots.com/guide/changing-pwm-frequencies-arduino for discussion
                          // the code is found in arduino website.
  Serial.begin (9600);
  
  pinMode(IR1Pin, INPUT); // set IR1Pin as input
  pinMode(IR2Pin, INPUT); // set IR2Pin as input
  pinMode(IR3Pin, INPUT); // set IR3Pin as input
  pinMode(IR4Pin, INPUT); // set IR4Pin as input
  //motor

pinMode(E1, OUTPUT);
pinMode(E2, OUTPUT);

pinMode(I1, OUTPUT);
pinMode(I2, OUTPUT);
pinMode(I3, OUTPUT);
pinMode(I4, OUTPUT);
analogWrite(E1,speed);
analogWrite(E2,speed);
  
}

void loop()
{
  
  IRRead();

}

void IRRead()
{

  
  float IR1PinValue = 5.*analogRead(IR1Pin)/1024.; //set the reading of IR1Pin as IR1PinValue
  Serial.print("IR1Pin :");
  Serial.println(IR1PinValue);

  float IR2PinValue = 5.*analogRead(IR2Pin)/1024.; //set the reading of IR2Pin as IR2PinValue
  Serial.print("IR2Pin :");
  Serial.println(IR2PinValue);  

  float IR3PinValue = 5.*analogRead(IR3Pin)/1024.; //set the reading of IR3Pin as IR3PinValue
  Serial.print("IR3Pin :");
  Serial.println(IR3PinValue);  

  float IR4PinValue = 5.*analogRead(IR4Pin)/1024.; //set the reading of IR4Pin as IR4PinValue
  Serial.print("IR4Pin :");
  Serial.println(IR4PinValue);



// It depends on the floor. for m3  <1. is black and >4 is floor

  if (IR1PinValue <2 && IR2PinValue >4 && IR3PinValue >4&& IR4PinValue >4) //
  {
    turn_left();
    Serial.println("Sharp Left Turn");

  }
  else if (IR1PinValue <2 && IR2PinValue <2 && IR3PinValue>4 && IR4PinValue >4)
  {
    turn_left();
    Serial.println("Left Turn");

  }
  else if (IR1PinValue >4 && IR2PinValue <2 && IR3PinValue >4 && IR4PinValue >4)
  {
    Serial.println("Left Turn");
    turn_left();

  }
    else if (IR1PinValue >4 && IR2PinValue >4 && IR3PinValue <2 && IR4PinValue >4)
  {
    turn_right();
    Serial.println("Right Turn");

  }
    else if (IR1PinValue >4 && IR2PinValue >4 && IR3PinValue <2 && IR4PinValue <2)
  {
    turn_right();
    Serial.println("Right Turn");

  }
  else if (IR1PinValue >4 && IR2PinValue >4 && IR3PinValue >4 && IR4PinValue < 2)
  {
    turn_right();
    Serial.println("Sharp Right Turn");

  }
  else 
  {
    drive_forward();
    Serial.println("Forward");
    delay(100);
    motor_stop();
    delay(100);

  }


}

void motor_stop(){
digitalWrite(I1, LOW);
digitalWrite(I2, LOW);

digitalWrite(I3, LOW);
digitalWrite(I4, LOW);
delay(25);
}

void drive_forward(){

digitalWrite(I1, HIGH); // left motor
digitalWrite(I2, LOW);

digitalWrite(I3, HIGH);//rightmotor
digitalWrite(I4, LOW);
}

void drive_backward(){
digitalWrite(I1, LOW);
digitalWrite(I2, HIGH);

digitalWrite(I3, LOW);
digitalWrite(I4, HIGH);
}

void turn_left() {
 digitalWrite(I1, LOW);
digitalWrite(I2, LOW);

digitalWrite(I3, HIGH);
digitalWrite(I4, LOW); 
  
  }

void sharp_turn_left(){
digitalWrite(I1, LOW);
digitalWrite(I2, HIGH);

digitalWrite(I3, HIGH);
digitalWrite(I4, LOW);
}
// the right wheel go backward
void sharp_turn_right(){
digitalWrite(I1, HIGH);
digitalWrite(I2, LOW);

digitalWrite(I3, LOW);
digitalWrite(I4, HIGH);
}
// left  wheel stops
void turn_right(){
digitalWrite(I1, HIGH);
digitalWrite(I2, LOW);

digitalWrite(I3, LOW);
digitalWrite(I4, LOW);
  }
  /**
 * Divides a given PWM pin frequency by a divisor.
 *
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 *
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 *
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 *
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://forum.arduino.cc/index.php?topic=16612#msg121031
 */
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
