#include "mbed.h"
#include "MAX9814.h"

MAX9814::MAX9814(PinName pin): _pin(pin), _led1(LED1), _led2(LED2), _led3(LED3), _led4(LED4) {
    calibration();
}


void MAX9814::led_array(float x ) {

    if (_value<x+0.05) {
            _led1=0;
            _led2=0;
            _led3=0;
            _led4=0;
    }
    if (_value>x+0.05&&_value<0.5+x) {
            _led1=1;
            _led2=0;
            _led3=0;
            _led4=0;
    }
    if (_value>0.5+x&&_value<1+x) {
            _led1=1;
            _led2=1;
            _led3=0;
            _led4=0;
    }
    if (_value>1+x&&_value<1.2+x) {
            _led1=1;
            _led2=1;
            _led3=1;
            _led4=0;
    }
    if (_value>1.2+x&&_value<2.8+x) {
            _led1=1;
            _led2=1;
            _led3=1;
            _led4=1;
    }
}

float MAX9814::calibration() {
    
    _t.start();
    _t1.start();
    float peakToPeak=0, signalMax=0, signalMin=1024;

    while (_t1.read()<1) {
        while (_t.read_ms()<50) {
            _sample=_pin.read();

            if (_sample<1024) {
                if (_sample>signalMax)
                    signalMax=_sample;

                else if (_sample<signalMin)
                    signalMin=_sample;
            }
        }
     _t.reset();
     peakToPeak=signalMax-signalMin;
     _value= (peakToPeak*3.3);
     _value = floor(_value * 100) / 100;
     _sum+=_value;
     _count++;
    }
    _average=_sum/_count;
    _t1.reset();

    return _average;
}

float MAX9814::sound_level() {

    _t.start();
    float peakToPeak=0, signalMax=0, signalMin=1024;

    while (_t.read_ms()<50) {
        _sample=_pin.read();

        if (_sample<1024) {
            if (_sample>signalMax)
                signalMax=_sample;

            else if (_sample<signalMin)
                signalMin=_sample;
        }
    }
    _t.reset();
    peakToPeak=signalMax-signalMin;
    _value= (peakToPeak*3.3);
    _value = floor(_value * 100) / 100;
    _sum+=_value;
    _count++;

    return _value;
}


void MAX9814::volume_indicator() {
        led_array(_average);
        sound_level();
}
