#include <stdio.h>
#include "simple_socket.h"
#include "utils.h"

void start_server(int port)
{
    int8_t server_sock, client_sock;
    uint8_t header[HEADER_LENGTH];
    uint8_t *raw_data;
    uint64_t data_len;
    FILE *fp;

    if ((server_sock = create_ipv4_server(port, false)) == FALSE)
        return err_print(ERR_SERVER_CREATE_FAIL);
    listen(server_sock, BACKLOG);
    if ((client_sock = accept_connection(server_sock, NULL, NULL)) == FALSE)
        return err_print(ERR_SERVER_ACCEPT_FAIL);

    /* Receive the header containing the file's size and 
	allocate a buffer to store the data */
    recvall(client_sock, header, HEADER_LENGTH, NULL, NULL);
    data_len = decode_64bit(header);
    raw_data = malloc(data_len);

    /* Finally, receive the raw data and write it to a file */
    recvall(client_sock, raw_data, data_len, NULL, NULL);
    fp = fopen("success.png", "w");
    fwrite(raw_data, 1, data_len, fp);
    fclose(fp);
}

int main(int argc, char **argv)
{
    int port;
    if (argc != 2 || (port = get_port_num(argv[1])) == FALSE)
    {
        printf("프로그램 실행 방식이 잘못되었습니다.\n");
        printf("사용법 : %s (포트번호)\n", argv[0]);
        return (-1);
    }
    start_server(port);
}