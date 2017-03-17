#include "compressor.h"

struct HNode
{
    int value;
    HNode *child[2];
};
HNode *newHNode()
{
    HNode *n=new HNode;
    n->value=-1;
    n->child[0]=n->child[1]=nullptr;
    return n;
}

void releaseHNode(HNode *node)
{
    if(!node)return;
    releaseHNode(node->child[0]);
    releaseHNode(node->child[1]);
    delete node;
}

void build_buffman(HNode *node,int value,int len,int code)
{
    for(int i=len-1;~i;i--)
    {
        int v=!!(code&(1<<i));
        if(!node->child[v])node->child[v]=newHNode();
        node=node->child[v];
    }
    node->value=value;
}


void unlz77(WORD *d_buf,DWORD d_buf_size, BYTE *l_buf, BYTE *src)
{
    int x=0;
    int next=0;
    for(int i=0;i<d_buf_size;i++)
    {
        int dis=d_buf[i]-256;
        if(dis<0) src[next++]=d_buf[i];
        else
        {
            BYTE *buf=src+next-dis;
            for(int j=0;j<l_buf[x]+MIN_REPEAT_LENGTH;j++)src[next++]=buf[j];
            x++;
        }
    }
}

void uncompress(BYTE *dest,BYTE *src)
{
    WORD tree_size=*(WORD*)src;
    src+=2;
    WORD len_size_size=*(WORD*)src;
    src+=2;
    DWORD d_buf_size=*(DWORD*)src;
    src+=4;
    DWORD l_buf_size=*(DWORD*)src;
    src+=4;
    WORD *tree=(WORD*)src;
    src+=tree_size*sizeof(tree[0]);
    LenSizeType *len_size=(LenSizeType*)src;
    src+=len_size_size*sizeof(len_size[0]);
    BYTE *bit_stream=src;


    HNode *huffman=newHNode();

    int code=0,last_len=0;
    for(int i=0,a=0;i<len_size_size;i++)
    {
        int len=len_size[i].len;
        int size=len_size[i].size;
        code<<=(len-last_len);
        last_len=len;
        while(size--)build_buffman(huffman,tree[a++],len,code++);
    }


    WORD *d_buf=new WORD[d_buf_size];
    BYTE *l_buf=new BYTE[l_buf_size];

    int byte_count=0;
    for(int i=0;i<d_buf_size;i++)
    {
        HNode *node=huffman;
        for(;node->value==-1;byte_count++)node=node->child[!!(bit_stream[byte_count/8]&(1<<(7-byte_count%8)))];
        d_buf[i]=node->value;
    }
    for(int i=0;i<l_buf_size;i++)
    {
        HNode *node=huffman;
        for(;node->value==-1;byte_count++)node=node->child[!!(bit_stream[byte_count/8]&(1<<(7-byte_count%8)))];
        l_buf[i]=node->value;
    }
    releaseHNode(huffman);
    unlz77(d_buf,d_buf_size,l_buf,dest);
    delete[] l_buf;
    delete[] d_buf;
}