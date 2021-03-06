#ifndef SIMPLE_SOCKET_H
#define SIMPLE_SOCKET_H

#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include "utils.h"

#define MAX_CONNECTIONS 64
#define BACKLOG 128
#define BUFFER_SIZE 1460
#define HEADER_LENGTH 2

int32_t create_ipv4_server(u_int16_t server_port, bool set_nonblock);
int32_t connect_to_server(svr_add *add);
int32_t accept_connection(int32_t server_sock);
bool sendall(int32_t sock, void *buffer, int32_t len);
bool recvall(int32_t sock, void *buffer, int32_t len);

void encode_64bit(u_int64_t n, u_int8_t *byetarray);
void encode_16bit(u_int16_t n, u_int8_t *byetarray);
u_int64_t decode_64bit(u_int8_t *byetarray);
u_int16_t decode_16bit(u_int8_t *byetarray);

#endif
