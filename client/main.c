#include <stdio.h>
#include <sys/stat.h>
#include "simple_socket.h"
#include "utils.h"

#define HEADER_LENGTH 8

void send_to_server(svr_add *add)
{
    FILE *fp;
    struct stat info;
    uint8_t *raw_data;
    int8_t server_sock;

    fp = fopen("cute.png", "r");
    fstat(fileno(fp), &info);
    raw_data = malloc(HEADER_LENGTH + info.st_size);
    fread(raw_data + HEADER_LENGTH, 1, info.st_size, fp);
    fclose(fp);

    /* Encode the size of the file in the 8 first bytes of our buffer
	and then send the total to the server */
    encode_64bit(info.st_size, raw_data);
    server_sock = connect_to_server(add);
    sendall(server_sock, raw_data, HEADER_LENGTH + info.st_size, NULL, 0);
}

int main(int argc, char **argv)
{
    svr_add *add;
    if (argc != 2 || (add = create_add(argv[1]) == NULL))
    {
        printf("프로그램 실행 방식이 잘못되었습니다.\n");
        printf("사용법 : %s (IP주소):(포트번호)\n", argv[0]);
        return (-1);
    }
    send_to_server(add);
    free_add(add);
}