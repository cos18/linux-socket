#include "simple_socket.h"
#include "utils.h"

int32_t accept_connection(int32_t server_sock)
{
    int32_t sock;
    struct sockaddr_in clientaddr;
    int clilen = sizeof(clientaddr);

    sock = accept(server_sock, (struct sockaddr *)&clientaddr, &clilen);
    if (sock < 0)
        return FALSE;
    recvall(sock, NULL, 0);
    return sock;
}