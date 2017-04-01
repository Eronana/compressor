#include <vector>
#include <cstring>
#include "compressor.h"
#include "lzhash.h"
#include "lz77.h"
#include "huffman.h"


DWORD getBufferSize(DWORD size)
{
    size*=1.5;
    if(size<2048)size=2048;
    return size;
}

DWORD compress(BYTE *dest, BYTE *src,DWORD size,int lazy_match,int max_chain)
{
    std::vector<WORD> d_buf;
    std::vector<BYTE> l_buf;
    lz77(d_buf,l_buf,(BYTE*)src,size,lazy_match,max_chain);

    std::vector<WORD> tree;
    std::vector<LenSizeType> len_size;
    std::vector<BYTE> bit_stream;
    huffman(d_buf,l_buf,tree,len_size,bit_stream);

    WORD tree_size=tree.size();
    WORD len_size_size=len_size.size();
    DWORD bit_stream_size=bit_stream.size();

    BYTE *dest_bak=dest;
    *(WORD*)dest=tree_size;
    dest+=2;
    *(WORD*)dest=len_size_size;
    dest+=2;
    *(DWORD*)dest=d_buf.size();
    dest+=4;
    *(DWORD*)dest=l_buf.size();
    dest+=4;
    
    int tree_bsize=tree_size*sizeof(tree[0]);
    int len_size_bsize=len_size_size*sizeof(len_size[0]);

    memcpy(dest,&tree[0],tree_bsize);
    dest+=tree_bsize;
    memcpy(dest,&len_size[0],len_size_bsize);
    dest+=len_size_bsize;
    memcpy(dest,&bit_stream[0],bit_stream_size);

    dest+=bit_stream_size;
    return dest-dest_bak;
}
