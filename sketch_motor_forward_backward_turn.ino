/*
 * // This code has all the functions to drive the motor. 
 I didn't use the motor driver but the IC LM293D. So check the functions at the end to see how to make the robot move forward or back ward. turn left or right. stops. 
 the chip has 2 pins EN (see schematic)/ one for the left motor and one for the right motor. E1 and E2. If off the IC does not drive anymore more. free wheels.
 If they are HIGH the IC drives at full speed and  the pins I1 I2 I3 I4 that controll the direction of the motor. 
  EN1 and EN2 also control the speed of the motor. In that case, they need to connected to the pins PWM (like 10 and 11) and we can put 
   a number between 0 and 255. 255 is full speed. It does not seem to work wtih a number below 150.
   Vss must be connected to the 5V from arduino. It is to run the IC. It is a reference. I knows that 5V is HIGH  
   Vs is the power supply for the motor. It can be between 4.5V to 8V. I have 6V. 4 pins of the  IC are for the ground. 
   Capacitors have to be added. across the power the Vs and the Vss (100u). and across the motor (0.1u). 
   I1 I2 are to control the left motor. I3 I4 are to control the right motor. See functions at the end.
    Now interestingly. for a sharp left turn. left wheel when go back and right go forward. 
   for a regular left turn left stops and right moves forward.
 for a sharp right turn. right wheel go back and left moves. for a right turn. right stops and left moves. 

 I also changed to frequency of the PWM pins to 112Hz instead of 500 Hz. It seems to more the move smoother.
 see discussion in : http://coolkidsrobots.com/guide/changing-pwm-frequencies-arduino

 reference: 
  http://www.instructables.com/id/Control-your-motors-with-L293D-and-Arduino/?ALLSTEPS,
  http://hardwarefun.com/tutorials/creating-robots-using-arduino-h-bridge 
*/

#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2

#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2

byte speed=150;
// --------------------------------------------------------------------------- Setup
void setup() { 
 setPwmFrequency(E1,256); // this is to set the frequency of the PWM pins to 112Hz. 
 setPwmFrequency(E2,256); // see http://coolkidsrobots.com/guide/changing-pwm-frequencies-arduino for discussion
                          // the code is found in arduino website.
// Setup motors
 pinMode(E1, OUTPUT);
 pinMode(E2, OUTPUT);

pinMode(I1, OUTPUT);
pinMode(I2, OUTPUT);
pinMode(I3, OUTPUT);
pinMode(I4, OUTPUT);
analogWrite(E1,speed);
analogWrite(E2,speed);
}


// --------------------------------------------------------------------------- Loop
void loop() {
  // forward 
  // drive forward for 1s 
drive_forward();
delay(5000);
motor_stop();
delay(200);
//this is a very small turn because of 200
drive_backward();
delay(1000);
motor_stop();
delay(200);


 
}

// --------------------------------------------------------------------------- Drive

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
digitalWrite(I1, LOW);
digitalWrite(I2, LOW);

digitalWrite(I3, HIGH);
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
