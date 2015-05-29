#include <Servo.h>
Servo serv;

const int len = 9;
int reading,
    currang,
    total,
    avg,
    lowang = 0,
    zeroang = 90,
    highang = 180,
    zero = 50,
    threshold = 500,
    hist[len + 1];

void setup() {
  serv.attach(13);
}

void incrot(char newang) {
  if(currang != newang) {
    if(currang < newang)
      currang++;
    else
      currang--;
    serv.write(currang);
} }

void pushval() {
  if(reading != hist[0]) {
    total -= hist[0];
    for(char i = 0; i < len; i++)
      hist[i] = hist[i + 1];
    total += reading;
    hist[len] = reading;
    avg = total / len;
} }

void loop() {
  zero:
  if(currang != zeroang)
    incrot(zeroang);
  reading = analogRead(A0);
  pushval();
  if(avg > threshold)
    goto low;
  goto zero;

  low:
  if(currang != lowang)
    incrot(lowang);
  reading = analogRead(A0);
  if(reading != hist[0])
    pushval();
  if(avg < zero)
    goto zero;
  if(avg > threshold)
    goto high;
  goto low;

  high:
  if(currang != highang)
    incrot(highang);
  reading = analogRead(A0);
  if(reading != hist[0])
    pushval();
  if(avg < threshold)
    goto low;
  goto high;
}
