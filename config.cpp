#include "utils.h"
#include "compressor.h"

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
size_t config_count=SIZEOF(config);