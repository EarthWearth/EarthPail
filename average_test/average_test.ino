// libraries
// #include <Servo.h>
#include <Average.h>

// integers
int // serv_pwr = 13,
    // serv_ctrl = 12,
    pot = A0,
    smoothing = 50,
    readings = 0;

// objects/classes
// Servo serv;
Average<int> avg(smoothing);

void setup()
{ Serial.begin(9600);
  /* serv.attach(serv_ctrl); */ }

void loop()
{ do
  { avg.push(analogRead(pot));
    readings++; }
  while(readings < smoothing);
  Serial.println("mean: ");
  Serial.print(avg.mean());
  Serial.println("mode: ");
  Serial.print(avg.mode());
  Serial.println("mini: ");
  Serial.print(avg.minimum());
  Serial.println("maxi: ");
  Serial.print(avg.maximum());
  Serial.println("stdv: ");
  Serial.print(avg.stddev()); }
