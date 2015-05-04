#include <Servo.h>

// objects
Servo myservo; // title of our servo

// pins
const byte sensor_pin = A0, // location of load sensor pin
           servo_pin  = 9; // location of servo control pin

// variables
float weight;

void setup() {
  myservo.attach(servo_pin); // associate servo title with control pin
  Serial.begin(9600); // start serial communication with computer
}

void loop() {
  weight = analogRead(sensor_pin) * 453.592; // measure weight on platform and convert from pounds to grams
  while(weight < 1) { // when nothing is on platform
    delay(80);
  }
  if(weight < 10) { // when recyclables are on platform
    myservo.write(0); // tilt platform to left
    delay(5000); // wait five seconds for platform
    myservo.write(90); // flatten platform
    delay(5000);
  }
  else { // when garbage is on platform
    myservo.write(180); // tilt platform to right
    delay(5000);
    myservo.write(90);
    delay(5000);
}
