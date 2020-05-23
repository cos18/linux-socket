#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <unistd.h>
#include "utils.h"
#include "address.h"

int main(int argc, char **argv)
{
    struct sockaddr_in *servaddr;
    int socket_fd;
    int status = FALSE;
    char buf[BUFF_SIZE];

    if (argc != 2 || (servaddr = get_sockaddr(argv[1])) == NULL)
    {
        printf("프로그램 실행 방식이 잘못되었습니다.\n");
        printf("사용법 : %s (IP주소):(포트번호)\n", argv[0]);
        return (-1);
    }
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("소켓 생성에 실패했습니다!\n");
        free(servaddr);
        return (-1);
    }
    if (connect(socket_fd, (struct sockaddr *)servaddr, sizeof(*servaddr)) < 0)
    {
        printf("서버와의 연결에 실패했습니다!\n");
        return -1;
    }
    printf("서버와의 연결에 성공했습니다!\n");
    socket_write(socket_fd, "Hello Server\n");
    while (status)
    {
        switch (socket_read(socket_fd, buf))
        {
        case READ_SUCCESS:
            printf("%s\n", buf);
            socket_write(socket_fd, "");
        case READ_END:
        case READ_ERR:
        default:
            close(socket_fd);
            status = FALSE;
        }
    }
    close(socket_fd);
    free(servaddr);
}