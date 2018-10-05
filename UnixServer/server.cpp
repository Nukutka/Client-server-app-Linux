#include "server.h"

WindowHandler* winh;

bool stopServerKey = false;

Server::Server(WindowHandler* tmp)
{
    winh = tmp;
    clientsCount_ = 0;
}

int Server::sendData(int sock, const char * message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("send\n");
        return -1;
    }
    return 0;
}

int Server::recvData(int sock, char * message, int size) {
    memset(&message[0],0,size); // clear buff
    if (recv(sock, message, size, 0) < 0) {
        perror("recv\n");
        return -1;
    }
    return 0;
}

int Server::stopServer() {
    stopServerKey = true;
    char buff[255];
    for (int i = 0; i < clients_.size(); i++) { // send close msg to all clients
        sendData(clients_[i].getReserveSock(),"close");
    }
    //pthread_exit(0);
    return 0;
}

// Init server param's
int Server::startServer() {
    stopServerKey = false;
    sock_ = socket(AF_INET, SOCK_STREAM, 0); // TCPv4, garant, auto (TCP)
    if(sock_ < 0) {
        perror("socket\n");
        return -1;
    }

    saddr_.sin_family = AF_INET;
    saddr_.sin_port = htons(3500);
    saddr_.sin_addr.s_addr = inet_addr("127.0.0.1");
    int one = 1;
    setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &one, sizeof(int));

    if(bind(sock_, (struct sockaddr *)&saddr_, sizeof(saddr_)) < 0) {
        perror("bind\n");
        close(sock_);
        return -1;
    }

    if (listen(sock_, SOMAXCONN)< 0) {
        perror("listen\n");
        close(sock_);
        return -1;
    }

    pthread_create(&thread_,NULL,serverThread, this);
    return 0;
}

// Waiting connections
void * Server::serverThread(void *arg) {
    Server *server = (Server*)arg;
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    while (!stopServerKey) {
        fd_set socketsSet;
        FD_ZERO(&socketsSet);
        FD_SET(server->sock_, &socketsSet);


        if(select(server->sock_+1, &socketsSet, 0, 0, &tv) < 0) {
            perror("select\n");
            continue;
        }
        if (FD_ISSET(server->sock_, &socketsSet)) {
            int clientSocket = accept(server->sock_, NULL, NULL);
            if (clientSocket < 0) {
                perror("accept 1\n");
                continue;
            }

            int clientReserveSocket = accept(server->sock_, NULL, NULL);
            if (clientReserveSocket < 0) {
                perror("accept 2\n");
                continue;
            }

            server->clientsCount_++;
            pthread_t clThread;
            Client *client = new Client(clientSocket,clientReserveSocket, clThread);
            pthread_create(&clThread, NULL, clientThread, client);
            server->pushClient(*client);
        }
    }
    close(server->sock_);
    return NULL;
}

// Listening clients message
void * Server::clientThread(void *arg) {
    Client* client = (Client*)arg;
    char buff[255];
    char serverMsg[3] =  { 'o','k','\0'};
    QString tmp; // to form
    bool stopClientKey = false;

    while (!stopServerKey && !stopClientKey) {
        recvData(client->getSock(),buff,255);
        tmp = buff;
        sendData(client->getSock(),serverMsg);
        if (tmp == "start") {
            tmp = buff;
            emit winh->startSignal();
        }
        if (tmp == "stop") {
            tmp = buff;
            emit winh->stopSignal();
        }
        if (tmp == "restart") {
            tmp = buff;
            emit winh->restartSignal();
        }
        if (tmp == "setTime") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->setTimeSignal(tmp);
        }
        if (tmp == "setTeamOne") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = "";
            tmp = buff;
            emit winh->setTeamOneSignal(tmp);
        }
        if (tmp == "setTeamTwo") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->setTeamTwoSignal(tmp);
        }
        if (tmp == "setPeriod") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->setPeriodSignal(tmp);
        }
        if (tmp == "addGoalOne") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->addGoalOneSignal(tmp);
        }
        if (tmp == "addGoalTwo") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->addGoalTwoSignal(tmp);
        }
        if (tmp == "deleteGoalOne") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->deleteGoalOneSignal(tmp);
        }
        if (tmp == "deleteGoalTwo") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->deleteGoalTwoSignal(tmp);
        }
        if (tmp == "cancelDeleteOne") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->cancelDeleteOneSignal(tmp);
        }
        if (tmp == "cancelDeleteTwo") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff;
            emit winh->cancelDeleteTwoSignal(tmp);
        }
        if (tmp == "deletePlayerOne") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff; // name
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            QString tmp2 = buff; // time
            emit winh->deletePlayerOneSignal(tmp, tmp2);
        }
        if (tmp == "deletePlayerTwo") {
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            tmp = buff; // name
            recvData(client->getSock(),buff,255);
            sendData(client->getSock(),serverMsg);
            QString tmp2 = buff; // time
            emit winh->deletePlayerTwoSignal(tmp, tmp2);
        }
        if (tmp == "close") {
            close(client->getSock());
            close(client->getReserveSock());
            stopClientKey = true;
        }
    }
    return NULL;
}






























