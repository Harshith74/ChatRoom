#include<unistd.h>
#include <stdio.h>
#include<sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
int sd,nsd,clilen;
char serverMessage[1024];
char clientMessage[1024];
	struct sockaddr_in serv,cli;
   	 sd = socket(AF_INET,SOCK_STREAM,0);

    	serv.sin_family = AF_INET;
    	serv.sin_addr.s_addr = INADDR_ANY;
    	serv.sin_port = htons(2500);
    	bind(sd,(struct sockaddr*)&serv,sizeof(serv));

    	listen(sd,1);
    	//write(1,"Waiting for client\n",sizeof("Waiting for client\n"));
        clilen=sizeof(cli);
		nsd=accept(sd,(struct sockaddr *)&cli,&clilen);
		    //write(1,"successfully entered server",sizeof("successfully entered server"));
        while (1)
        {   
            read(nsd, &clientMessage, sizeof(clientMessage));
            printf("\nCLIENT: %s", clientMessage);
            printf("\ntext message here .. :");
            fgets(serverMessage,sizeof(serverMessage),stdin);
            write(nsd, &serverMessage, sizeof(serverMessage));    
        }
        //close the socket
        close(sd);
        return 0;
    }