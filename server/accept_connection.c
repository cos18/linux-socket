#include "simple_socket.h"
#include "utils.h"

int32_t accept_connection(int32_t server_sock, struct sockaddr *addr,
                          socklen_t *addr_len)
{
    int32_t sock;
    struct addrinfo addr_lost;

    if (addr == NULL)
        sock = accept(server_sock, (struct sockaddr *)addr_lost.ai_addr, &addr_lost.ai_addrlen);
    else
        sock = accept(server_sock, (struct sockaddr *)addr, addr_len);
    if (sock < 0)
        return FALSE;
    recvall(sock, NULL, 0, NULL, NULL);
    return sock;
}