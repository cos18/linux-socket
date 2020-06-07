#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "simple_socket.h"
#include "utils.h"

/**
 * @brief 문자열이 올바른 포트 번호인지 확인후 int로 변환합니다.
 * 올바른 포트 번호는 Well Known Port를 제외한
 * 나머지 포트 번호 범위 (1024~65535)를 말합니다.
 * 
 * @param str 확인해야 할 문자열
 * @return 변환한 포트 번호 or FALSE (0)
 */
int get_port_num(char *str)
{
    int result;
    if (!isdigit(*str) || *str == '0')
        return FALSE;
    result = *str - '0';
    while (*(++str))
    {
        if (!isdigit(*str))
            return FALSE;
        result *= 10;
        result += *str - '0';
    }
    return ((1024 <= result && result <= 65535) ? result : FALSE);
}

/**
 * @brief 에러 코드를 받아 에러 메세지를 출력합니다.
 * 에러 코드는 utils.h에 정의되어 있습니다.
 * 
 * @param errno 발생한 에러 코드
 */
void err_print(int errno)
{
    char *errstr[10] = {
        "",
        "서버를 생성하는 도중 문제가 발생했습니다.",
        "클라이언트의 요청을 받는 도중 문제가 생겼습니다.",
        "올바르지 않은 헤더를 읽어왔습니다.",
        "서버에 접속하는데 실패했습니다. 서버가 접속 가능한지 확인해주세요.",
        "파일을 전송하는 중 오류가 발생핬습니다.",
        "문자열을 전송하는 중 오류가 발생핬습니다.",
        "파일을 수신하는 중 오류가 발생했습니다.",
        "문자열을 수신하는 중 오류가 발생했습니다."};
    printf("ERROR %d : %s\n", errno, errstr[errno]);
}

/**
 * @brief 서버 정보를 문자열로 가지는 svr_add 구조체를 생성합니다
 * 
 * @param str client 프로그램 실행시 들어오는 argv 문자열
 * @return svr_add* (올바르지 않은 문자열의 경우 NULL)
 */
svr_add *create_add(char *str)
{
    svr_add *result;
    char *cut;
    char *ip;
    cut = strchr(str, ':');
    if (cut == NULL || !get_port_num(cut + 1))
        return NULL;
    ip = strndup(str, cut - str);
    if (inet_addr(ip) == INADDR_NONE)
    {
        free(ip);
        return NULL;
    }
    result = (svr_add *)malloc(sizeof(svr_add));
    result->ip = ip;
    result->port = strndup(cut + 1, strlen(cut + 1));
    return (result);
}

/**
 * @brief svr_add 구조체를 동적할당한 부분을 free 시켜줍니다
 * 
 * @param s free할 svr_add 구조체
 */
void free_add(svr_add *s)
{
    free(s->ip);
    free(s->port);
    free(s);
}

u_int16_t add_header_flag(u_int16_t header, u_int8_t flag)
{
    return header | (flag << (HEADER_LENGTH * 8 - HEADER_FLAG_BIT));
}

u_int8_t get_header_flag(u_int16_t *header)
{
    u_int8_t result;
    result = *header >> (HEADER_LENGTH * 8 - HEADER_FLAG_BIT);
    *header &= ((1 << (HEADER_LENGTH * 8 - HEADER_FLAG_BIT)) - 1);
    return result;
}

char *ft_strnul(void)
{
    char *result;
    result = (char *)malloc(1);
    *result = '\0';
    return (result);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *result;
    int locate;

    if (!s1 || !s2)
        return (NULL);
    result = (char *)malloc(strlen(s1) + strlen(s2) + 1);
    if (result)
    {
        locate = 0;
        while (*s1)
        {
            result[locate++] = *s1;
            s1++;
        }
        while (*s2)
        {
            result[locate++] = *s2;
            s2++;
        }
        result[locate] = '\0';
    }
    return (result);
}

char *ft_strchr(const char *s, int c)
{
    int is_end;
    char *now;

    is_end = 0;
    now = (char *)s;
    while (1)
    {
        if (*now == c)
            break;
        if (*now == '\0')
        {
            is_end = 1;
            break;
        }
        now++;
    }
    return ((is_end) ? NULL : now);
}

char *ft_strpush(char *s, int push)
{
    int locate;

    locate = 0;
    while (s[locate + push])
    {
        s[locate] = s[locate + push];
        locate++;
    }
    while (s[locate])
        s[locate++] = '\0';
    return (s);
}

void loading(u_int64_t total, u_int64_t file_size)
{
    int progress = total * 100 / file_size;
    printf("\r진행중 [");
    for (int i = 1; i <= 20; i++)
        printf("%c", (i * 5 <= progress) ? '=' : ' ');
    printf("] %d%%", progress);
    fflush(stdout);
}
