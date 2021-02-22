#ifndef _msg_H_
#define _msg_H_
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#define gname_size 10
#define uname_size 10
#define msg_size 100

enum MSG_STATUS{CLOSE_ME,MESSAGE};

enum Mode{DEV,PROD};


struct group_chat_request
{
    char group_name[gname_size];
    char user_name[uname_size];    
};


struct group_chat_acknowledge
{
    int group_identifier;
    int user_identifier;    
};

struct group_message
{
    enum MSG_STATUS status;
    int group_identifier;
    int user_identifier;
    char message[msg_size];
    char user_name[uname_size];
    long long time_stamp;
};

struct message_queue
{
    struct group_message message_q_ll;
    struct message_queue *next;
};



#endif
