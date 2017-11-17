#include "mbed.h"
#include "MAX9814.h"
#include "C12832.h"
Serial pc (USBTX, USBRX);
C12832 lcd(p5, p7, p6, p8, p11);

MAX9814 mic(p15);
MAX9814 mic2(p16);
float V;
float V2;

int main()

{
    while (1) {
        mic.volume_indicator();
            //lcd.locate(0,0);
            //lcd.printf("\n\r Mic Level 1 is %f", mic.sound_level());
            //wait(0.1);
        mic2.volume_indicator();
            //lcd.locate(0,10);
            //lcd.printf("\n\r Mic Level 2 is %f", mic2.sound_level());
            //wait(0.1);
            
            V  = mic.sound_level();
            V2 = mic2.sound_level();
            
            if (V >= V2){ 
            lcd.cls();
            lcd.locate(0,0);
            lcd.printf("Left");
            //wait (0.05);
            }
            else if (V <= V2){
            lcd.cls();
            lcd.locate(0,0);
            lcd.printf("Right");
            //wait (0.05);
            }
            
        }
}