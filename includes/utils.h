#ifndef UTILS_H
#define UTILS_H

#define TRUE 1
#define FALSE 0
#define HEADER_LENGTH 8

#define ERR_SERVER_CREATE_FAIL 1
#define ERR_SERVER_ACCEPT_FAIL 2

typedef struct svr_address
{
    char *ip;
    char *port;
} svr_add;

int get_port_num(char *str);
void err_print(int errno);
svr_add *create_add(char *str);
void free_add(svr_add *s);

#endif