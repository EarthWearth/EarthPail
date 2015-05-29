#include <Servo.h>
Servo serv;

char        currangle = 90; // presume start at 90°
const char  len = 10, // * readings to keep
            newest = len - 1, // array position of newest reading
            oldest = 0,
            limit = 25; // * max measurement in lbs
float       reading, // current reading; may or may not be added to hist[]
            total, // sum of all entries in hist[]
            avg, // of all entries in hist[]
            hist[len]; // declare hist with len positions
const float zero = .1, // * in lbs; no readings up to this are taken into account
            threshold = .5; // * readings that are at least this are considered trash

char state(char check) { // 
  char val;
  if(avg >= threshold)
    val = 2;
  else if(avg > zero)
    val = 1;
  else
    val = 0;
  Serial.println(val);
  return val = check;
}

void incrot(char newangle) {
  if(currangle < newangle) {
    currangle++;
    serv.write(currangle);
  }
  else if(currangle > newangle) {
    currangle--;
    serv.write(currangle);
  }
}

void setup() {
  Serial.begin(9600);
  serv.attach(13);
  serv.write(90);
  for(char i = 0; i < len; i++) {
    hist[i] = analogRead(A0);
  }
}

void loop() {
  if(state(0)) incrot(90);
  if(state(1)) incrot(0);
  if(state(2)) incrot(180);
  
  reading = map(analogRead(A0), 0, 1023, 0, limit);
  if(reading != hist[oldest]) {
    total -= hist[oldest];
    for(char i = 0; i < newest; i++)
      hist[i] = hist[i + 1];
    hist[newest] = reading;
    total += hist[newest];
    avg = total / len;
    Serial.println(avg);
  }
}
