/* Infrared code to read in sensors depending on tritrack location
 *  IR sensor will need to output the detection of an obstacle and feed it back
 *  into the mbed inputs, triggering a movement response
 *  --- 17ELD002, R ASANTE, Group G - Created: 18/01/2018
*/
int  IR_SENS_LEFT = 1;
int  IR_SENS_RIGHT = 2;
int  IR_SENS_FORWARD = 3;
int  IR_SENS_BACK = 4;

int IR_SENS_LEFTDETECTED = 5;
int IR_SENS_RIGHTDETECTED = 6;
int IR_SENS_BACKDETECTED = 7;
int IR_SENS_FORWARDDETECTED = 8;

void setup()
{
  pinMode(IR_SENS_LEFT, INPUT);    
  pinMode(IR_SENS_RIGHT, INPUT);  
  pinMode(IR_SENS_BACK, INPUT);    
  pinMode(IR_SENS_FORWARD, INPUT);


  pinMode(IR_SENS_LEFTDETECTED, OUTPUT); 
  pinMode(IR_SENS_FORWARDDETECTED, OUTPUT); 
  pinMode(IR_SENS_BACKDETECTED, OUTPUT); 
  pinMode(IR_SENS_RIGHTDETECTED, OUTPUT); 
}

void loop()
{
if (digitalRead(IR_SENS_LEFT) == 1){
  digitalWrite(IR_SENS_LEFTDETECTED, 1);
}

if (digitalRead(IR_SENS_RIGHT) == 1){
  digitalWrite(IR_SENS_RIGHTDETECTED, 1);
}
if (digitalRead(IR_SENS_BACK) == 1){
  digitalWrite(IR_SENS_BACKDETECTED, 1);
}
if (digitalRead(IR_SENS_FORWARD) == 1){
  digitalWrite(IR_SENS_FORWARDDETECTED, 1);
}
}

