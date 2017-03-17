#include "lz77.h"
#include "lzhash.h"

bool isSame(BYTE *a, BYTE *b, int size)
{
    for (int i = 0; i < size; i++)if (a[i] != b[i])return false;
    return true;
}

void do_next(int n,int &l,int &r,int &next,LZHash &lz_hash)
{
    next+=n;
    for(int i=0;i<n;i++)lz_hash.insert(r++);
    l=std::max(0,r-MAX_WINDOW_SIZE);
}

void lz77(std::vector<WORD> &d_buf, std::vector<BYTE> &l_buf, BYTE *src, DWORD size,int lazy_match,int prev_length)
{
    d_buf.clear();
    l_buf.clear();
    if(prev_length<=0)
    {
        d_buf.resize(size);
        for(int i=0;i<size;i++)d_buf[i]=src[i];
        return;
    }

    d_buf.reserve(size);
    l_buf.reserve(size);

    if(prev_length>MAX_WINDOW_SIZE)prev_length=MAX_WINDOW_SIZE;
    if(lazy_match>MAX_REPEAT_LENGTH)lazy_match=MAX_REPEAT_LENGTH;
    int l = 0, r = 0;
    int next = 0;
    LZHash lz_hash(src,size,next);
    while (next < size)
    {
        FindResult fr=lz_hash.find(next,prev_length);
        int is_next = 0;
        while(fr.length<lazy_match&&next<size)
        {
            do_next(1,l,r,next,lz_hash);
            is_next = 1;
            auto fr2 = lz_hash.find(next,prev_length);
            if(fr2.length>fr.length+2)
            {
                fr=fr2;
                d_buf.push_back(src[next-1]);
                is_next = 0;
            }
            else break;
        }
        
        if (fr.length >= MIN_REPEAT_LENGTH)
        {
            d_buf.push_back(next-is_next-(fr.position - src) + 256);
            l_buf.push_back(fr.length-MIN_REPEAT_LENGTH);
        }
        else
        {
            for (int i = 0; i < fr.length; i++)d_buf.push_back(fr.position[i]);
        }
        do_next(fr.length-is_next,l,r,next,lz_hash);
    }
}
