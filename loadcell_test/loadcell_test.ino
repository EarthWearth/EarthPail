float values = 100,
sumSub,
sumMult,
sumAdd;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < values; i++) {
    sumSub += analogRead(A0) - analogRead(A1);
    sumAdd += analogRead(A0) + analogRead(A1);
    sumMult += analogRead(A0) * analogRead(A1);
    delay(1000 / values);
  }
  sumSub /= values * 2;
  sumMult /= values * 2;
  sumAdd /= values * 2;
  // print out the value you read:
  Serial.print(sumAdd);
  Serial.print(", ");
  Serial.print(sumMult);
  Serial.print(", ");
  Serial.println(sumSub);
}
