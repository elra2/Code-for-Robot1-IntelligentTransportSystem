#include "mbed.h"
#include "USBHostXpad.h"
#include "C12832.h"
#include "Servo.h"

Serial pc(USBTX, USBRX);
C12832 lcd(p5, p7, p6, p8, p11);

//Servo
Servo servo_L(p22);
Servo servo_R(p21);
float MOVEBACK = 0.8;
float MOVEFORWARD = 0.2;
float STANDSTILL = 0.5;

//New xbox controller
USBHostXpad XBOXCONT;

void onXpadEvent (int buttons, int stick_lx, int stick_ly, int stick_rx, int stick_ry, int trigger_l, int trigger_r) {
         //STICK POSITION
         if(stick_lx < -16000) {
            lcd.cls();
            lcd.printf("Left\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEBACK;
            servo_R = MOVEFORWARD;
        }
        else if(stick_lx > 16000) {
            lcd.cls();
            lcd.printf("Right\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEFORWARD;
            servo_R = MOVEBACK;
            }
        else if(stick_ly < -16000) {
            lcd.cls();
            lcd.printf("Backwards\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEBACK;
            servo_R = MOVEBACK;
        }
        else if(stick_ly > 16000) {
            lcd.cls();
            lcd.printf("Forward\n");
            lcd.cls();
            lcd.locate(0,3);
            servo_L = MOVEFORWARD;
            servo_R = MOVEFORWARD;
            }
            
            
        //ABXY BUTTONS    
        else if(XBOXCONT.read(USBHostXpad::XPAD_PAD_A) == 1){
        lcd.cls();
        lcd.printf("BUTTON A PRESSED", USBHostXpad::XPAD_PAD_A);
        servo_L = STANDSTILL;
        servo_R = STANDSTILL;
            }
       else if(XBOXCONT.read(USBHostXpad::XPAD_PAD_B) == 1){
            lcd.cls();
            lcd.printf("BUTTON B PRESSED", USBHostXpad::XPAD_PAD_B);
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_PAD_X) == 1){
            lcd.cls();
            lcd.printf("BUTTON X PRESSED", USBHostXpad::XPAD_PAD_X);
            }
       else if(XBOXCONT.read(USBHostXpad::XPAD_PAD_Y) == 1){
            lcd.cls();
            lcd.printf("BUTTON Y PRESSED", USBHostXpad::XPAD_PAD_Y);
            }
            
        //LEFT TRIGGER
       else if(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) <=0.5){
            lcd.cls();
            lcd.printf("NO SPEED", USBHostXpad::XPAD_PAD_Y);
            }
       else if(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) <= 1){
            lcd.cls();
            lcd.printf("FAST SPEED", USBHostXpad::XPAD_PAD_Y);
            }
        
        //RIGHT TRIGGER
        else if(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 0.5){
            lcd.cls();
            lcd.printf("NO SPEED", USBHostXpad::XPAD_PAD_Y);
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 1){
            lcd.cls();
            lcd.printf("SLOW SPEED", USBHostXpad::XPAD_PAD_Y);
            }
        else {
            servo_L = STANDSTILL;
            servo_R = STANDSTILL;
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
   // while(1) {
        //Thread::wait(200);
    //}
}
