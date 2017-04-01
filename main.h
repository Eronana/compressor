#ifndef _H_MAIN_
#define _H_MAIN_
#include "compressor.h"
#define SIZEOF(a) (sizeof(a)/sizeof(a[0]))
struct Config
{
    int lazy_match;
    int max_chain;
};
Config config[]={
    // lazy_match, max_chain
    {0,0}, // store
    {2,5},
    {4,10},
    {8,32},
    {16,32},
    {16,128},
    {32,256},
    {64,1024},
    {128,4096},
    {MAX_REPEAT_LENGTH,MAX_WINDOW_SIZE}, // highest compression ratio
};
const int DEFAULT_LEVEL=3;
#endif