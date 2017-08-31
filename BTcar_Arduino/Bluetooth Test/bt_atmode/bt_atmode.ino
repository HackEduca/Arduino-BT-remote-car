//HC-06 VCC → Arduino 5V
//HC-06 GND → Arduino GND
//HC-06 TXD → Arduino pin 10
//HC-06 RXD → Arduino pin 11


#include  <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX
  
void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(115200);
}
  
void loop()
{
  if (BTSerial.available())
    Serial.write(BTSerial.read());
    
  if (Serial.available())
    BTSerial.write(Serial.read());
}
