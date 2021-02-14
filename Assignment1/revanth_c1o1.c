#include<unistd.h>
#include <stdio.h>
#include<sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
int main(){
	int sd,len,type;
    char clientMessage[25];
	char buff[25];
	struct sockaddr_in serv;
	sd = socket(AF_INET,SOCK_STREAM,0);
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr =inet_addr("127.0.0.1");
	serv.sin_port = htons(2500);
    connect(sd,(struct sockaddr *)&serv,sizeof(serv));
    while(1){
        printf("\ntext message here .. :");
        fgets(clientMessage,sizeof(clientMessage),stdin);
        write(sd,clientMessage,sizeof(clientMessage));
        read(sd,&buff,sizeof(buff));
        printf("\nSERVER: %s",buff);
    }     
}