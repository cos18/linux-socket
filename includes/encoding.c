#include "simple_socket.h"

void encode_64bit(u_int64_t n, u_int8_t *byetarray)
{
    u_int8_t shift = 56;
    for (u_int16_t i = 0; i < 8; i++)
    {
        byetarray[i] = (n >> shift) & 255;
        shift -= 8;
    }
}

void encode_16bit(u_int16_t n, u_int8_t *byetarray)
{
    u_int8_t shift = 8;
    for (u_int16_t i = 0; i < 2; i++)
    {
        byetarray[i] = (n >> shift) & 255;
        shift -= 8;
    }
}

u_int64_t decode_64bit(u_int8_t *byetarray)
{
    u_int64_t decoded = 0;
    u_int8_t shift = 56;
    for (u_int16_t i = 0; i < 8; i++)
    {
        decoded = decoded | (u_int64_t)byetarray[i] << shift;
        shift -= 8;
    }
    return decoded;
}

u_int16_t decode_16bit(u_int8_t *byetarray)
{
    u_int16_t decoded = 0;
    u_int8_t shift = 8;
    for (u_int16_t i = 0; i < 2; i++)
    {
        decoded = decoded | (byetarray[i] << shift);
        shift -= 8;
    }
    return decoded;
}