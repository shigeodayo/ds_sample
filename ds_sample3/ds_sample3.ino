/**
 *    ds_sample3.ino
 *    近づくと段階的にLEDが光る
 **/


/** ピンの割り当て **/
const int LED_PIN    = 11;  // LEDの明るさを調節するピン (11)
const int SENSOR_PIN = 0;   // 測距センサの値を取得するピン (A0)


/** LEDが反応する範囲 **/
const int DIST_VALUE_MIN = 150;   // 反応する距離を示す値の最小値、値が小さいほど測距センサから遠い
const int DIST_VALUE_MAX = 500;  // 反応する距離を示す値の最大値、値が大きいほど測距センサから近い


/** setupルーチン、プログラム起動時に最初に呼ばれる **/
void setup() {
  pinMode(LED_PIN, OUTPUT);  // LED_PINを出力用のピンとして設定

  Serial.begin(9600);        // シリアル通信の設定
}


/** loopルーチン、プログラム起動中に繰り返し実行される **/
void loop() {
  int distValue = analogRead(SENSOR_PIN);  // 測距センサの値を読み取る、値が大きいほど距離が近い

  Serial.println(distValue);               // 測距センサの値をシリアルモニタに出力する


  /* map関数を使うために、測距センサの値が最小/最大値を超えないように調整する */
  if (distValue < DIST_VALUE_MIN) {
    distValue = DIST_VALUE_MIN;
  } else if (distValue > DIST_VALUE_MAX) {
    distValue = DIST_VALUE_MAX;
  }

  /* map関数: map(value, fromLow, fromHigh, toLow, toHigh)
   * ある値 (fromLow <= value <= fromHigh)を、新たな値 (toLow <= newValue <= toHigh)に置き換える */
  int ledValue = map(distValue, DIST_VALUE_MIN, DIST_VALUE_MAX, 0, 255);  // 測距センサの値をLEDの光量に置き換える
  analogWrite(LED_PIN, ledValue);  // アナログ出力
                                   // LEDに加わる電圧を0-5Vの間で調整 (ledValue=0 -> 0V : ledValue=255 -> 5V)


  delay(100);  // 100ms処理を待つ
}
