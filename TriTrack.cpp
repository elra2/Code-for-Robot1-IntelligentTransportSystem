/* TriTrack Library Functions----------------- Created 17/01/2018
 * For the purpose of 17ELD002 for Team G, actions of the TriTrack functions
 * Including digital inputs, outputs, analog inputs, outputs, servo control and sensors 
 * Copyright (c) 2018 R ASANTE, Github ID: elra2, Wolfson School/lboro.ac.uk
 *
 */

#include "TriTrack.h"
#include "Servo.h"
#include "mbed.h"


//Servo
Servo servo_L(p22); //CH1 WIRE
Servo servo_R(p21); //CH2 WIRE

//IR Sensors
AnalogIn LEFT_IR(A0);
AnalogIn RIGHT_IR(A1);
AnalogIn FORWARD_IR(A2);
AnalogIn BACKWARD_IR(A3);

void TriTrack::velocity(int direction)
{
    _direction = direction;
    //DO SELECT SWITCH
    if (_direction == 1){   //Move Left
    servo_L = 0.8;
    servo_R = 0.2;
        }
    if ((direction) == 2){ //Move Right
    servo_L = 0.2;
    servo_R = 0.8;
        }
    if (direction == 3){  //Move Forward
    servo_L = 0.2;
    servo_R = 0.2;
        }
    if (direction == 4){ //Move Backward
    servo_L = 0.8;
    servo_R = 0.8;
    }
    if (direction == 5){ //Move Backward
    servo_L = 0.5;
    servo_R = 0.5;
    }
}

int TriTrack::IR_Sensor_Location(){ //Get The Location of the IR Sensor in object
        if(LEFT_IR > 0.2f) {
            _location = 1;
        }
        else if (FORWARD_IR > 0.2f){
            _location = 2;
        }
        else if (RIGHT_IR  > 0.2f){
            _location = 3;
        }
        else if (BACKWARD_IR > 0.2f){
            _location = 4;
        }
    return _location;
}
    
