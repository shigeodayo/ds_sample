/**
 *    ds_sample7.ino
 *    一定以上近づくと、LEDが段階的に光り始める、その後段階的に消えていく
 **/


/** ピンの割り当て **/
const int LED_PIN    = 11;  // LEDの明るさを調節するピン (11)
const int SENSOR_PIN = 0;   // 測距センサの値を取得するピン (A0)


/** LEDが反応を開始する距離を示す定数 **/
const int DIST_VALUE_THRESHOLD = 400;  // ここを変えるとLEDが反応する距離を変えられる


/** LEDの明るさの範囲 (0->0V : 255->5V) **/
const int LED_VALUE_MIN = 0;    // LEDの最小の明るさ
const int LED_VALUE_MAX = 255;  // LEDの最大の明るさ

const int LED_WORK_TIME_MS = 10000; // LEDが最大/最小の明るさなるまでにかかる時間(ミリ秒)
const int LED_VALUE_STEP = 5;        // LEDの明るさの増加/減少分


const int SWITCH_WAIT_TIME = 5000; // LEDが光っている時間


/** setupルーチン、プログラム起動時に最初に呼ばれる **/
void setup() {
  pinMode(LED_PIN, OUTPUT);  // LED_PINを出力用のピンとして設定

  Serial.begin(9600);        // シリアル通信の設定
}


/** loopルーチン、プログラム起動中に繰り返し実行される **/
void loop() {
  int distValue = analogRead(SENSOR_PIN);  // 測距センサの値を読み取る、値が大きいほど距離が近い

  /* 一定以上近づくと、段階的に光り始め、その後段階的に消えていく */
  if (distValue > DIST_VALUE_THRESHOLD) {
    brightenLinearly();
    delay(SWITCH_WAIT_TIME);
    dimLinearly();
  }

  digitalWrite(LED_PIN, LOW);  // 近づいていないとき、LEDは消えている

  delay(100);  // 100ms処理を待つ
}


/** LEDを徐々に光らせる **/
void brightenLinearly() {
  int stepNum = 1 + (LED_VALUE_MAX - LED_VALUE_MIN) / LED_VALUE_STEP;
  int eachStepDelay = LED_WORK_TIME_MS / stepNum;

  int ledValue = LED_VALUE_MIN;
  for (int i = 0; i < stepNum; i++) {
    ledValue = constrain(ledValue, 0, 255);  // [0,255]の値しかとらないように制限
    analogWrite(LED_PIN, ledValue);
    Serial.println(ledValue);
    ledValue += LED_VALUE_STEP;

    delay(eachStepDelay);
  }
}


/** LEDを徐々に消す **/
void dimLinearly() {
  int stepNum = 1 + (LED_VALUE_MAX - LED_VALUE_MIN) / LED_VALUE_STEP;
  int eachStepDelay = LED_WORK_TIME_MS / stepNum;

  int ledValue = LED_VALUE_MAX;
  for (int i = 0; i < stepNum; i++) {
    ledValue = constrain(ledValue, 0, 255);  // [0,255]の値しかとらないように制限
    analogWrite(LED_PIN, ledValue);
    Serial.println(ledValue);
    ledValue -= LED_VALUE_STEP;

    delay(eachStepDelay);
  }
}
