#include <SoftwareSerial.h>
SoftwareSerial BTSerial(0, 1); // RX, TX

int E1 = 10;
int M1 = 12;
int E2 = 11;
int M2 = 13;
char BTcomd;

void setup() {
  Serial.begin(9600);
  Serial.println("GG,OK");
  BTSerial.begin(115200);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop() {
  if (BTSerial.available() > 0) {
    BTcomd = BTSerial.read();
    Serial.print("BTcomd= ");
    Serial.print(BTcomd);
  }

  if ( BTcomd == 'U') {
    Serial.println("Forward");
    digitalWrite(M1, LOW);
    analogWrite(E1, 255);
    digitalWrite(M2, LOW);
    analogWrite(E2, 255);

  } else if ( BTcomd == 'D') {
    Serial.println("Backward");
    digitalWrite(M1, HIGH);
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH);
    analogWrite(E2, 255);

  } else if ( BTcomd == 'R') {
    Serial.println("Right");
    digitalWrite(M1, LOW);
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH);
    analogWrite(E2, 255);

  }  else if ( BTcomd == 'L') {
    Serial.println("Left");
    digitalWrite(M1, HIGH);
    analogWrite(E1, 255);
    digitalWrite(M2, LOW);
    analogWrite(E2, 255);
  }

  else {
    Serial.println("Halt");
    digitalWrite(M1, LOW);
    analogWrite(E1, 0);
    digitalWrite(M2, LOW);
    analogWrite(E2, 0);
  }

  delay(10);
}

