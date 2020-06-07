#include "simple_socket.h"

void left_shift_array(void *array, u_int64_t array_length, u_int64_t bytes)
{
    int8_t *bytearray = (int8_t *)array;
    u_int64_t i = -1;

    while (++i < array_length - bytes)
        bytearray[i] = bytearray[i + bytes];
    while (i < array_length)
        bytearray[i++] = 0;
}

bool recvall(int32_t sock, void *buffer, int32_t len)
{
    static u_int8_t tmp[MAX_CONNECTIONS + 3][BUFFER_SIZE] = {{0}};
    static u_int16_t tmp_len[MAX_CONNECTIONS + 3] = {0};
    u_int8_t in_buffer[BUFFER_SIZE] = {0};
    u_int8_t *out_buffer = (u_int8_t *)buffer;
    int32_t out_index = 0, in_index = 0, tmp_index = 0;
    int32_t recv_length = 0;

    if (out_buffer == NULL)
    {
        bzero(tmp[sock], BUFFER_SIZE);
        tmp_len[sock] = 0;
    }
    if (tmp_len[sock] > 0)
    {
        while (tmp_index < tmp_len[sock] && out_index < len)
            out_buffer[out_index++] = tmp[sock][tmp_index++];
        left_shift_array(tmp[sock], tmp_len[sock], tmp_index);
        tmp_len[sock] -= tmp_index;
        tmp_index = 0;
    }
    while (out_index < len)
    {
        in_index = 0;
        recv_length = recv(sock, in_buffer, BUFFER_SIZE, 0);
        if (recv_length <= 0)
            return false;
        while (out_index < len && in_index < recv_length)
            out_buffer[out_index++] = in_buffer[in_index++];
    }
    while (in_index < recv_length)
        tmp[sock][tmp_len[sock]++] = in_buffer[in_index++];
    return true;
}