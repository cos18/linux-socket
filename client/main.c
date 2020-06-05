#include "simple_socket.h"
#include "utils.h"

void receive_to_server(svr_add *add, char *file_name)
{
    int8_t server_sock;

    server_sock = connect_to_server(add);
    split_recv(server_sock, file_name);
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