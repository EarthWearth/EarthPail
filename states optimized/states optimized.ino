#include <Servo.h>
Servo serv;
char currangle = 90;  
float reading, total, avg, hist[10];

bool state(char check) {
  char val;
  if(avg >= .5) val = 2;
  else if(avg > .1) val = 1;
  else val = 0;
  Serial.print(val);
  return val = check;
}

void incrot(char newangle) { if(currangle != newangle) currangle += ((currangle < newangle) - .5) * 2; }

void setup() {
  Serial.begin(9600);
  serv.attach(13);
  serv.write(90);
  for(char i = 0; i < 10; i++) hist[i] = analogRead(A0);
}

void loop() {
  if(state(0)) incrot(90);
  if(state(1)) incrot(0);
  if(state(2)) incrot(180);
  
  reading = map(analogRead(A0), 0, 1023, 0, 25);
  if(reading != hist[0]) {
    avg = (avg * 10 - hist[0] + reading) / 10;
    for(char i = 0; i < 9; i++)
      hist[i] = hist[i + 1];
    hist[9] = reading;
    Serial.println(avg);
  }
}
