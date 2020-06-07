#include "simple_socket.h"
#include "utils.h"

int send_string(int32_t sock, char *str)
{
    int is_last;
    u_int8_t raw_data[HEADER_LENGTH + BUFFER_SIZE] = {0};
    u_int16_t sended = 0;
    u_int64_t total = 0;
    u_int64_t len;

    encode_16bit(add_header_flag(0, STRING_SEND_START), raw_data);
    sendall(sock, raw_data, HEADER_LENGTH);

    len = strlen(str);
    while (total < len)
    {
        memset(raw_data, 0, HEADER_LENGTH + BUFFER_SIZE);
        is_last = (BUFFER_SIZE < len - total) ? FALSE : TRUE;
        sended = is_last ? len - total : BUFFER_SIZE;
        for (int i = 0; i < sended; i++)
            raw_data[HEADER_LENGTH + i] = str[total + i];
        encode_16bit(add_header_flag(sended, (is_last ? STRING_SEND_END : STRING_SEND)), raw_data);
        if (!sendall(sock, raw_data, sended + HEADER_LENGTH))
            return ERR_STRING_SEND_FAIL;
        total += sended;
    }
    return TRUE;
}