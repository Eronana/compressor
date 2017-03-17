#ifndef _H_LZ77_
#define _H_LZ77_
#include "compressor.h"
#include <vector>
void lz77(std::vector<WORD> &d_buf, std::vector<BYTE> &l_buf, BYTE *src, DWORD size,int lazy_match,int prev_length);
#endif
