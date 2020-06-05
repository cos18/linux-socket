#include "simple_socket.h"

int32_t connect_to_server(svr_add *add)
{
    int32_t sock;
    struct addrinfo hints = {0};
    struct addrinfo *servinfo, *p;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(add->ip, add->port, &hints, &servinfo) != 0)
        return FALSE;
    for (p = servinfo; p != NULL; p = p->ai_next)
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) > 0)
        {
            if (connect(sock, p->ai_addr, p->ai_addrlen) == 0)
                break;
            else
                close(sock);
        }
    if (p == NULL)
        sock = -1;
    freeaddrinfo(servinfo);
    return sock;
}