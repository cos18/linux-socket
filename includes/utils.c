#include <stdio.h>
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