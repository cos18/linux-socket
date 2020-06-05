#include <sys/stat.h>
#include "simple_socket.h"
#include "utils.h"

int split_send(int8_t socket, char *file_name)
{
    int is_last;
    FILE *fp;
    struct stat info;
    uint8_t raw_data[HEADER_LENGTH + BUFFER_SIZE];
    uint16_t sended = 0;
    uint64_t total = 0;

    fp = fopen(file_name, "r");
    fstat(fileno(fp), &info);
    while (total < info.st_size)
    {
        memset(raw_data, 0, HEADER_LENGTH + BUFFER_SIZE);
        is_last = (BUFFER_SIZE < info.st_size - total) ? FALSE : TRUE;
        sended = is_last ? info.st_size - total : BUFFER_SIZE;
        fread(raw_data + HEADER_LENGTH, 1, sended, fp);
        encode_16bit((is_last ? sended | (1 << (HEADER_LENGTH * 8 - 1)) : sended), raw_data);
        sendall(socket, raw_data, sended + HEADER_LENGTH);
        total += sended;
    }
    fclose(fp);
    return TRUE;
};