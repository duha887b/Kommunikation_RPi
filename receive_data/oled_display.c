//
// Created by jakob on 17.06.22.
//
#include <stdio.h>
#include "oled_display.h"


/*
 * nutzt "echte" ssd1306_i2c -> nicht getestet
void init_display(){
    fd = ssd1306I2CSetup(I2CADRESS);

    displayOn(fd);
    draw_line(1,1,"MRT2-Praktikum");
    updateDisplay(fd);

}*/

/*ebenfalls nicht getestet
 * void updateTemp(double temp) {
    char t[] = "Aktuelle Temperatur: ";
    char s[30] = {};
    sprintf(s, "%lf",temp);
    strcat(t,s);

    draw_line(1,1,"%s\n",t)
}*/

//nutzt ssd1306_i2c von iliapenev (github)
void init_display(){
    ssd1306_begin(SSD1306_SWITCHCAPVCC, I2CADRESS);

    ssd1306_display();
    ssd1306_clearDisplay();
    char welcome[] = "MRT2-Praktikum";
    ssd1306_drawString(welcome);
    ssd1306_display();
}

void updateTemp(char *temp){
    ssd1306_clearDisplay();

    char t[] = "Aktuelle Temperatur: ";

    strcat(t,temp);

    ssd1306_drawString(t);
    ssd1306_display();

    printf("%s\n",t);
}