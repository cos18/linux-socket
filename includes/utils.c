#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "utils.h"

/**
 * @brief 문자열이 올바른 포트 번호인지 확인후 int로 변환합니다.
 * 올바른 포트 번호는 Well Known Port를 제외한
 * 나머지 포트 번호 범위 (1024~65535)를 말합니다.
 * 
 * @param str 확인해야 할 문자열
 * @return 변환한 포트 번호 or FALSE (0)
 */
int is_string_num(char *str)
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
        "클라이언트의 요청을 받는 도중 문제가 생겼습니다."};
    printf("ERROR : %s\n", errstr[errno]);
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
    if (cut == NULL || !is_string_num(cut + 1))
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
