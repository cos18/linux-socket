#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "utils.h"
#include "address.h"

struct sockaddr_in *get_sockaddr(char *fulladdr)
{
    char *dotdot = strchr(fulladdr, ':');
    char *ip = strndup(fulladdr, dotdot - fulladdr);
    in_addr_t ip_number = inet_addr(ip);
    free(ip);
    if (!is_string_num(dotdot + 1) || ip_number == INADDR_NONE)
        return (NULL);
    struct sockaddr_in *result = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    result->sin_family = AF_INET;
    result->sin_port = htons(atoi(dotdot + 1));
    inet_pton(AF_INET, ip, &(result->sin_addr));
    free(ip);
    return (result);
}