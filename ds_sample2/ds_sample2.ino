/**
 *    ds_sample2.ino
 *    一定以上近づくと、LEDが消える
 **/


/** ピンの割り当て **/
const int LED_PIN    = 11;  // LEDの明るさを調節するピン (11)
const int SENSOR_PIN = 0;   // 測距センサの値を取得するピン (A0)


const int DIST_VALUE_THRESHOLD = 500;  // LEDが反応を開始する距離を示す定数
                                       // ここを変えるとLEDが反応する距離を変えられる


/** setupルーチン、プログラム起動時に最初に呼ばれる **/
void setup() {
  pinMode(LED_PIN, OUTPUT);  // LED_PINを出力用のピンとして設定

  Serial.begin(9600);        // シリアル通信の設定
}


/** loopルーチン、プログラム起動中に繰り返し実行される **/
void loop() {
  int distValue = analogRead(SENSOR_PIN);  // 測距センサの値を読み取る、値が大きいほど距離が近い

  Serial.println(distValue);               // 測距センサの値をシリアルモニタに出力する


  /* 一定以上近づくとLEDが消え、それよりも遠いとLEDが光る */
  if (distValue > DIST_VALUE_THRESHOLD) {  // 近づく
    digitalWrite(LED_PIN, LOW);            // LEDを消す
  } else {                                 // 離れる
    digitalWrite(LED_PIN, HIGH);           // LEDを光らせる
  }


  delay(100);  // 100ms処理を待つ
}
