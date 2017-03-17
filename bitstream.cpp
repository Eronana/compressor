#include "compressor.h"
#include "bitstream.h"

BitStream::BitStream(std::vector<BYTE> &buffer):buffer(buffer),temp(0),count(0){}
void BitStream::put(int code,int len)
{
    if(count+len>=8)
    {
        int x=8-count;
        temp<<=x;
        count=len-x;
        temp|=code>>count;
        buffer.push_back(temp);
        code&=((1<<count)-1);
        while(count>=8)
        {
            buffer.push_back(code>>(count-8));
            count-=8;
            code&=((1<<count)-1);
        }
        temp=code;
    }
    else
    {
        count+=len;
        temp<<=len;
        temp|=code;
    }
}
void BitStream::end()
{
    if(count)buffer.push_back(temp<<(8-count));
}

std::vector<BYTE> &BitStream::get_buffer()
{
    return buffer;
}
