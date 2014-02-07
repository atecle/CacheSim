#ifndef _sim_func_h
#define _sim_func_h

void help();
void checkInput(int argc, char **argv);
int isPower2(int n);
int getBlock(int w, int b);
int getSetIndex(int w, int s);
struct Address cache;
int isHit(struct Address *cache, int set_index, int tag);
void direct(char *trace_file, int cache_size, int block_size, char *w_pol);



struct Address {
    
    int valid_bit;
    int tag;
    int set_index;
    int dirty_bit;
    
    
};

#endif
