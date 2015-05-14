#include <Servo.h>

// bit: unit with two possible values, 0 or 1

// bool: 1 bit, so has 2^1 = 2 states
// char: 8 bits, so has 2^8 = 256 states
// short: 16 bits, so has 2^16 = 65536 states
// double: floating-point (i.e., decimal); more accurate than float

// unsigned: no +/-, so values less than middle value aren't treated as negative (more capacity)
// const: constant (as opposed to variable) so takes less space
// long: squares capacity (double the bits) of int (integer)
// Servo: object used to define servo

bool                 load_moved = false; // true/false, whether current load has been identified
unsigned char        index = 0; // 0–reading_count, which reading is being operated upon
const unsigned char  reading_count = 10, // constant for initialization of readings[]
                     servo_pin = 13,
                     input_pin = A0,
                     servo_delay = 500; // half a second
unsigned short       total = 0;
const unsigned short trash_minimum = 500; // 500/1024 of 5 volts
double               average_reading = 0;
unsigned long long   readings[reading_count];
Servo                myservo;

void average() {
  total -= readings[index]; // subtracts old reading from total; does nothing for initial value of 0
  readings[index] = analogRead(input_pin); // set value at index to current reading
  total += readings[index]; // adds new reading to total
  index += 1; // move to next index
    if(index == reading_count) index = 0; // loop back to 0
  average_reading = total / reading_count;
  Serial.println(average_reading); }

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < reading_count; i++) readings[i] = 0; // set all readings to 0 to allow for averaging
  myservo.attach(servo_pin);
  myservo.write(90);
}

void loop() {
  average();
  if(average_reading > 50) {
    for(int i = 0; i < reading_count; i++) average();
    if(average_reading > trash_minimum) {
      myservo.write(180);
      delay(servo_delay);
      while(average_reading > 0.0) average();
      myservo.write(90);
      delay(servo_delay);
    }
    else {
      myservo.write(0);
      delay(servo_delay);
      while(average_reading > 1) average();
      myservo.write(90);
      delay(servo_delay);
    }
  }
}
