
/* Robot with to work with an ultrasonic sensor. If it gets close to an obstacle, it moves back and turn left .
 * See the sektc to test the sensor ultrasound first.
 *  
 */
#define E1 10  // Enable Pin for motor 1  - we will use the analogWrite to control speed so we need 10 and 11
#define E2 11  // Enable Pin for motor 2  - because you can write analog output using PWM technique. analogWRite() takes a number between 0 and 255
                                    //      255 is for 5V so full speed. 0 is free wheel/ 

#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
#define trigPin  7 // pin "trig" digital  7 Arduino
#define echoPin  6  //pin "echo" digital 6  Arduino

long temps, distance;
byte speed=150; // speed motor 

void setup() {
  
 setPwmFrequency(E1,256); // this is to set the frequency of the PWM pins to 112Hz. 
 setPwmFrequency(E2,256); // see http://coolkidsrobots.com/guide/changing-pwm-frequencies-arduino for discussion
                          // the code is found in arduino website.
 // pins for ultrasound 
  pinMode(echoPin, INPUT); 
  pinMode(trigPin, OUTPUT);
// Setup motors for LM293D
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);
  // speed
  digitalWrite(E1, speed);  // motor are on
  digitalWrite(E2,speed); // motor are on
  }




void loop()
{


    drive_forward();
    delay(700);
    motor_stop();
    delay(100);
  computeDistance();
  // if distance smaller than 20 drive backward and turn left. 
  if (distance <20 && distance>0) {  
 //   Serial.println("smaller than 20");
 //   Serial.println("back ");
    drive_backward();
    delay(500);
    Serial.println("left");
      turn_left();  
    delay(200);
  motor_stop();
  delay(100);
  }
  else {
    drive_forward();
    delay(700);
    motor_stop();
    delay(100);
  }

    
  }
//    
//-------------------------------------------------------------------------------------------
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

void turn_left(){
digitalWrite(I1, LOW);
digitalWrite(I2, HIGH);

digitalWrite(I3, HIGH);
digitalWrite(I4, LOW);
}

void turn_right(){
digitalWrite(I1, HIGH);
digitalWrite(I2, LOW);

digitalWrite(I3, LOW);
digitalWrite(I4, HIGH);
}

void computeDistance() {
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 temps = pulseIn(echoPin, HIGH);
 distance = temps * 344/(2*10000);
 Serial.println(distance);
 
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
