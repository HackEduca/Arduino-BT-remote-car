const byte LED = 13;
char val;     // 儲存接收資料的變數，採字元類型
void setup() {
  pinMode(LED, OUTPUT);
 
  // 序列傳輸速率依照藍牙模組的設定
  // 115200bps或57600bps
  Serial.begin(115200);
  Serial.println("Welcome to Arduino!");
}
 
void loop() {
  if( Serial.available() ) {
    val = Serial.read();
    switch (val) {
    case '0' :
      digitalWrite(LED, LOW);
      Serial.println("LED OFF");
      break;
    case '1' :
      digitalWrite(LED, HIGH);
      Serial.println("LED ON");
      break;
    }
  }
}
