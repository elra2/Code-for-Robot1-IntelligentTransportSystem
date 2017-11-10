#include "mbed.h"
#include "USBHostXpad.h"
#include "C12832.h"
#include "Servo.h"

Serial pc(USBTX, USBRX);
C12832 lcd(p5, p7, p6, p8, p11);
/* --- Code output/verifitcation indicators in place of lcd should it be needed
DigitalOut forward(LED1);
DigitalOut back(LED2);
DigitalOut left(LED3);
DigitalOut right(LED4);
---- */

//Servo
Servo servo_L(p22); //CH1 WIRE
Servo servo_R(p21); //CH2 WIRE

//Fastest = 3, Slowest = 1
float MOVEBACK_SPEED3 = 0.8;
float MOVEBACK_SPEED2 = 0.7;
float MOVEBACK_SPEED1 = 0.6;

float STANDSTILL = 0.5;

float MOVEFORWARD_SPEED1 = 0.4;
float MOVEFORWARD_SPEED2 = 0.3;
float MOVEFORWARD_SPEED3 = 0.2;


//New xbox controller
USBHostXpad XBOXCONT;

void onXpadEvent (int buttons, int stick_lx, int stick_ly, int stick_rx, int stick_ry, int trigger_l, int trigger_r) {            
         //STICK POSITION - LEFT
         if(stick_lx < -16000) {
            lcd.cls();
            lcd.printf("Left\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED2;
            servo_R = MOVEFORWARD_SPEED2;
        }
        else if(stick_lx > 16000) {
            lcd.cls();
            lcd.printf("Right\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED2;
            servo_R = MOVEBACK_SPEED2;
            }
        else if(stick_ly < -16000) {
            lcd.cls();
            lcd.printf("Backwards\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED2;
            servo_R = MOVEBACK_SPEED2;
        }
        else if(stick_ly > 16000) {
            lcd.cls();
            lcd.printf("Forward\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED2;
            servo_R = MOVEFORWARD_SPEED2;
            }
            
      //STICK POSITION - RIGHT
         if(stick_lx < -16000) {
            lcd.cls();
            lcd.printf("Left\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED2;
            servo_R = MOVEFORWARD_SPEED2;
        }
        else if(stick_lx > 16000) {
            lcd.cls();
            lcd.printf("Right\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED2;
            servo_R = MOVEBACK_SPEED2;
            }
        else if(stick_ly < -16000) {
            lcd.cls();
            lcd.printf("Backwards\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED2;
            servo_R = MOVEBACK_SPEED2;
        }
        else if(stick_ly > 16000) {
            lcd.cls();
            lcd.printf("Forward\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED2;
            servo_R = MOVEFORWARD_SPEED2;
            }
            
            
        //ABXY BUTTONS    
        if(XBOXCONT.read(USBHostXpad::XPAD_PAD_A) == 1){
        lcd.cls();
        lcd.printf("BUTTON A PRESSED");
        servo_L = STANDSTILL;
        servo_R = STANDSTILL;
            }
       else if(XBOXCONT.read(USBHostXpad::XPAD_PAD_B) == 1){
            lcd.cls(); 
            lcd.printf("BUTTON B PRESSED");
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_PAD_X) == 1){
            lcd.cls();
            lcd.printf("BUTTON X PRESSED");
            }
       else if(XBOXCONT.read(USBHostXpad::XPAD_PAD_Y) == 1){
            lcd.cls();
            lcd.printf("BUTTON Y PRESSED");
            }
            
        //LEFT TRIGGER
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) >= 0.1 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) <= 0.3 ){
            lcd.cls();
            lcd.printf("LOW SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED1;
            servo_R = MOVEBACK_SPEED1;
            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) >= 0.4 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) <= 0.7 ){
            lcd.cls();
            lcd.printf("HIGHER SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED2;
            servo_R = MOVEBACK_SPEED2;
            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) >= 0.8 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) <= 1 ){
            lcd.cls();
            lcd.printf("FASTEST SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED3;
            servo_R = MOVEBACK_SPEED3;
            }
        
        //RIGHT TRIGGER
      while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) >= 0.1 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 0.3 ){
            lcd.cls();
            lcd.printf("LOW SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED1;
            servo_R = MOVEFORWARD_SPEED1;
            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) >= 0.4 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 0.7 ){
            lcd.cls();
            lcd.printf("HIGHER SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED2;
            servo_R = MOVEFORWARD_SPEED2;
            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) >= 0.8 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 1 ){
            lcd.cls();
            lcd.printf("FASTEST SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED3;
            servo_R = MOVEFORWARD_SPEED3;
            }
            
      //DPAD POSITION
        if(XBOXCONT.read(USBHostXpad::XPAD_HAT_UP) == 1){
            lcd.cls(); 
            lcd.printf("forward %f", USBHostXpad::XPAD_HAT_UP);
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED1;
            servo_R = MOVEFORWARD_SPEED1;
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_HAT_LEFT) == 1){
            lcd.cls(); 
            lcd.printf("LEFT %f", USBHostXpad::XPAD_HAT_LEFT);
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED1;
            servo_R = MOVEFORWARD_SPEED1;
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_HAT_RIGHT) == 1){
            lcd.cls(); 
            lcd.printf("RIGHT %f", USBHostXpad::XPAD_HAT_RIGHT);
            lcd.locate(0,3);
            servo_L = MOVEFORWARD_SPEED1;
            servo_R = MOVEBACK_SPEED1;
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_HAT_DOWN) == 1){
            lcd.cls(); 
            lcd.printf("DOWN %f", USBHostXpad::XPAD_HAT_DOWN);
            lcd.locate(0,3);
            servo_L = MOVEBACK_SPEED1;
            servo_R = MOVEBACK_SPEED1;
            }
            
volatile int poll = 0;
}
 
void xpad_task(void const *) {
    volatile int poll = 0;
    lcd.cls();
    lcd.printf("Disconnected..");
    while(1) {
        // try to connect a Xbox 360 Wireless Controller
        
        while(!XBOXCONT.connect())
            Thread::wait(500);
        // when connected, attach handler called on xpad event
        XBOXCONT.attachEvent(onXpadEvent);
        XBOXCONT.led(USBHostXpad::LED_ROTATE); //TEST ITS CONNECTED CHANGE ROTATE FUNCTION
        Thread::wait(500);
        XBOXCONT.rumble(0xff, 0);
        Thread::wait(500);
        XBOXCONT.rumble(0, 0xff);
        Thread::wait(500);
        XBOXCONT.rumble(0, 0);
        Thread::wait(500);
        XBOXCONT.led(USBHostXpad::LED4_FLASH);
        XBOXCONT.led(USBHostXpad::LED2_ON);
        lcd.cls();
        lcd.printf("Connected!");
        // wait until the mouse is disconnected
        while(XBOXCONT.connected()) {
            Thread::wait(500);
            poll ++;
            if (poll > 2) {
                XBOXCONT.restart();
                poll = 0;
            }
        }
    }
}

 
int main() {
    Thread xpadTask(xpad_task, NULL, osPriorityNormal, 1024 * 4);
    pc.baud(115200);
    lcd.cls();
    while(1) {
           //INITIAL POSITION
            servo_L = STANDSTILL;
            servo_R = STANDSTILL;
            lcd.printf("Still Standing");
        Thread::wait(500);
    }
}
