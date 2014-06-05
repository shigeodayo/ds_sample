/**
 *    ds_sample10.ino
 *    ランダムな時間、ランダムな振り幅で、LEDが光っては消えるを繰り返す。複数のLEDに対応
 **/


/** pin assigns **/
const int LED_PIN[] = {9, 10};

/** amplitude (0-255/2) **/
const int MAX_AMPLITUDE_DOUBLE = 255;
const int MIN_AMPLITUDE_DOUBLE = 200;

/** radian step, manipulate the speed **/
const float MAX_RADIAN_STEP_INV = 50;  // 1 / 50
const float MIN_RADIAN_STEP_INV = 10;  // 1/ 10


float radians[] = {0.0, 0.0};
float radianSteps[] = {0.1, 0.1};
float amplitudes[] = {MAX_AMPLITUDE_DOUBLE / 2.0, MAX_AMPLITUDE_DOUBLE / 2.0};
float biases[] = {MAX_AMPLITUDE_DOUBLE / 2.0, MAX_AMPLITUDE_DOUBLE / 2.0};

int peakCounts[] = {0, 0};

void setup() {
  for (int i = 0; i < sizeof(LED_PIN) / sizeof(LED_PIN[0]); i++) {
    pinMode(LED_PIN[i], OUTPUT);
    digitalWrite(LED_PIN[i], LOW);
  }

  randomSeed(analogRead(0));  // initialize the pseudo-random number generator

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < sizeof(LED_PIN) / sizeof(LED_PIN[0]); i++) {
    if (radians[i] >= (peakCounts[i] + 1) * PI) {
      peakCounts[i]++;

      float prevAmplitude = amplitudes[i];

      amplitudes[i] = random(MIN_AMPLITUDE_DOUBLE, MAX_AMPLITUDE_DOUBLE - biases[i] + prevAmplitude) / 2.0;
      Serial.print("amp: ");
      Serial.println(amplitudes[i]);

      radianSteps[i] = 1.0 / random(MIN_RADIAN_STEP_INV, MAX_RADIAN_STEP_INV);

      if (peakCounts[i] == 2) {
        biases[i] += amplitudes[i] - prevAmplitude;

        peakCounts[i] = 0;
        radians[i] = 0;
      } else {
        biases[i] += prevAmplitude - amplitudes[i];
      }
    }


    int ledValue = amplitudes[i] * (-cos(radians[i])) + biases[i];
    ledValue = constrain(ledValue, 0, 255);
    analogWrite(LED_PIN[i], ledValue);
    Serial.println(radians[i]);

    radians[i] += radianSteps[i];
  }
}
