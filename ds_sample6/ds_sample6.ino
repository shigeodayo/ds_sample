/**
 *    ds_sample6.ino
 *    一定以上近づくと、LEDが段階的に消え始める
 **/

/** pin assigns **/
const int SENSOR_PIN = 0; // analog pin (A0)
const int LED_PIN = 3; // digital pin (3)

/** constant values **/
const int DIST_VALUE_THRESHOLD = 500;
const int LED_VALUE_MAX = 255;
const int LED_VALUE_MIN = 0;
const int LED_VALUE_STEP = 5;
const int DELAY_STEP = 100; // 100ms


void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int distValue = analogRead(SENSOR_PIN);
  Serial.println(distValue);

  if (distValue > DIST_VALUE_THRESHOLD) {
    decBrightnessGradually();
  }

  digitalWrite(LED_PIN, HIGH);

  delay(100);
}

void decBrightnessGradually() {
  int ledValue = LED_VALUE_MAX;
  while (ledValue >= LED_VALUE_MIN) {
    analogWrite(LED_PIN, ledValue);
    delay(DELAY_STEP);
    ledValue -= LED_VALUE_STEP;
  }
}
