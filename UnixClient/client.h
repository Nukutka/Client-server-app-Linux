#ifndef CLIENT_H
#define CLIENT_H

#include "includes.h"
#include "windowhandler.h"

class Client
{
public:
    Client(WindowHandler* winHand);
    int startClient();
    int stopClient();
    static int sendData(int sock, const char * message);
    static int recvData(int sock, char * message, int size);
    static void * listeningServer(void *arg);

    int getSock(){
        return sock_;
    }

    int getReserveSock() {
        return reserveSock_;
    }

    pthread_t getThread() {
        return thread_;
    }
private:
    int sock_;
    int reserveSock_;
    pthread_t thread_;
};

#endif // CLIENT_H
