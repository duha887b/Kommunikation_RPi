#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include "temperature.h"


#define BASE 200 // wiringPi „device node“ BASE Nummer
#define SPI_CHAN 0 // SPI Kanal

int main() {
    mcp3004Setup(BASE, SPI_CHAN);
    // ^ In einer gemeinsamen Datei initialisieren?
    for (;;) {
        float temp = readTemperature(BASE);

        printf("%f\n", temp);  // printf später löschen und mit return ersetzen!
        delay(1000); // in ms
    }
}

