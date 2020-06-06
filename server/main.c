#include "simple_socket.h"
#include "utils.h"

void start_server(int port, char *file_name)
{
    int err_code;
    char *message;
    int8_t server_sock, client_sock;

    if ((server_sock = create_ipv4_server(port, false)) == FALSE)
        return err_print(ERR_SERVER_CREATE_FAIL);
    printf("서버를 실행했습니다!\n클라이언트의 요청을 기다리는 중...\n");
    listen(server_sock, BACKLOG);
    if ((client_sock = accept_connection(server_sock, NULL, NULL)) == FALSE)
        err_code = ERR_SERVER_ACCEPT_FAIL;
    else
    {
        if ((err_code = recv_string(client_sock, &message)) == TRUE)
        {
            printf("클라이언트에게 요청을 받았습니다!\nClient : %s\n", message);
            free(message);
            if ((err_code = split_send(client_sock, file_name)) == TRUE)
                printf("\n전송이 완료되었습니다!\n");
        }
    }
    printf("서버를 종료합니다.\n");
    close(server_sock);
    if (err_code != TRUE)
        err_print(err_code);
}

int main(int argc, char **argv)
{
    int test_fd;
    int port;
    if (argc != 3 || (port = get_port_num(argv[1])) == FALSE)
    {
        printf("프로그램 실행 방식이 잘못되었습니다.\n");
        printf("사용법 : %s (포트번호) (전송할 파일이름)\n", argv[0]);
        return (-1);
    }
    if ((test_fd = open(argv[2], O_RDONLY)) < 0)
    {
        printf("%s 파일이 존재하지 않습니다.\n", argv[2]);
        return (-1);
    }
    close(test_fd);
    start_server(port, argv[2]);
}