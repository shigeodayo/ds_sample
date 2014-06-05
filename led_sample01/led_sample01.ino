/**
 *    led_sample01.ino
 *    ランダムな時間、ランダムな振り幅で、LEDが光っては消えるを繰り返す
 **/


/** pin assigns **/
const int LED_PIN = 9;

/** amplitude (0-255/2) **/
const int MAX_AMPLITUDE_DOUBLE = 255;
const int MIN_AMPLITUDE_DOUBLE = 150;

/** radian step, manipulate the speed **/
const float MAX_RADIAN_STEP_INV = 50;  // 1 / 50
const float MIN_RADIAN_STEP_INV = 10;  // 1/ 10


float radian = 0.0;
float radianStep = 0.1;
float amplitude = MAX_AMPLITUDE_DOUBLE / 2.0;
float bias = MAX_AMPLITUDE_DOUBLE / 2.0;

int peakCount = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);


  digitalWrite(LED_PIN, LOW);

  randomSeed(analogRead(0));  // initialize the pseudo-random number generator

  Serial.begin(9600);
}

void loop() {
  if (radian >= (peakCount + 1) * PI) {
    peakCount++;

    float prevAmplitude = amplitude;

    amplitude = random(MIN_AMPLITUDE_DOUBLE, MAX_AMPLITUDE_DOUBLE - bias + prevAmplitude) / 2.0;
    Serial.print("amp: ");
    Serial.println(amplitude);

    radianStep = 1.0 / random(MIN_RADIAN_STEP_INV, MAX_RADIAN_STEP_INV);

    if (peakCount == 2) {
      bias += amplitude - prevAmplitude;

      peakCount = 0;
      radian = 0;
    } else {
      bias += prevAmplitude - amplitude;
    }
  }


  int ledValue = amplitude * (-cos(radian)) + bias;
  ledValue = constrain(ledValue, 0, 255);
  analogWrite(LED_PIN, ledValue);
  Serial.println(ledValue);

  radian += radianStep;

  delay(50);
}
