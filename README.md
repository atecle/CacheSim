CS 344: Computer Architecture
========

*Simulation of direct mapped cache with FIFO replacement*

This was a learning exersise for my comp arch class to get a handle on how caches work. Despite what the usage says, I only a direct mapped, FIFO, write through cache is supported.

I used [pin](http://software.intel.com/sites/landingpage/pintool/docs/58423/Pin/html/) to generate memory access traces. The typical trace file looks something like this...

0x804ae1c: W 0x9cb2874  
0x804ae10: R 0xbf8ef498  
0x804ae16: R 0xbf8ef49c  
0x804ae19: R 0x9cb2880  
0x804ae19: W 0x9cb2880  
0x804ae1c: R 0x9cb2884  
0x804ae1c: W 0x9cb2884  
0x804ae10: R 0xbf8ef498  

It's important that the traces be generated on a 32-bit machine because of how I extract the tag, block offset, and set index from the address.

To implement the cache I created an array of structs, each struct holding the tag, valid bit, and set index, all initially set to zero. As I read through the trace file, I extracted the relevant memory addresses, computed its tag, set bits, and block offset according to the user parameters, and accessed the cache array to determine a hit or a miss. Because it is direct-mapped, the FIFO replacement policy, did not require me to keep track of which line in the set was put in place first, given that there is only one line. As for the write through policy, I simply incremented a counter each time I replaced any data.
