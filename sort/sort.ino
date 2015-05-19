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

const unsigned char  reading_count = 10, // constant 0–255 to declare readings[]
                     servo_pin = 13,
                     input_pin = A0,
                     time = 500; // half-second delay for servo to move
unsigned char        index = 0; // 0–reading_count, which reading in the order is being operated upon
signed short         deviation;
unsigned short       total = 0;
const unsigned short trash_min = 300, // smallest weight to qualify as trash
                     load_min = 50; // smallest weight to activate servo
double               average_reading = 0;
unsigned long long   readings[reading_count];
Servo                myservo;

void average() {
  total -= readings[index]; // subtracts old reading from total; does nothing for initial value of 0
  readings[index] = analogRead(input_pin); // set value at index to current reading
  total += readings[index]; // adds new reading to total
  index += 1; // move to next index
  if(index == reading_count)
    index = 0; // loop back to 0
  average_reading = total / reading_count;
  Serial.println(average_reading); }

void move_to(byte angle) {
  myservo.write(angle);
  delay(time); 
  while(average_reading > 0) // while the average is increasing or staying the same
    average();
  myservo.write(90);
  delay(time);
}

void setup() {
  Serial.begin(9600);
  for(unsigned char this_reading = 0; this_reading < reading_count; this_reading++)
    average();
  myservo.attach(servo_pin);
  myservo.write(90); // platform starts flat
}

void loop() {
  if(average_reading > load_min) {
    if(average_reading > trash_min) 
      move_to(180);
    else
      move_to(0);
  }
  average();
}
