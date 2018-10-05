#include "client.h"

Client::Client(int sock, int reserveSock, pthread_t thread)
{
    this->sock_ = sock;
    this->reserveSock_ = reserveSock;
    this->thread_ = thread;
}
