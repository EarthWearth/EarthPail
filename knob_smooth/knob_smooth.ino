#include <Average.h>
#include <Servo.h>

Servo servo; // create servo object

// constants
const byte pot_pin = 0, // analog pin for pot
           servo_pin = 9, // digital pin for servo
           smoothness = 10, // values in history to average

// list of resistance values (special instantiation for use with Average library)
Average<float> history(smoothness);

// variables
int wait_time = 10; // time to wait between iterations of loop (milliseconds)
int angle; // angle to write to servo, between 0 and 180
int resistance;
int run_count = 10; // obtain this many values before starting to average them

int smooth(int value) {
  return Average.rollingAverage(history, smoothness, value);
}

void setup() {
  servo.attach(servo_pin); // associate servo object with servo at pin 9
  Serial.begin(9600); // open serial communication with computer
}

void loop() {
  // set servo position according to the scaled value of the rolling average, taking into account the last [smooth] values, and add the next value to history
  resistance = analogRead(pot_pin);
  angle = map(smooth(resistance), 0, 1023, 0, 180);
  if(run_count != 0) // until 10 values have been obtained
    run_count--; // count down
  else { // once 10 values have been obtained
    servo.write(angle);
    Serial.println(angle); // record pot reading in serial monitor
    delay(wait_time); // allow for servo movement and skip errors
  }
}

// to do: use array list for rolling average
