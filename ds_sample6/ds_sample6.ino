/**
 *    ds_sample6.ino
 *    一定以上近づくと、LEDが段階的に消え始める
 **/


/** ピンの割り当て **/
const int LED_PIN    = 11;  // LEDの明るさを調節するピン (11)
const int SENSOR_PIN = 0;   // 測距センサの値を取得するピン (A0)


/** LEDが反応を開始する距離を示す定数 **/
const int DIST_VALUE_THRESHOLD = 500;  // ここを変えるとLEDが反応する距離を変えられる


/** LEDの明るさの範囲 (0->0V : 255->5V) **/
const int LED_VALUE_MIN = 0;    // LEDの最小の明るさ
const int LED_VALUE_MAX = 255;  // LEDの最大の明るさ

const int LED_WORK_TIME_MS = 15000; // LEDが最小の明るさなるまでにかかる時間(ミリ秒)
const int LED_VALUE_STEP = 5;        // LEDの明るさの減少分


/** setupルーチン、プログラム起動時に最初に呼ばれる **/
void setup() {
  pinMode(LED_PIN, OUTPUT);  // LED_PINを出力用のピンとして設定

  Serial.begin(9600);        // シリアル通信の設定
}


/** loopルーチン、プログラム起動中に繰り返し実行される **/
void loop() {
  int distValue = analogRead(SENSOR_PIN);  // 測距センサの値を読み取る、値が大きいほど距離が近い

  /* 一定以上近づくと、段階的に消え始める */
  if (distValue > DIST_VALUE_THRESHOLD) {
    dimLinearly();
  }

  digitalWrite(LED_PIN, HIGH);  // 近づいていないとき、LEDは光っている

  delay(100);  // 100ms処理を待つ
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