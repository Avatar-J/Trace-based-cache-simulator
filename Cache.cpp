#include <iostream>

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

        Cache(int cache_Size, int associativity, int block_Size, string write_policy, string write_allocate){

            cacheSize = cache_Size;
            associativity = associativity;
            blockSize = block_Size;
            writePolicy = write_policy;
            writeAllocate = write_allocate;
            numberOfBlocks = (cacheSize*1024)/block_Size;
            numberOfSets = numberOfBlocks/associativity;

            int* cache_array = new int[numberOfBlocks]; //dynamic memory allocation
            int* lru_count  = new int[numberOfBlocks];
            int* dityBit_array = new int[numberOfBlocks];

            for(int i =0; i < numberOfBlocks; i++){ //initializes arrays 
            cache_array[i]=-1;
            lru_count[i] = 0;
            dityBit_array = 0;
            } 

        }

        void calc_index_of_set_and_tag_value(int address, int* indexOfSets, int* tagValue){

            *indexOfSets = address % numberOfSets;

            *tagValue = address/ (blockSize * numberOfSets);
            
        }

        string checkHit(int array_index, int tag, int* blockIndex, int* hitCounter, int* clockCounter, int* missCounter){

            string hit_or_miss;

            for(int i = 0; i < associativity; i++){

                if( cache_array[array_index + i] == tag){
                    hit_or_miss = "Hit";
                    lru_count[array_index + i] = 0; //least recently used 
                    *blockIndex = array_index + i;  // keeps tract of block index  
                    *hitCounter += 1;
                    *clockCounter += cacheAccessTime;
                    break;              
                }

                lru_count[array_index + i] +=  1;
                hit_or_miss = "Miss";
                *missCounter += 1;
                *clockCounter += memoryPenalty;

        }
        return hit_or_miss;

            
        }

       


};