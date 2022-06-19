//
// Created by IVO on 19.6.2022 г..
//

#include "temperature.h"
#include <wiringPi.h>
//helper един вид
float convertADCToCelsius(float adcValue) {  // adcValue in mV
    return (adcValue*(3300/1024) - 500)/10;
    //https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
}

float readTemperature(int base) {
    float adcValue = analogRead(base);
    return convertADCToCelsius(adcValue);
}