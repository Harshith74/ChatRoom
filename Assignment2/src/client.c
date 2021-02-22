// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h>

#include <msg.h>
// #include <ntp.h>

enum Mode mode;

int sock = 0;
pthread_t ptid; 
struct group_message msg;
struct group_chat_acknowledge ack;
FILE *fp;

void handle_sig(int sign)
{
	if(SIGINT){
		printf("killing client,PID=%d\n",getpid());
		pthread_kill(ptid,SIGINT);
		close(sock);
		exit(0);
	}
}

void* recv_read(void *v)
{
	char filename[30];

	long long delay=0;
	int *sock = (int *)v;
	struct group_message incoming;

	while(1)
	{
		if(read( *sock , &incoming, sizeof(incoming)))
		{
				printf("%s:%s\n",incoming.user_name,incoming.message);			
		}
	} 
}

int main(int argc, char const *argv[]) 
{ 	
	printf("client created,PID=%d\n",getpid());
	struct sockaddr_in serv_addr;  
    	if(argc!=5)
    	{
        	printf("Wrong Arguments!! \nUsage:%s <Server-IP-Addr> <Port> <User-Name> <Group-Name>\n",argv[0]);
       		exit(EXIT_FAILURE);
    	}
	
    
    int port=atoi(argv[2]);
    struct group_chat_request req;
        
    strcpy(req.group_name,argv[4]);
    strcpy(req.user_name,argv[3]);
	
	mode=PROD;

	
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(port); 
	signal(SIGINT,handle_sig);

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	write(sock,&req,sizeof(req));
    read(sock,&ack,sizeof(ack));
    
    msg.group_identifier=ack.group_identifier;
    msg.user_identifier=ack.user_identifier;
    strcpy(msg.user_name,req.user_name);

    pthread_create(&ptid, NULL, &recv_read, &sock); 
	while(1)
	{
		fgets(msg.message,1024,stdin);
		write(sock , &msg , sizeof(msg)); 
	}
	return 0; 
} 
