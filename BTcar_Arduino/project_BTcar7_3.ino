#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include "AFMotor.h"
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double cmd;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);



void setup(){
    Serial.begin(115200);
    Serial.println("hello");
    
}

void loop(){
    
    if((Serial.available()) > (0)){
        cmd = Serial.read();
        if(((cmd)==('w'))){
            motor1.setSpeed(255);
             motor1.run(2);
            motor2.setSpeed(255);
             motor2.run(2);
        }
        if(((cmd)==('s'))){
            motor1.setSpeed(255);
             motor1.run(1);
            motor2.setSpeed(255);
             motor2.run(1);
        }
        if(((cmd)==('d'))){
            motor1.setSpeed(255);
             motor1.run(1);
            motor2.setSpeed(255);
             motor2.run(2);
        }
        if(((cmd)==('a'))){
            motor1.setSpeed(255);
             motor1.run(2);
            motor2.setSpeed(255);
             motor2.run(1);
        }
        if(((cmd)==('f'))){
            motor1.setSpeed(0);
             motor1.run(RELEASE);
            motor2.setSpeed(0);
             motor2.run(RELEASE);
        }
    }
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

