#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <stdbool.h>

#define UDP_PORT 9000
#define BUFFSIZE 1024
#define BASE 200 // wiringPi „device node“ BASE Nummer
#define SPI_CHAN 0 // SPI Kanal
#define DELAY 1000


int sockid=0;
int status=0;
struct sockaddr_in client_addr;
struct  sockaddr_in server_addr;

//
// Created by IVO on 19.6.2022 г..
//

//helper един вид
float convertADCToCelsius(float adcValue) {  // adcValue in mV
    return (adcValue*(3300/1024) - 500)/10;
}

float readTemperature(int base) {
    float adcValue = analogRead(base);
    return convertADCToCelsius(adcValue);
}

void ini(){

    sockid = socket(PF_INET,SOCK_DGRAM,0);
    if(sockid == -1){
        perror("socket creation failed");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//raspi
    server_addr.sin_port= htons(UDP_PORT);
    
}

void send_data(float temp){
    char msg[30] ;
    sprintf(msg, "%.1f", temp);
    unsigned int addrlen = sizeof (server_addr);

    int count = sendto(sockid,msg,strlen(msg),0,(struct sockaddr*)&server_addr,addrlen);
    printf("count: %i\n",count);
    status = count;
}


int main() {
    printf("start transmitter \n");
    ini();
    printf("Hallo");
    mcp3004Setup(BASE, SPI_CHAN);

    while (true){
        if(0){
            break;
        }

        send_data(readTemperature(BASE));
        
        delay(DELAY);
    }




    status = close(sockid);
    if(status==0){
        printf("socket close successful \n");
    } else{ perror("socket close failed");}

    return 0;
}
