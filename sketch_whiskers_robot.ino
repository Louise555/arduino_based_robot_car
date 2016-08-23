/*
 * we try to add whiskers to the robot. See whiskers testing 
 * if the switch is pressed then it is a LOW (whiskers feel something) otherwise a HIGH
 */
// --------------------------------------------------------------------------- Motors

#define E1 10  // Enable Pin for motor 1  - we will use the analogWrite to control speed so we need 10 and 11
#define E2 11  // Enable Pin for motor 2  - because you can write analog output using PWM technique. analogWRite() takes a number between 0 and 255
                                    //      - 255 is for 5V

#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
byte speed =150; // forward  speed = 150 - the speed can be between 0 and 255 theoritically. but below 150 it does not work. if speed is 0 the the driver is enable

// for bumpers or whiskers
const int bumpRight=2; // whiskers right
const int bumpLeft=3; // whiskers left
int bpLeft; // state of pin 3 it is HIGH when the siwtch is open as I destroyed the other way
int bpRight;
// --------------------------------------------------------------------------- Setup
void setup() {
Serial.begin(9600);

// Setup motors
 pinMode(E1, OUTPUT);
 pinMode(E2, OUTPUT);

pinMode(I1, OUTPUT);
pinMode(I2, OUTPUT);
pinMode(I3, OUTPUT);
pinMode(I4, OUTPUT);
analogWrite(E1, speed); // enable the motors at the required speed. 
analogWrite(E2, speed);

// whiskers
  pinMode(bumpRight,INPUT);
  pinMode(bumpLeft,INPUT);
}


// --------------------------------------------------------------------------- Loop
void loop() {
// forward  speed = 150 - the speed can be between 0 and 255 theoritically. but below 150 it does not work. if speed is 0 the the driver is enable
drive_forward();
bpLeft=digitalRead(bumpLeft);
  if (bpLeft==LOW) {
      Serial.print(" reverse and turn right ");
      Serial.println("left bumper") ;
      Serial.println(bpLeft);
    }
bpRight=digitalRead(bumpRight);
  if (bpRight==LOW) { 
    Serial.print("reverse and turn left");
    Serial.println("right bumper");
    Serial.println(bpRight);
    }
  Serial.println(bpRight);


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
digitalWrite(I1, HIGH);
digitalWrite(I2, LOW);

digitalWrite(I3, LOW);
digitalWrite(I4, LOW);
  }


