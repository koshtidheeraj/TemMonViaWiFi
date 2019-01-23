const int sensor_1 = A1; // A1 pin assigned to get temperature
float voutdig; // var to store vout digital
float voutana; // var to store vout analog
float tempCelcius;
void setup() {
  pinMode(sensor_1,INPUT);
  Serial.begin(115200);
}

void loop() {
  voutdig = analogRead(sensor_1);
  voutana = (voutdig*5000)/1023; // 1023 = 5000 mv so vout = ?
  // 10 mv = 1 celcius temp. increase
  tempCelcius = voutana/10;
  Serial.print(tempCelcius); // To write temp. on serial monitor
  delay(2000);
}
