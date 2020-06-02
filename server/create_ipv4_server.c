#include "simple_socket.h"
#include "utils.h"

int32_t create_ipv4_server(uint16_t server_port, bool set_nonblock)
{
    int32_t sock;
    struct sockaddr_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(server_port);

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        return FALSE;
    if (set_nonblock == true)
        fcntl(sock, F_SETFL, O_NONBLOCK);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        return FALSE;
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return FALSE;
    return sock;
}
