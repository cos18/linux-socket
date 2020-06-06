#include "simple_socket.h"
#include "utils.h"

int split_recv(int8_t socket, char *file_name)
{
    int continued = TRUE;
    int errno = 0;
    FILE *fp = NULL;
    uint8_t header[HEADER_LENGTH];
    uint8_t raw_data[BUFFER_SIZE];
    uint8_t flag;
    uint16_t data_len;

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
        case FILE_SEND_START:
            fp = fopen(file_name, "w");
            continue;
        case FILE_SEND_END:
            continued = FALSE;
        case FILE_SEND:
            break;
        default:
            continued = FALSE;
            errno = ERR_DIFF_HEADER_FLAG;
            continue;
        }
        memset(raw_data, 0, BUFFER_SIZE);
        if (!recvall(socket, raw_data, data_len))
        {
            errno = ERR_FILE_RECV_FAIL;
            break;
        }
        fwrite(raw_data, 1, data_len, fp);
    }
    if (fp)
        fclose(fp);
    return (errno ? errno : TRUE);
};