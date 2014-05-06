/**
 *    ds_sample5.ino
 *    一定以上近づくと、LEDが段階的に光り始める
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
    incBrightnessGradually();
  }

  digitalWrite(LED_PIN, LOW);

  delay(100);
}

void incBrightnessGradually() {
  int ledValue = LED_VALUE_MIN;
  while (ledValue <= LED_VALUE_MAX) {
    analogWrite(LED_PIN, ledValue);
    delay(DELAY_STEP);
    ledValue += LED_VALUE_STEP;
  }
}