#include "huffman.h"
#include "bitstream.h"
#include <map>
#include <queue>

struct Node
{
    int value;
    int freq;
    Node *left,*right;
    Node(){}
    Node(int value,int freq):value(value),freq(freq),left(nullptr),right(nullptr){}
    Node(Node *left,Node *right):freq(left->freq+right->freq),left(left),right(right){}
    ~Node()
    {
        delete left;
        delete right;
    }
};
struct Node_CMP  
{   
    bool operator()(const Node *a, const Node *b) const  
    {  
        return a->freq>b->freq;
    }  
};

void get_tree(Node *node,std::map<WORD,std::vector<int>> &mcode,int len)
{
    if(!node->left&&!node->right)mcode[len].push_back(node->value);
    else
    {
        len++;
        if(node->left)get_tree(node->left,mcode,len);
        if(node->right)get_tree(node->right,mcode,len);
    }
}


struct BitCode
{
    int len;
    int code;
};

void huffman(
    std::vector<WORD> &d_buf, std::vector<BYTE> &l_buf,
    std::vector<WORD> &tree,
    std::vector<LenSizeType> &len_size,
    std::vector<BYTE> &bit_stream)
{
    std::map<int,int> mp;
    for(auto x:d_buf)mp[x]++;
    for(auto x:l_buf)mp[x]++;

    std::priority_queue<Node*,std::vector<Node*>,Node_CMP> pq;
    for(auto &x:mp) pq.push(new Node(x.first,x.second));
    
    while(pq.size()>1)
    {
        Node *left=pq.top();pq.pop();
        Node *right=pq.top();pq.pop();
        pq.push(new Node(left,right));
    }

    std::map<WORD,std::vector<int>> code_tree;
    Node *huffman=pq.top();
    get_tree(huffman,code_tree,0);
    delete huffman;
    std::map<int,BitCode> bitCode;
    int code=0,last_len=0;
    for(auto &x:code_tree)
    {
        WORD len=x.first;
        auto &elems=x.second;
        len_size.push_back({len,static_cast<WORD>(elems.size())});
        code<<=(len-last_len);
        last_len=len;
        for(int i=0;i<elems.size();i++)
        {
            bitCode[elems[i]]={len,code++};
            tree.push_back(elems[i]);
        }
    }
    bit_stream.clear();
    BitStream bitStream(bit_stream);
    for(auto x:d_buf)bitStream.put(bitCode[x].code,bitCode[x].len);
    for(auto x:l_buf)bitStream.put(bitCode[x].code,bitCode[x].len);
    bitStream.end();
}
