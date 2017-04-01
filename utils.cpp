#include <cstdlib>
#include <cstring>
#include "utils.h"

int get_options(int argc,char **argv,const char *option)
{
    for(int i=1;i<argc;i++)if(argv[i][0]=='-'&&!strcmp(argv[i]+1,option))return i;
    return 0;
}
Config get_config(int argc,char **argv)
{
    int r;
    if((r=get_options(argc,argv,"level")))
    {
        int level=atoi(argv[r+1]);
        if(level<0)level=0;
        if(level>=config_count)level=config_count-1;
        return config[level];
    }
    Config c=config[DEFAULT_LEVEL];
    if((r=get_options(argc,argv,"lazy")))c.lazy_match=atoi(argv[r+1]);
    if((r=get_options(argc,argv,"chain")))c.max_chain=atoi(argv[r+1]);
    return c;
}
