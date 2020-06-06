#include <sys/stat.h>
#include "simple_socket.h"
#include "utils.h"

int split_send(int8_t socket, char *file_name)
{
    int is_last;
    FILE *fp;
    struct stat info;
    uint8_t raw_data[HEADER_LENGTH + BUFFER_SIZE] = {0};
    uint16_t sended = 0;
    uint64_t total = 0;

    printf("%s 파일 전송을 시작합니다\n", file_name);

    fp = fopen(file_name, "r");
    fstat(fileno(fp), &info);

    encode_16bit(add_header_flag(0, FILE_SEND_START), raw_data);
    encode_64bit((uint64_t)info.st_size, raw_data + HEADER_LENGTH);
    sendall(socket, raw_data, HEADER_LENGTH + 8);

    while (total < (uint64_t)info.st_size)
    {
        memset(raw_data, 0, HEADER_LENGTH + BUFFER_SIZE);
        is_last = (BUFFER_SIZE < info.st_size - total) ? FALSE : TRUE;
        sended = is_last ? info.st_size - total : BUFFER_SIZE;
        fread(raw_data + HEADER_LENGTH, 1, sended, fp);
        encode_16bit(add_header_flag(sended, (is_last ? FILE_SEND_END : FILE_SEND)), raw_data);
        if (!sendall(socket, raw_data, sended + HEADER_LENGTH))
            return ERR_FILE_SEND_FAIL;
        total += sended;
        loading(total, info.st_size);
    }
    fclose(fp);
    return TRUE;
};