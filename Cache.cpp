#include <iostream>
#include "Cache.hpp"

using namespace std;




   

        Cache::Cache(int cache_Size, int associativity, int block_Size, string write_policy, string write_allocate){

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

       Cache::~Cache(){
            delete[] cache_array;  //free allocated space
            cache_array = NULL;

            delete[] lru_count;
            lru_count = NULL;

            delete[] dityBit_array;
            dityBit_array = NULL;
        }


        void Cache::calc_index_of_set_and_tag_value(int address, int* indexOfSets, int* tagValue){

            *indexOfSets = address % numberOfSets;

            *tagValue = address/ (blockSize * numberOfSets);
            
        }


        string Cache::checkHit(int array_index, int tag, int* blockIndex, int* hitCounter, int* clockCounter, int* missCounter){

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


        void Cache::replaceBlock(int array_index, int tag, int* blockIndex){
                int max = lru_count[array_index];
                int maxIndex = array_index;

                for(int i = 0; i < associativity; i++){

                    if(max < lru_count[array_index + i] ){
                        max = lru_count[array_index + i];
                        maxIndex = array_index + i;
                    }

                    if(cache_array[array_index + i] == -1){
                        cache_array[array_index + i] = tag;
                        *blockIndex = array_index + i;
                        break;
                    }

                    if(i == (associativity - 1)){
                        cache_array[maxIndex] = tag;
                        *blockIndex = maxIndex;
                    }
                }  

        }


        void Cache::read(int index, int tag, int* blockIndex, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int* readMiss, int* readHit ){

                int array_index = index * associativity;

                string operation = checkHit(array_index, tag, blockIndex, hitCountPtr, clockCounterPtr, missCountPtr);

                    if(operation == "Miss"){
                        replaceBlock(array_index, tag, blockIndex);
                        *readMiss += 1;
                    }
                    else{
                        *readHit += 1;
                    }
            }
            

        void Cache::write(int index, int tag, int* blockIndex, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr,  int* writeMiss, int* writeHit){

                int array_index = index * associativity;

                string operation = checkHit(array_index, tag, blockIndex, hitCountPtr, clockCounterPtr, missCountPtr);


                if(writeAllocate == "yes"){
                    if(operation == "Miss"){
                            replaceBlock(array_index, tag, blockIndex); //for write allocate
                            *writeMiss += 1;
                    }
                    else{
                        *writeHit += 1;
                    }
                    dityBit_array[*blockIndex] = 1;
                }  
                else{
                    if(operation == "Miss"){
                        *writeMiss += 1;
                    }
                    else{
                        *writeHit += 1;
                    }
                }    
            
            }


            void Cache::performance(int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int* writeMiss, int* writeHit, int* readMiss, int* readHit){

                    int totalNumberOfAccess = *hitCountPtr + *missCountPtr;

                    int averageAccessTime = *clockCounterPtr / totalNumberOfAccess;

                    int missRate = (*missCountPtr / totalNumberOfAccess);
                    int hitRate = 1 - missRate;

                    cout<< "Total number of miss: " <<  *missCountPtr <<endl;
                    cout<< "Miss rate: " <<  missRate <<endl;
                    cout<< "Total write miss: " <<  *writeMiss <<endl;
                    cout<< "Total read miss: " <<  *readMiss <<endl;

                    cout<< "Total number of hits: " <<  *hitCountPtr <<endl;
                    cout<< "Hit rate: " << hitRate<< endl;
                    cout<< "Total write hit: " <<  *writeHit <<endl;
                    cout<< "Total read hit: " <<  *readHit <<endl;

                    cout<< "Total number of acesses: " <<  totalNumberOfAccess <<endl;

                    cout<< "Average Access Time: " << averageAccessTime << endl;


            }

       