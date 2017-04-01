#ifndef _H_COMPRESSOR_
#define _H_COMPRESSOR_

typedef unsigned char BYTE;
typedef unsigned short WORD;
#ifdef __APPLE__
typedef unsigned int DWORD;
#else
typedef unsigned long DWORD;
#endif
const int MAX_WINDOW_SIZE = (WORD)0xFFFFFFFF - 256;
const int MIN_REPEAT_LENGTH = 3;
const int MAX_REPEAT_LENGTH = 255 + MIN_REPEAT_LENGTH;

struct LenSizeType
{
    WORD len,size;
};

DWORD getBufferSize(DWORD size);
DWORD compress(BYTE *dest, BYTE *src,DWORD size,int lazy_match,int prev_length);
void uncompress(BYTE *dest,BYTE *src);
#endif
