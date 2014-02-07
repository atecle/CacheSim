//
//  sim.c
//
//
//  Created by Adam on 8/3/13.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "sim_func.h"


int main (int argc, char **argv)
{
    
    checkInput(argc, argv);
    
    int cache_size = atoi(argv[1]);
    int block_size = atoi(argv[3]);
    int num_lines;
    int num_sets;
    //char *r_alg = argv[4];
    char *w_pol = argv[5];
    
    if (strcmp(argv[2], "direct")) {
        num_lines = 1;
        num_sets = cache_size/(block_size);
        
    }
    
    if (strcmp(argv[2], "assoc")) {
        num_sets = 1;
        num_lines = cache_size/block_size;
        
    }
    
    if (argv[2][5] == ':') {
        
        char *input = argv[2];
        int len = strlen(input);
        char n_way[len - 6];
        int i;
        int j;
        
        
        for (i = 6, j = 0; i < len && j < (len - 6); i++, j++) //getting n from assoc:n
        {
            n_way[j] = argv[2][i];
        }
        num_lines = atoi(n_way);
        
    }
    
    direct(argv[6], cache_size, block_size, w_pol);
    
    
    
    
    return 0;
    
}


void help()  {//prints help message
    
    fprintf(stderr, "<USAGE>: ");
    
    fprintf(stderr,"sim [-h] <cache size> <associativity> <block size> <replace alg> <write policy> <trace file>\n");
    fprintf(stderr,"\n");
    
    fprintf(stderr,"[-h]: Display usage information \n");
    fprintf(stderr,"\n");
    
    fprintf(stderr,  "<cache size>: Total size of cache. Must be power of two and must equal to (number of sets x <set size> x <block size>) \n");
    fprintf(stderr,  "\n");
    
    fprintf(stderr,  "<associativity>: 'direct', 'assoc', or 'assoc:n' \n");
    fprintf(stderr,  "\n");
    
    fprintf(stderr,  "\t'direct' simulates direct mapped cache.\n");
    fprintf(stderr,  "\t'assoc' simulates a fully associative cache'. \n");
    fprintf(stderr,  "\t'assoc:n' simulates an n-way associative cache. n must be a power of two.\n");
    fprintf(stderr,  "\n");
    
    fprintf(stderr,  "<block size>: Must be power of 2, specifies size of cache block.\n");
    fprintf(stderr,  "\n");
    
    fprintf(stderr,  "<replace alg> : 'FIFO', 'LRU', or 'Random' \n");
    fprintf(stderr,  "\n");
    
    fprintf(stderr,  "\t'FIFO' simulates first in first out replacement algorithm.\n");
    fprintf(stderr,  "\t 'LRU' simulates least recently used replacement algorithm.\n");
    fprintf(stderr,  "\t 'Random' simulates random replacement algorithm.\n");
    fprintf(stderr,  "\n");
    
    fprintf(stderr,  "<write policy>: 'wt' simulates write through cache. 'wb' simulates write back cache\n");
    fprintf(stderr,  "\n");
    
    fprintf(stderr,  "<trace file>: name of the file that contains memory access traces generated using Pin.\n");
    
    exit(0);
}




