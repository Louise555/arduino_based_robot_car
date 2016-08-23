
/* testing the whiskers for the car. The switches are normally close. (HIGH) 
 *  If the switches are pressed then the swithes open the circuit. 
 * set up is 5V - whisker 1 - pin2 -10K - gnd
 * 5V - whisker 2 - pin3 - 10K - gndd
 */
 boolean bpLeft;
 boolean bpRight;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT); // right bumper 
  pinMode(3,INPUT); // left bumper    
}

void loop() {
  bpLeft=digitalRead(3);
  bpRight=digitalRead(2);
  if (bpLeft==LOW) {
      Serial.println("left numper "); 
      Serial.println(" reverse and turn right ");
      delay(500); // wait for bouncing to be over
    }
    Serial.println(" " );
  if (bpRight==LOW) { 
   Serial.println("right  bumper ");
    Serial.println("reverse and turn left");
    delay(500); // wait for bouncing to be over
    }
}
