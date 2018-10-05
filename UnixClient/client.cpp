#include "client.h"

bool stopClientKey = false;
WindowHandler* winh;

Client::Client(WindowHandler* tmp)
{
    winh = tmp;
}

int Client::sendData(int sock, const char * message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("send\n");
        return -1;
    }
    return 0;
}

int Client::recvData(int sock, char * message, int size) {
    if (recv(sock, message, size, 0) < 0) {
       // perror("recv\n");
        return -1;
    }
    return 0;
}

int Client::startClient() {
    stopClientKey = false;
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_ < 0) {
        perror("socket");
        return -1;
    }
    reserveSock_ = socket(AF_INET, SOCK_STREAM, 0);
    if(reserveSock_ < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3500);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(connect(sock_, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
        perror("connect 1\n");
        close(sock_);
        return -1;
    }
    if(connect(reserveSock_, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
        perror("connect 2\n");
        close(reserveSock_);
        return -1;
    }
    pthread_create(&thread_, NULL, listeningServer, this);
    return 0;
}

int Client::stopClient() {
    char serverMsg[3];
    stopClientKey = true;
    return 0;
}

void * Client::listeningServer(void *arg) {
    Client *client = (Client*)arg;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    setsockopt(client->getReserveSock(), SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    int res;
    char buff[255];
    char serverMsg[3];
    do {
        res = client->recvData(client->getReserveSock(),buff,255);
    } while ((std::string(buff) != "close") && !stopClientKey);
    sendData(client->getSock(),"close");
    recvData(client->getSock(),serverMsg,sizeof serverMsg);
    close(client->getSock());
    close(client->getReserveSock());
    emit winh->serverOffSignal();
    return NULL;
}








