#ifndef CLIENT_H
#define CLIENT_H

#include "includes.h"

class Client
{
public:
    Client(int sock,int reserveSock, pthread_t thread);

    int getSock(){
       return sock_;
    }

    int getReserveSock(){
       return reserveSock_;
    }

    pthread_t getThread() {
        return thread_;
    }

    void setThread(pthread_t thread) {
        thread_ = thread;
    }

private:
    int sock_;
    int reserveSock_;
    pthread_t thread_;
};

#endif // CLIENT_H
