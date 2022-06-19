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
#include "temperature.h"
#include <stdbool.h>

#define UDP_PORT 9000
#define BUFFSIZE 1024
#define BASE 200 // wiringPi „device node“ BASE Nummer
#define SPI_CHAN 0 // SPI Kanal
#define DELAY 1000;


int sockid;
int status;
struct sockaddr_in client_addr;
struct  sockaddr_in server_addr;

void ini(){

    sockid = socket(PF_INET,SOCK_DGRAM,0);
    if(sockid == -1){
        perror("socket creation failed");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.150");//raspi
    server_addr.sin_port= htons(UDP_PORT);

}

void send_data(float temp){
    char *msg ;
    gcvt(temp,5,msg);
    unsigned int addrlen = sizeof (server_addr);

    long count = sendto(sockid,msg,strlen(msg),0,(struct sockaddr*)&server_addr,addrlen);
    printf("count: %li\n",count);
    status = count;
}


int main() {
    printf("start transmitter \n");
    ini();
    mcp3004Setup(BASE, SPI_CHAN);

    while (true){
        if(status == -1){
            break;
        }

        send_data(readTemperature(BASE))
        delay(DELAY);
    }




    status = close(sockid);
    if(status==0){
        printf("socket close successful \n");
    } else{ perror("socket close failed");}

    return 0;
}
