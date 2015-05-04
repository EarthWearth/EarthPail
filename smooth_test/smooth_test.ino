#include <Servo.h>

/*
data type  a = b, x = y; */
const byte reading_count = 10, // readings to remember
           sensor = A0, servo_power = 13, servo_control = 12, // pins
           zero = 10, threshold = 255, // unit: 5/1024 volts
           standby_angle = 90, trash_angle = 0, recycle_angle = 180; // for servo
byte       readings[reading_count], // list of length "reading_count"
           index = 0, // list position to store/access reading
           total = 0;
const int  servo_speed = 5000; // unit: 1/1000 second
float      average; // decimal precision for division
Servo      platform;

void move_to(byte some_angle) { // function definition
  platform.write(some_angle);
  delay(servo_speed); // wait for servo
  platform.write(standby_angle); // move back
  delay(servo_speed);
}

void setup() {
  Serial.begin(9600);
  platform.attach(servo_control); // use servo_control pin for platform
  for(int i = 0; i < reading_count; i++) // with i from 0 to reading_count
    readings[i] = 0;
}

void loop() {
  total += (readings[index] = analogRead(sensor)); // add first reading to list and to total
  index += 1; // add 1 to index
  total -= readings[index]; // subtract next reading 
  if(index == reading_count) // when we have finished the reading list
    index = 0; // go back to the beginning
  average = total / reading_count;
  if(average > threshold)
    move_to(trash_angle);
  else if(average > zero)
    move_to(recycle_angle);
}
