#include <cstring>
#include "lzhash.h"

int LZHash::lz77_hash(int idx)
{
    return ((data[idx]<<16)|(data[idx+1]<<8)|data[idx+2])%HASH_MOD;
}
int LZHash::index_map(int idx)
{
    return idx%MAX_WINDOW_SIZE;
}
int LZHash::find_head(int idx)
{
    int hash=lz77_hash(idx);
    return head[hash];
}
int LZHash::find_next(int idx)
{
    int n=prev[index_map(idx)];
    if(n>idx)n=-1;
    return n;
}

LZHash::LZHash(BYTE *data,int d_size,int &next):d_size(d_size),next(next),data(data)
{
    head=new int[HASH_MOD];
    prev=new int[MAX_WINDOW_SIZE];
    memset(head,-1,sizeof(*head)*HASH_MOD);
    memset(prev,-1,sizeof(*prev)*MAX_WINDOW_SIZE);
}

LZHash::~LZHash()
{
    delete[] head;
    delete[] prev;
}

void LZHash::insert(int idx)
{
    int hash=lz77_hash(idx);
    int node=head[hash];
    if(node==-1) head[hash]=idx;
    else
    {
        if(data[idx]==data[idx-3]&&data[idx+1]==data[idx-2]&&data[idx+2]==data[idx-1])return;
        prev[index_map(idx)]=head[hash];
        head[hash]=idx;
    }
}

FindResult LZHash::find(int pos, int prev_length)
{
    FindResult fr={data+pos,1};
    for(int node=find_head(pos);prev_length--&&~node&&next-node<=MAX_WINDOW_SIZE;node=find_next(node))
    {
        int length=0;
        for(int i=node;i<d_size&&length<MAX_REPEAT_LENGTH&&pos+length<d_size&&data[i]==data[pos+length];i++,length++);
        if(length>fr.length)fr={data+node,length};
    }
    return fr;
}
