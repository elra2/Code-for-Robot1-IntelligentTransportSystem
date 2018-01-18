#include "mbed.h"
#include "USBHostXpad.h"
#include "C12832.h"
#include "Servo.h"
#include "TriTrack.h"


Serial pc(USBTX, USBRX);
C12832 lcd(p5, p7, p6, p8, p11);


DigitalOut dout(LED1);

DigitalOut UPWARD(p23);
DigitalOut DOWNWARD(p24);
DigitalOut LEFTWARD(p25);
DigitalOut RIGHTWARD(p26);

TriTrack TriTrackBot;

//New xbox controller
USBHostXpad XBOXCONT;

void onXpadEvent (int buttons, int stick_lx, int stick_ly, int stick_rx, int stick_ry, int trigger_l, int trigger_r) {            
        
        //INITIAL POSITION - AUTO MOVEMENT

         
         //STICK POSITION - LEFT
         if(stick_lx < -16000) {
            lcd.cls();
            lcd.printf("Left\n");
            TriTrackBot.velocity(LEFT);

        }
        else if(stick_lx > 16000) {
            lcd.cls();
            lcd.printf("Right\n");
            }
        else if(stick_ly < -16000) {
            lcd.cls();
            lcd.printf("Backwards\n");
            lcd.cls();
            lcd.locate(0,3);
        }
        else if(stick_ly > 16000) {
            lcd.cls();
            lcd.printf("Forward\n");
            lcd.cls();
            lcd.locate(0,3);

            }
            
      //STICK POSITION - RIGHT
         if(stick_lx < -16000) {
            lcd.cls();
            lcd.printf("Left\n");
            lcd.cls();
            lcd.locate(0,3);

        }
        else if(stick_lx > 16000) {
            lcd.cls();
            lcd.printf("Right\n");
            lcd.cls();
            lcd.locate(0,3);

            }
        else if(stick_ly < -16000) {
            lcd.cls();
            lcd.printf("Backwards\n");
            lcd.cls();
            lcd.locate(0,3);

        }
        else if(stick_ly > 16000) {
            lcd.cls();
            lcd.printf("Forward\n");
            lcd.cls();
            lcd.locate(0,3);
            }
            
            
        //ABXY BUTTONS    
        if(XBOXCONT.read(USBHostXpad::XPAD_PAD_A) == 1){
        lcd.cls();
        lcd.printf("BUTTON A PRESSED");
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
            Thread::wait(1000);

            
            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) >= 0.4 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) <= 0.7 ){
            lcd.cls();
            lcd.printf("HIGHER SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);

            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) >= 0.8 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_L) <= 1 ){
            lcd.cls();
            lcd.printf("FASTEST SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            }
        
        //RIGHT TRIGGER
      while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) >= 0.1 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 0.3 ){
            lcd.cls();
            lcd.printf("LOW SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) >= 0.4 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 0.7 ){
            lcd.cls();
            lcd.printf("HIGHER SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);
            }
       while(XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) >= 0.8 && XBOXCONT.read(USBHostXpad::XPAD_TRIGGER_R) <= 1 ){
            lcd.cls();
            lcd.printf("FASTEST SPEED", USBHostXpad::XPAD_PAD_Y);
            lcd.locate(0,3);

            }
            
      //DPAD POSITION
        if(XBOXCONT.read(USBHostXpad::XPAD_HAT_UP) == 1){
            lcd.cls(); 
            lcd.printf("forward %f", USBHostXpad::XPAD_HAT_UP);
            lcd.locate(0,3);
            UP = 1;
            wait(2);
            Thread::wait(1000);
            UP = 0;
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_HAT_LEFT) == 1){
            lcd.cls(); 
            lcd.printf("LEFT %f", USBHostXpad::XPAD_HAT_LEFT);
            lcd.locate(0,3);
            DOWN = 1;
            wait(2);
            Thread::wait(1000);
            DOWN = 0;
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_HAT_RIGHT) == 1){
            lcd.cls(); 
            lcd.printf("RIGHT %f", USBHostXpad::XPAD_HAT_RIGHT);
            lcd.locate(0,3);
            LEFT = 1;
            Thread::wait(1000);
            LEFT = 0;
            }
        else if(XBOXCONT.read(USBHostXpad::XPAD_HAT_DOWN) == 1){
            lcd.cls(); 
            lcd.printf("DOWN %f", USBHostXpad::XPAD_HAT_DOWN);
            lcd.locate(0,3);
            RIGHT = 1;
            Thread::wait(1000);
            RIGHT = 0;
            }
            
volatile int poll = 0;
}
 
void xpad_task(void const *) {
    volatile int poll = 0;
    lcd.cls();
    lcd.printf("Disconnected..");
    while(1) {
        // Try to connect a Xbox 360 Wireless Controller
        
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
        Thread::wait(500);
    }
}


