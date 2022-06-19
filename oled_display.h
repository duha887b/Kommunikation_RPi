//
// Created by jakob on 17.06.22.
//

#ifndef KOMMUNIKATION_RPI_OLED_DISPLAY_H
#define KOMMUNIKATION_RPI_OLED_DISPLAY_H
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>
#include <stdlib.h>
#include "ssd1306_i2c.h"
#define I2CADRESS 0x00 //hier adresse einfügen

void init_display();
void updateTemp(char *temp);

#endif //KOMMUNIKATION_RPI_OLED_DISPLAY_H
