#ifndef _H_BITSTREAM_
#define _H_BITSTREAM_

#include <vector>
class BitStream
{
private:
    std::vector<BYTE> &buffer;
    BYTE temp;
    int count;
public:
    BitStream(std::vector<BYTE> &buffer);
    void put(int code,int len);
    void end();

    std::vector<BYTE> &get_buffer();
};

#endif
