#include <Servo.h>

// objects
Servo servobj;

// pins
/*const*/ byte sensor = A0; // load cell
/*const*/ int servo_pin[] = {13, 12}; // list of servo pins
  /*const*/ bool pwr = 0; // power pin: always on
  /*const*/ bool ctrl = 1; // control pin

// constants
/*const*/ int angle[] = {90, 0, 180}; // list of standard angles
  /*const*/ bool flat = 0; // angle when platform is flat
  /*const*/ bool trash = 1; // angle when sorting trash
  /*const*/ byte recycle = 2; // angle when sorting recycling
/*const*/ int delays[] = {80, 5000}; // list of standard delays
  /*const*/ bool runs = 0; // delay between loops
  /*const*/ bool rot = 1; // delay to allow servo to move into position

// variables
float zero = 0.0; // weight of platform to subtract from measurements
float threshold = 9.5; // cutoff between weights of trash and recyclables
float error = 0.0; // maximum difference in measurement to excuse
float weight; // in grams
int errors; // number of times type of material could not be determined

void setup() {
  pinMode(sensor, INPUT); // initialize load cell
  pinMode(servo_pin[pwr], OUTPUT); // initialize servo power pin
    digitalWrite(servo_pin[pwr], HIGH); // power servo
  pinMode(servo_pin[ctrl], OUTPUT); // initialize servo control pin
  servobj.attach(servo_pin[ctrl]); // associate servo object with servo control pin
}

void loop() {
  weight = analogRead(sensor) * 453.592; // convert from pounds to grams
  while(weight < zero) { // nothing on platform
    delay(delays[runs]); // wait with a delay to prevent nuclear meltdown
  }
  if(weight - zero < threshold - error) { // once while loop is interrupted, if plastic with 100% certainty
    servobj.write(angle[recycle]); // sort recycling
    delay(delays[rot]); // allow servo to rotate into position
    servobj.write(angle[flat]); // return platform to flat position
    delay(delays[runs]);
  }
  else if(weight - zero > threshold + error) { // if nonrecyclable with 100% certainty
    servobj.write(angle[trash]); // sort trash
    delay(delays[rot]);
    servobj.write(angle[flat]);
    delay(delays[runs]);
  }
  else { // if uncertain
    servobj.write(angle[trash]); // sort trash
    delay(delays[rot]);
    servobj.write(angle[flat]);
    delay(delays[runs]);
    errors++;
  }
}

/* TO DO

  find way to record number of errors
  make array list to record relevant weights
  figure out why arrays aren't working with type system
*/
