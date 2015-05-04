// Arduino with load cell

// Put two known loads on the sensor and take readings. Put those values
// here.
float aReading = 192.0;
float aLoad = 15.0; // lbs.
float bReading = 344.0;
float bLoad = 24.3; // lbs.

long time = 0;
int interval = 500; // Take a reading every 500 ms

void setup() {
  Serial.begin(9600);
}

void loop() {
  float newReading = analogRead(0);
  
  // Calculate load based on A and B readings above
  float load = ((bLoad - aLoad)/(bReading - aReading)) * (newReading - aReading) + aLoad;
  
  // millis returns the number of milliseconds since the board started the current program
  if(millis() > time + interval) {
    Serial.print("Reading: ");
    Serial.print(newReading,1); // 1 decimal place
    Serial.print("  Load: ");
    Serial.println(load,1);  // 1 decimal place, println adds a carriage return
    time = millis();
  }
}
