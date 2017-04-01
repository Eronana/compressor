#include <cstdio>
#include <cstdlib>
#include "utils.h"
#include "compressor.h"

void usage(char *e)
{
    puts("usage:");
    puts("  compression:");
    printf("    %s test.txt.compressed test.txt -c\n",e);
    printf("    %s test.txt.compressed test.txt -c -level 5\n",e);
    printf("    %s test.txt.compressed test.txt -c -lazy 128 -chain 100\n",e);
    puts("  uncompression:");
    printf("    %s test.txt test.txt.compressed -x\n",e);
    puts("  options:");
    puts("    c: compression");
    puts("    x: uncompression");
    printf("    level: compression level. 0 for store, %lu for highest compression ratio. default is %d\n",config_count-1,DEFAULT_LEVEL);
    printf("    lazy : set max lazy match, default is %d\n",config[DEFAULT_LEVEL].lazy_match);
    printf("    chain: set max length of find in hash chain, default is %d\n",config[DEFAULT_LEVEL].max_chain);
    puts("    lazy and chain will be ignored if you setted level");
    exit(1);
}

int main(int argc,char **argv)
{
    if(argc<3||get_options(argc,argv,"h"))usage(argv[0]);
    bool isC=get_options(argc,argv,"c");
    bool isX=get_options(argc,argv,"x");
    if(isC&&isX)
    {
        fprintf(stderr,"-c and -x cannot exist at the same time\n");
        return 1;
    }
    if(!isC&&!isX)
    {
        fprintf(stderr,"please use -c to compression or -x to uncompression\n");
        return 1;
    }
    char *dest_file=argv[1];
    char *src_file=argv[2];
    FILE *src_fp=fopen(src_file,"r");
    if(!src_fp)
    {
        fprintf(stderr,"cannot open src file: %s\n",src_file);
        return 1;
    }
    FILE *dest_fp=fopen(dest_file,"w");
    if(!dest_fp)
    {
        fprintf(stderr,"cannot open dest file: %s\n",dest_file);
        return 1;
    }

    fseek(src_fp,0,SEEK_END);
    DWORD src_size=ftell(src_fp);
    if(src_size==0)
    {
        fprintf(stderr,"cannot compress empty file\n");
        fclose(src_fp);
        return 1;
    }
    BYTE *src=new BYTE[src_size];
    fseek(src_fp,0,SEEK_SET);
    fread(src,src_size,1,src_fp);
    fclose(src_fp);

    
    if(isC)
    {
        Config c=get_config(argc,argv);
        BYTE *buffer=new BYTE[getBufferSize(src_size)];
        puts("compressing...");
        DWORD compressed_size=compress(buffer,src,src_size,c.lazy_match,c.max_chain);
        puts("compression is complete");
        printf("original size: %lu\n",src_size);
        printf("compressed size: %lu\n",compressed_size+4);
        printf("compression ratio: %.2f%%\n",(compressed_size+4)*100.0/src_size);
        fwrite(&src_size,4,1,dest_fp);
        fwrite(buffer,compressed_size,1,dest_fp);
        fclose(dest_fp);
        puts("saved.");
    }
    else
    {
        DWORD original_size=*(DWORD*)src;
        BYTE *buffer=new BYTE[original_size];
        puts("uncompressing...");
        uncompress(buffer,src+4);
        puts("uncompression is complete");
        printf("original size: %lu\n",original_size);
        printf("compressed size: %lu\n",src_size);
        printf("compression ratio: %.2f\n",float(src_size)/original_size);
        fwrite(buffer,original_size,1,dest_fp);
        fclose(dest_fp);
        puts("saved.");
    }
    return 0;
}
