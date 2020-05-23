#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

/**
 * @brief 문자열이 올바른 숫자인지 확인합니다.
 * 올바른 숫자란, atoi로 변환시 중단 없이 원하는 값이 나오는 것을 말합니다.
 * 
 * @param str 확인해야 할 문자열
 * @return TRUE (1) or FALSE (0)
 */
int is_string_num(char *str)
{
    if (!isdigit(*str) || *str == '0')
        return FALSE;
    while (*(++str))
    {
        if (!isdigit(*str))
            return FALSE;
    }
    return TRUE;
}

/**
 * @brief 소켓을 통해 데이터를 전송합니다.
 * 
 * @param socket 소켓 FD
 * @param data 전송해야 할 데이터 (문자열)
 */
void socket_write(int socket, char *data)
{
    char buf[BUFF_SIZE];
    memset(buf, 0, BUFF_SIZE);
    memcpy(buf, data, strlen(data));
    write(socket, buf, BUFF_SIZE);
    printf("%s\n", buf);
}

/**
 * @brief 소켓을 통해 데이터를 수신합니다.
 * 
 * @param socket 소켓 FD
 * @param buf 받을 데이터를 저장할 배열 (버퍼 사이즈만큼 할당되어있어야 함)
 * @return int READ status 코드
 */
int socket_read(int socket, char *buf)
{
    if (read(socket, buf, BUFF_SIZE) == -1)
        return READ_ERR;
    return (*buf ? READ_SUCCESS : READ_END);
}
