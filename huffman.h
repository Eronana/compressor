#ifndef _H_HUFFMAN_
#define _H_HUFFMAN_
#include "compressor.h"
#include <vector>
void huffman(
    std::vector<WORD> &d_buf, std::vector<BYTE> &l_buf,
    std::vector<WORD> &tree,
    std::vector<LenSizeType> &len_size,
    std::vector<BYTE> &bit_stream);
#endif