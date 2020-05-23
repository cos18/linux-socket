#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>

#define BUFF_SIZE 1024
#define READ_ERR 0
#define READ_SUCCESS 1
#define READ_END 2
#define TRUE 1
#define FALSE 0

int is_string_num(char *str);
void socket_write(int socket, char *data);
int socket_read(int socket, char *buf);

#endif