void checkInput(int argc, char **argv) {    //Checks validity of user input
    
    
    int num_lines;
    int block_size;
    int cache_size;
    int sets;
    int n; // for assoc:n
    
    int direct = 0; //Used as booleans
    int full_assoc = 0;
    int assoc = 0;
    
    if (argc != 8 && argc != 7)
    {
        help();
        exit(1);
    }
    
    char *input = argv[1];
    
    if (!strcmp(input, "-h"))
    {
        help();
    }
    
    cache_size = atoi(argv[1]);
    if (!isPower2(cache_size))
    {
        fprintf(stderr,  "<ERROR>: Cache size must be a power of 2.\n");
        exit(1);
    }
    
    
    input = argv[2]; //associativity
    
    
    if (strcmp(input, "direct") && strcmp(input, "assoc") && input[5] != ':')
    {
        fprintf(stderr,  "<ERROR>: Invalid input for associativity. Enter -h for help.\n");
        exit(1);
    }
    
    
    
    
    
    if (input[5] == ':')
    {
        
        int len = strlen(input);
        char input_string[len - 6]; // n
        int i;
        int j;
        
        for (i = 6, j = 0; i < len && j < (len - 6); i++, j++) //gets n from assoc:n
        {
            input_string[j] = argv[2][i];
        }
        
        n = atoi(input_string);
        assoc = 1;
        
        if (!isPower2(n))
        {
            
            fprintf(stderr,  "<ERROR>: Invalid input for 'assoc:n'. n must be a power of 2.\n");
            exit(1);
        }
        
        if (n == 1) { }
        else {
            fprintf(stderr, "<ERROR>: n-way associative cache not implemented.\n");
            exit(0);
        }
        
    }
    
    block_size = atoi(argv[3]);
    
    if (!isPower2(block_size))
    {
        fprintf(stderr, "<ERROR>: Block size must be a power of two\n");
        exit(1);
    }
    
    if (strcmp(argv[4], "FIFO") && strcmp(argv[4], "LRU") && strcmp(argv[4], "Random"))
    {
        fprintf(stderr,  "Invalid input for replacement algorithm. Enter -h for help.\n");
        exit(1);
    }
    
    if (!strcmp(argv[4], "LRU") || !strcmp(argv[4], "Random"))
    {
        fprintf(stderr, "<ERROR>: LRU and Random not implemented.\n");
        exit(0);
    }
    
    if (strcmp(argv[5], "wt") && strcmp(argv[5], "wb"))
    {
        fprintf(stderr,  "Invalid input for write policy. Enter -h for help.\n");
        exit(1);
    }
    
    if (!strcmp(argv[5], "wb"))
    {
        fprintf(stderr, "<ERROR>: Write back not implemented. \n");
        exit(0);
    }
    
    
    if (!strcmp(argv[2], "direct"))
    {
        
        direct = 1;
    }
    else if (!strcmp(argv[2], "assoc"))
    {
        
        fprintf(stderr, "<ERROR>: Fully-associative cache not implemented. \n");
        exit(0);
    }
    
    
    
    
    if (direct)
    {
        
        num_lines = 1;
        
        sets = cache_size/(block_size);
        if (cache_size != ((sets) * (num_lines) * (block_size))) {
            fprintf(stderr, "<ERROR>: Cache size must equal  to (number of sets x <set size> x <block size>)\n");
            exit(1);
        }
    }
    
    if (full_assoc)
    {
        sets = 1;
        num_lines = cache_size/(block_size);
        if (cache_size != ((sets) * (num_lines) * (block_size))) {
            fprintf(stderr, "<ERROR>: Cache size must equal  to (number of sets x <set size> x <block size>)\n");
            exit(1);
        }
        
    }
    
    
    if (assoc)
    {
        
        num_lines = n;
        sets = cache_size/(block_size * num_lines);
        if (cache_size != ((sets) * (num_lines) * (block_size))) {
            fprintf(stderr, "<ERROR>:TEST  Cache size must equal to (number of sets x <set size> x <block size>)\n");
            exit(1);
            
        }
        
    }
    
    FILE *fp;
    fp = fopen(argv[6], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "<ERROR>: File not found\n");
        exit(1);
    }
    
    
    
}



int isPower2(int x) {           //returns 1 if x is power of 2
    
    return !(x>>31) & !!x & !(x & (x+(~1+1)));
}


int getBlock(int w, int b) {        //returns right most b bits
    
    int mask = (1 << b) - 1;
    int block = w & mask;
    return block;
}


int getSetIndex(int w, int s) {         //returns right most s bits
    
    int mask = (1 << s) - 1;
    int set_index = w & mask;
    return set_index;
}


int isHit(struct Address *cache, int set_index, int tag) {          //returns 1 if hit, 0 if miss
    
    if (cache[set_index].valid_bit == 0) {
        
        cache[set_index].valid_bit = 1;
        cache[set_index].tag = tag;
        return 0;
    }
    else {
        if (cache[set_index].tag == tag)
        {
            return 1;
        }
        cache[set_index].tag = tag;
        return 0;
    }
}

void direct(char *trace_file, int cache_size, int block_size, char *w_pol) {
    
    FILE *file;
    file = fopen(trace_file, "r");
    
    int reads = 0;
    int writes = 0;
    int hits = 0;
    int misses = 0;
    int tag = 0;

    
    int sets = cache_size/block_size;
    int s = log2(sets);
    int b = log2(block_size);
    
    
    
    struct Address *cache = malloc(sizeof(struct Address)*sets);
    
    int i = 0;
    
    for (i = 0; i < sets; i++) {
        
        cache[i].tag = 0;
        cache[i].valid_bit = 0;
        cache[i].set_index = 0;
        cache[i].dirty_bit = 0;
    }
    
    
    char line[100];
    
    
    
    
    while (fgets(line, sizeof(line), file)) {  //Parses each line of trace file for W|R and the memory address, which are the second and third string respectively.
        
        char *word = strtok(line, " ");
        int str_num = 1;
        
        while (word != NULL) {
            
            if (str_num == 2) {
                
                if (!strcmp(word, "W")) {
                    writes++;
                }
               
            }
            
            
            
            if (str_num == 3) {
                
                int mem_add = (int)strtol(word, NULL, 0); // converts hex memory address to integer
                int block = getBlock(mem_add, b);
                mem_add = mem_add >> b;
                int set_index = getSetIndex(mem_add, s);
                tag = mem_add >> s;
                
                if (isHit(cache, set_index, tag)) {
                    hits++;
                }
                else {
                    misses++;
                    reads++;
                }
                
            }
            
            
            word = strtok(NULL, " ");
            str_num++;
            
        }
    }
    
    printf("Memory Reads: %d\n", reads);
    printf("Memory Writes: %d\n", writes);
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    
    
}