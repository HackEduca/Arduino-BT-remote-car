/******************************************************************/
#include <PS2X_lib.h>

#define PS2_DAT        8  //13    
#define PS2_CMD        6  //11
#define PS2_SEL        5  //10
#define PS2_CLK        7  //12
#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
int error = 0;
byte type = 0;
byte vibrate = 0;
int VRy_Read = 0, VRy_PWM = 0, VRx_Read = 0, VRx_PWM = 0;
/******************************************************************/
int E1 = 10;
int M1 = 12;
int E2 = 11;
int M2 = 13;


void setup() {
  Serial.begin(57600);
  delay(300);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  /******************************************************************/
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}

void loop() {
  if (error == 1) //skip loop if no controller found
    return;
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

  int VRy_Read = ps2x.Analog(PSS_LY);            //讀取搖桿數值(x.y)
  int VRx_Read = ps2x.Analog(PSS_LX);
  VRx_PWM = map(VRx_Read, 0, 255, 255, -255); //修正搖桿讀取數值為PWM
  VRy_PWM = map(VRy_Read, 0, 255, 255, - 255);
  Serial.print("VRx_PWM= ");
  Serial.print(VRx_PWM);
  Serial.print("    VRy_PWM= ");
  Serial.println(VRy_PWM);

  if ( (VRy_PWM) > 10 &&  (VRx_PWM) < 10 && (VRx_PWM) > -10 ) {                     //前進
    Serial.println("forward");
    digitalWrite(M1, HIGH);
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH);
    analogWrite(E2, 255);
    
  } else if ( (VRy_PWM) < -10 && (VRx_PWM) < 10 && (VRx_PWM) > -10 ) {                     //前進
    Serial.println("backward");
    digitalWrite(M1, LOW);
    analogWrite(E1, 255);
    digitalWrite(M2, LOW);
    analogWrite(E2, 255);
    
  } else if ( (VRx_PWM) > 10 &&  (VRy_PWM) < 10 && (VRy_PWM) > -10 ) {                     //前進
    Serial.println("Right");
    digitalWrite(M1, HIGH);
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH);
    analogWrite(E2, 150);
    
  } else if ( (VRx_PWM) < -10 &&  (VRy_PWM) < 10 && (VRy_PWM) > -10 ) {                     //前進
    Serial.println("Left");
    digitalWrite(M1, HIGH);
    analogWrite(E1, 150);
    digitalWrite(M2, HIGH);
    analogWrite(E2, 255);

  } else if ( ps2x.Button(PSB_R1)  ) {                     //前進
    Serial.println("RotationR");
    digitalWrite(M1, LOW);
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH);
    analogWrite(E2, 255);

  } else if ( ps2x.Button(PSB_L1)   ) {                     //前進
    Serial.println("RotationL");
    digitalWrite(M1, HIGH);
    analogWrite(E1, 255);
    digitalWrite(M2, LOW);
    analogWrite(E2, 255);

  } else {
    digitalWrite(M1, LOW);
    analogWrite(E1, 0);
    digitalWrite(M2, LOW);
    analogWrite(E2, 0);
  }

  delay(10);
}

