#include "simple_socket.h"
#include "utils.h"

void receive_to_server(svr_add *add, char *file_name)
{
    char *hello;
    int errno;
    int8_t server_sock;

    printf("서버에게 보낼 인사말을 입력해주세요.\n입력하지 않고 엔터만 입력하면 'Hello Server'가 전송됩니다.\n");
    get_next_line(0, &hello);
    if (strlen(hello) == 0)
    {
        free(hello);
        hello = strdup("Hello Server");
    }
    printf("입력하신 주소로 접속중입니다...\n");
    server_sock = connect_to_server(add);
    if (server_sock == -1)
    {
        free(hello);
        return err_print(ERR_CLIENT_CONNECT_FAIL);
    }
    errno = send_string(server_sock, hello);
    if (errno == TRUE)
    {
        printf("접속 후 서버에게 '%s'라고 보냈습니다.\n수신을 시작합니다.\n", hello);
        if ((errno = split_recv(server_sock, file_name)) == TRUE)
            printf("수신이 완료되었습니다\n");
    }
    printf("통신을 종료합니다\n");
    free(hello);
    close(server_sock);
    if (errno != TRUE)
        err_print(errno);
}

int main(int argc, char **argv)
{
    int test_fd;
    svr_add *add;
    if (argc != 3 || (add = create_add(argv[1])) == NULL)
    {
        printf("프로그램 실행 방식이 잘못되었습니다.\n");
        printf("사용법 : %s (IP주소):(포트번호) (저장될 파일 이름)\n", argv[0]);
        return (-1);
    }
    if ((test_fd = open(argv[2], O_RDONLY)) != -1)
    {
        close(test_fd);
        printf("%s 파일이 이미 존재합니다.\n겹치지 않은 파일명을 입력해주세요.", argv[2]);
        return (-1);
    }
    receive_to_server(add, argv[2]);
    free_add(add);
}