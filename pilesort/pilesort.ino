int weight_sensor = "A0";
float platform_weight = 0.0;
float threshold = 9.5; // in grams
float error = 0.0; // how

void setup() {
    pinMode(weight_sensor, INPUT);
}

void loop() {
    int weight = analogRead(weight_sensor) * 453.592; // convert from pounds to grams
    while(weight < platform_weight) { // nothing on platform
        delay(80); // wait with a delay to prevent nuclear meltdown
    if(weight < threshold) { // once while loop is interrupted, if plastic
        // write: tilt platform to recyclable side
    else {
        // write: tilt platform to garbage side
}
