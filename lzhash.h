#ifndef _H_LZHASH_
#define _H_LZHASH_
#include "compressor.h"

struct FindResult
{
    BYTE *position;
    int length;
};

class LZHash
{
    const int d_size;
    const int &next;
    const int HASH_MOD=100007;
    BYTE *data;
    int *head,*prev;

    int lz77_hash(int idx);
    int index_map(int idx);
    int find_head(int idx);
    int find_next(int idx);
public:
    LZHash(BYTE *data,int d_size,int &next);
    ~LZHash();
    void insert(int idx);
    FindResult find(int pos, int prev_length);
};

#endif
