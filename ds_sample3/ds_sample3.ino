/**
 *    ds_sample3.ino
 *    近づくと段階的にLEDが光る
 **/

/** pin assigns **/
const int SENSOR_PIN = 0; // analog pin (A0)
const int LED_PIN = 3; // digital pin (3)

/** constant values **/
const int DIST_VALUE_MIN = 50;
const int DIST_VALUE_MAX = 650;


void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int distValue = analogRead(SENSOR_PIN);
  Serial.println(distValue);

  if (distValue <= DIST_VALUE_MIN) {
    distValue = DIST_VALUE_MIN;
  } else if (distValue >= DIST_VALUE_MAX) {
    distValue = DIST_VALUE_MAX;
  }
  int ledValue = map(distValue, DIST_VALUE_MIN, DIST_VALUE_MAX, 0, 255);
  analogWrite(LED_PIN, ledValue);

  delay(100);
}
