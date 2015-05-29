#include <Servo.h>
Servo myservo;

unsigned char        index = 0;
const unsigned char  reading_count = 10,
                     servo_pin = 13,
                     input_pin = A0,
                     zero = 50;
unsigned short       total = 0;
const unsigned short time = 500,
                     threshold = 500;
double               average_reading = 0;
unsigned long long   readings[reading_count];

void average() {
  total -= readings[index];
  readings[index] = analogRead(input_pin);
  total += readings[index];
  index += 1;
  if(index == reading_count)
    index = 0;
  average_reading = total / reading_count;
  Serial.println(average_reading);
}

void move_to(char angle) {
  myservo.write(angle);
  delay(time);
  while(average_reading > zero)
    average();
  myservo.write(90);
  delay(time);
}

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < reading_count; i++)
    readings[i] = 0;
  myservo.attach(servo_pin);
  myservo.write(90);
}

void loop() {
  do{average();} while(readings[reading_count - 1] == 0);
  if(average_reading > zero) {
    if(average_reading > threshold) {
      above_threshold:
        move_to(180);
        while(average_reading > zero) {
          average();
          if(average_reading < threshold)
            goto below_threshold;
        }
    }
    else {
    below_threshold:
        move_to(0);
        while(average_reading > zero) {
          average();
          if(average_reading > threshold)
            goto above_threshold;
        }
    }
      
  }
}
