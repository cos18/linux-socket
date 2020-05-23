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

    if (argc != 2 || (servaddr = get_sockaddr(argv[1])) == NULL)
    {
        printf("프로그램 실행 방식이 잘못되었습니다.\n");
        printf("사용법 : %s (IP주소):(포트번호)", argv[0]);
        return (-1);
    }
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("소켓 생성에 실패했습니다!");
        free(servaddr);
        return (-1);
    }
    printf("try\n");
    // 연결 요청,,
    if (connect(socket_fd, (struct sockaddr *)servaddr, sizeof(*servaddr)) < 0)
    {
        printf("Connection failed !");
        return -1;
    }

    printf("Connection Success !");
    close(socket_fd);
    free(servaddr);
}