#include "simple_socket.h"
#include "utils.h"

int recv_string(int8_t socket, char **str)
{
    int continued = TRUE;
    int errno = 0;
    uint8_t header[HEADER_LENGTH];
    uint8_t raw_data[BUFFER_SIZE + 1];
    uint8_t flag;
    uint16_t data_len;
    char *tmp;

    *str = (char *)malloc(1);
    **str = 0;
    while (continued)
    {
        memset(header, 0, HEADER_LENGTH);
        if (!recvall(socket, header, HEADER_LENGTH))
        {
            errno = ERR_STRING_RECV_FAIL;
            break;
        }
        data_len = decode_16bit(header);
        flag = get_header_flag(&data_len);
        switch (flag)
        {
        case STRING_SEND_START:
            continue;
        case STRING_SEND_END:
            continued = FALSE;
        case STRING_SEND:
            break;
        default:
            continued = FALSE;
            errno = ERR_DIFF_HEADER_FLAG;
            continue;
        }
        memset(raw_data, 0, BUFFER_SIZE);
        if (!recvall(socket, raw_data, data_len))
        {
            errno = ERR_STRING_RECV_FAIL;
            break;
        }
        raw_data[data_len] = 0;
        tmp = ft_strjoin(*str, (char *)raw_data);
        free(*str);
        *str = tmp;
    }
    return (errno ? errno : TRUE);
};