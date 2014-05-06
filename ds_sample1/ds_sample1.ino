/**
 *    ds_sample1.ino
 *    一定以上近づくと、LEDが光る
 **/

/** pin assigns **/
const int SENSOR_PIN = 0; // analog pin (A0)
const int LED_PIN = 3; // digital pin (3)

/** constant values **/
const int DIST_VALUE_THRESHOLD = 500;


void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int distValue = analogRead(SENSOR_PIN);
  Serial.println(distValue);

  if (distValue > DIST_VALUE_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(100);
}
