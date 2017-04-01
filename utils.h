#ifndef _H_UTILS_
#define _H_UTILS_
#include <cstdlib>

#define SIZEOF(a) (sizeof(a)/sizeof(a[0]))

struct Config
{
    int lazy_match;
    int max_chain;
};
extern size_t config_count;
extern Config config[];
const int DEFAULT_LEVEL=3;
int get_options(int argc,char **argv,const char *option);
Config get_config(int argc,char **argv);
#endif
