//
// Created by dustin on 6/17/22.
//

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define I2CADRESS 0x3c
#define UDP_PORT 9000
#define BUFFSIZE 1024
#define DELAY 1000


int sockid;
int status;
int fd;
struct sockaddr_in client_addr;
struct  sockaddr_in server_addr;
char * recvBuf[BUFFSIZE];

//
// Created by jakob on 17.06.22.
//

 //nutzt "echte" ssd1306_i2c -> nicht getestet
void init_display(){
    fd = ssd1306I2CSetup(I2CADRESS);

    displayOn(fd);
    draw_line(1,1,"MRT2-Praktikum");
    updateDisplay(fd);

}

//ebenfalls nicht getestet
 void updateTemp(char* temp) {
    char* t = "Aktuelle Temperatur: ";
    
    
    //strcat(t,temp);
    clearDisplay(fd);
    draw_line(1,1,temp);
    updateDisplay(fd);
}


void ini(){

    sockid = socket(PF_INET,SOCK_DGRAM,0);
    if(sockid == -1){
        perror("socket creation failed");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //raspi
    server_addr.sin_port= htons(UDP_PORT);

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //PC
    client_addr.sin_port= htons(UDP_PORT);


    status = bind(sockid, (struct sockaddr *)&server_addr,sizeof (server_addr));
    if(status == -1){
        perror("binding failed");
        exit(0);
    }else{ printf("binding done\n");}

}

void receive_data(){
    unsigned int addrlen = sizeof (client_addr);

    int count = recvfrom(sockid,recvBuf,BUFFSIZE,0,(struct sockaddr *)&client_addr,&addrlen);

    if(count == -1){
        perror("recvfrom failed");
    } else{ printf("received data");}

    recvBuf[count] = '\0';

    printf(" :%s\n",recvBuf );
}


int main(){
    printf("Starte Programm_s\n");
    ini();
    init_display();

    while(true){
        if(0){
            break;
        }
        receive_data();
        updateTemp(recvBuf);
        delay(DELAY);
    }




    status = close(sockid);
    if(status==0){
        printf("socket close successful \n");
    } else{ perror("socket close failed");}
}
