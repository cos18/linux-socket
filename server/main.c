#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char **argv)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t addrlen = sizeof(cliaddr);
    int socket_fd;
    int accept_socket;
    int status = TRUE;
    char buf[BUFF_SIZE];

    if (argc != 2 || !is_string_num(argv[1]))
    {
        printf("프로그램 실행 방식이 잘못되었습니다.\n");
        printf("사용법 : %s (포트번호)\n", argv[0]);
        return (-1);
    }
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("소켓 생성에 실패했습니다!");
        return (-1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("바인드에 실패했습니다!");
        return (-1);
    }
    printf("포트 %s번이 열리면서 바인드되었습니다.\n", argv[1]);

    if (-1 == listen(socket_fd, 1))
    {
        printf("listen() 실행 실패\n");
        return (-1);
    }
    printf("클라이언트의 요청을 기다리는 중입니다...\n");
    accept_socket = accept(socket_fd, (struct sockaddr *)&cliaddr, &addrlen);
    if (accept_socket < 0)
    {
        printf("클라이언트 요청 처리 중 오류가 발생했습니다");
        return (-1);
    }
    printf("클라이언트와 연결에 성공했습니다\n");
    while (status)
    {
        switch (socket_read(accept_socket, buf))
        {
        case READ_SUCCESS:
            printf("%s\n", buf);
            socket_write(accept_socket, "Hello Client\n");
            break;
        case READ_END:
        case READ_ERR:
        default:
            close(socket_fd);
            status = FALSE;
        }
    }
    close(socket_fd);
    return 0;
}