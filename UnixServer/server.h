#ifndef SERVER_H
#define SERVER_H

#include "includes.h"
#include "client.h"
#include "windowhandler.h"

class Server
{
public:
    Server(WindowHandler* tmp);
    int startServer();
    int stopServer();
    static void * serverThread(void *arg);
    static void * clientThread(void *arg);
    static int recvData(int sock, char * message, int size);
    static int sendData(int sock, const char * message);

    void pushClient(Client client) {
        clients_.push_back(client);
    }

private:
    int sock_;
    struct sockaddr_in saddr_;
    pthread_t thread_;
    std::vector<Client> clients_;
    int clientsCount_;
};

#endif // SERVER_H
