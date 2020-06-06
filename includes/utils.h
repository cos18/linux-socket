#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

#define FD_SIZE 1024
#define READ 1
#define READ_EOF 0
#define ERROR -1
#define READ_BUFFER 2048

#define ERR_SERVER_CREATE_FAIL 1
#define ERR_SERVER_ACCEPT_FAIL 2
#define ERR_DIFF_HEADER_FLAG 3
#define ERR_CLIENT_CONNECT_FAIL 4
#define ERR_FILE_SEND_FAIL 5
#define ERR_STRING_SEND_FAIL 6
#define ERR_FILE_RECV_FAIL 7
#define ERR_STRING_RECV_FAIL 8

#define HEADER_FLAG_BIT 3
#define SEND_START 0
#define STRING_SEND_START 1
#define STRING_SEND 2
#define STRING_SEND_END 3
#define FILE_SEND_START 4
#define FILE_SEND 5
#define FILE_SEND_END 6
#define SEND_END 7

typedef struct svr_address
{
    char *ip;
    char *port;
} svr_add;

int get_port_num(char *str);
void err_print(int errno);
svr_add *create_add(char *str);
void free_add(svr_add *s);
u_int16_t add_header_flag(u_int16_t header, u_int8_t flag);
u_int8_t get_header_flag(u_int16_t *header);
char *ft_strnul(void);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strchr(const char *s, int c);
char *ft_strpush(char *s, int push);
void loading(u_int64_t total, u_int64_t file_size);

int get_next_line(int fd, char **line);

int split_send(int8_t socket, char *file_name);
int split_recv(int8_t socket, char *file_name);
int send_string(int32_t sock, char *str);
int recv_string(int8_t socket, char **str);

#endif