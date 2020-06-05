#include "simple_socket.h"
#include "utils.h"

int split_recv(int8_t socket, char *file_name)
{
    int continued = TRUE;
    FILE *fp;
    uint8_t header[HEADER_LENGTH];
    uint8_t raw_data[HEADER_LENGTH + BUFFER_SIZE];
    uint16_t data_len;

    fp = fopen(file_name, "w");
    while (continued)
    {
        memset(raw_data, 0, HEADER_LENGTH + BUFFER_SIZE);
        recvall(socket, header, HEADER_LENGTH);
        data_len = decode_16bit(header);
        if (data_len & (1 << (HEADER_LENGTH * 8 - 1)))
        {
            continued = FALSE;
            data_len &= ((1 << (HEADER_LENGTH * 8 - 1)) - 1);
        }
        recvall(socket, raw_data, data_len);
        fwrite(raw_data, 1, data_len, fp);
    }
    fclose(fp);
    return TRUE;
};