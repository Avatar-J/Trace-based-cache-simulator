#include <string>

using namespace std;

class Cache{
    private:
        int cacheSize =0;
        int associativity = 0;
        int blockSize =0;
        //int address = 0;
        int memoryPenalty;
        int cacheAccessTime;
        string writePolicy;
        string writeAllocate;
        int numberOfBlocks;
        int numberOfSets;

        int* cache_array ;
        int* lru_count; 
        int* dityBit_array;

    public:
        Cache(int cache_Size, int associativity, int block_Size, string write_policy, string write_allocate);
        ~Cache();
        void calc_index_of_set_and_tag_value(int address, int* indexOfSets, int* tagValue);
        string checkHit(int array_index, int tag, int* blockIndex, int* hitCounter, int* clockCounter, int* missCounter);
        void replaceBlock(int array_index, int tag, int* blockIndex);
        void read(int index, int tag, int* blockIndex, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int* readMiss, int* readHit );
        void write(int index, int tag, int* blockIndex, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr,  int* writeMiss, int* writeHit);
        void performance(int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int* writeMiss, int* writeHit, int* readMiss, int* readHit);



};