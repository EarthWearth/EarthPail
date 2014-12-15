#include <SoftwareServo.h>

// pins
const char sensor[] = "A0"; // load cell; just for reference
const int servo[] = [13, 12]; // servo
    const byte pwr = 13; // power pin: always on
    const byte ctrl = 12; // control pin

// variables
float platform = 0.0; // weight of platform to subtract from measurements
float threshold = 9.5; // cutoff between weights of trash and recyclables
float error = 0.0; // maximum difference in measurement to excuse

void setup() {
    pinMode(A0, INPUT); // initialize load cell
    pinMode(servo[pwr], OUTPUT); // initialize servo power pin
    pinMode(servo[ctrl], OUTPUT); // initialize servo control pin
}

void loop() {
    int weight = analogRead(weight_sensor) * 453.592; // convert from pounds to grams
    while(weight < platform_weight) { // nothing on platform
        delay(80); // wait with a delay to prevent nuclear meltdown
    if(weight < threshold) { // once while loop is interrupted, if plastic
        // write: tilt platform to recyclable side
    else {
        // write: tilt platform to garbage side
    }
}
