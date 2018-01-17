/* TriTrack Library----------------- Created 17/01/2018
 * For the purpose of 17ELD002 for Team G, actions of the TriTrack functions
 * Including digital inputs, outputs, analog inputs, outputs, servo control and sensors 
 * Copyright (c) 2018 R ASANTE, Github ID: elra2, Wolfson School/lboro.ac.uk
 *
 */
 
 
 //Fastest = 3, Slowest = 1
float MOVEBACK_SPEED3 = 0.8;
float MOVEBACK_SPEED2 = 0.7;
float MOVEBACK_SPEED1 = 0.6;

//float STANDSTILL = 0.5;

float MOVEFORWARD_SPEED1 = 0.4;
float MOVEFORWARD_SPEED2 = 0.3;
float MOVEFORWARD_SPEED3 = 0.2;


//Movement
#define LEFT = 1
#define RIGHT = 2
#define FORWARD = 3;
#define BACKWARD = 4;
#define STANDSTILL = 5;

//IR Sensor Location
#define IR_SENS_LEFT = 1
#define IR_SENS_FOWARD = 2 
#define IR_SENS_BACK = 3
#define IR_SENS_RIGHT = 4


class TriTrack
{
    /*MakeMovement: 1 int Parameter direction to be passed through, no returns
    Read_IR: Read IR Sensor location to detect obstacle or object, returns bool
    SetAutoMode: No Parameters, returns a bool
    */
public:
    void velocity(int direction); //add speed as float to be changed/altered
    int IR_Sensor_Location();
private:
    int _location;
    int _direction;
    int _AutoONOFF;
    float _Speed;
    int _counter;
};
