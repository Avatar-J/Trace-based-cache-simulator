#include <iostream>
#include <string>

using namespace std;

string checkHit(int index, int associativity, int tag, int array_index, int* cache_array, int* lru_count, int* blockPtr, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty, int cacheAccessTime ); 
void replaceBlock(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr);
void write(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* dityBit_array, int* hitCountPtr, int* missCountPtr, int memoryPenalty, int cacheAccessTime, string writeback, int* writeMiss, int* writeHit);
void read(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty, int cacheAccessTime, int* readMiss, int* readHit );
void performance(int* hitCountPtr, int* missCountPtr, int* clockCounterPtr);

int main(){

        int cacheSize =0;
        int associativity = 0;
        int blockSize{0};
        int address{0};
        int memoryPenalty;
        int cacheAccessTime;
        string writeback;

        int blockIndex;
        int* blockPtr = &blockIndex;

        int readMiss = 0, readHit=0, writeMiss=0, writeHit=0;
       
        int miss_count =0, hit_count=0;
        int* missCountPtr = &miss_count;
        int* hitCountPtr = &hit_count;

        int clockCounter =0;
        int* clockCounterPtr = &clockCounter;

        cout << "Set Configurations" << endl;
        cout << "Cache Size in kiB: ";
        cin >> cacheSize;

        cout << "Associativity: " ;
        cin >> associativity;

        cout << "Block size in bytes: " ;
        cin >> blockSize;

        cout << "Address: " ;
        cin >> address;

        cout << "Memory Penalty in clocks: " ;
        cin >> memoryPenalty;

        cout << "Cache Acess Time in clocks: " ;
        cin >> cacheAccessTime;

        cout << "Write back [yes/no]: " ;
        cin >> writeback;

        


        int numberOfBlocks = (cacheSize*1024)/blockSize;

        int numberOfSets = numberOfBlocks/associativity;

        int IndexOfSets = address % numberOfSets;

        int* cache_array = new int[numberOfBlocks]; //dynamic memory allocation
        int* lru_count  = new int[numberOfBlocks];
        int* dityBit_array = new int[numberOfBlocks];


         //int IndexOfSets = (address/blockSize) % numberOfBlocks;

        int tagValue = address/ (blockSize * numberOfSets);



        for(int i =0; i < numberOfBlocks; i++){ //initializes arrays 
            cache_array[i]=-1;
            lru_count[i] = 0;
            dityBit_array = 0;
        } 

        

       delete[] cache_array;  //free allocated space
       cache_array = NULL;

       delete[] lru_count;
       lru_count = NULL;

       delete[] dityBit_array;
       dityBit_array = NULL;
    return 0;
}

string checkHit(int index, int associativity, int tag, int array_index, int* cache_array, int* lru_count, int* blockPtr, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty, int cacheAccessTime){

    
    string operation = "";
    

    for(int i = 0; i < associativity; i++){

        if( cache_array[array_index + i] == tag){
            operation = "Hit";
            lru_count[array_index + i] = 0;
            *blockPtr = array_index + i;
            *hitCountPtr += 1;
            *clockCounterPtr += cacheAccessTime;
            break;              
        }

        lru_count[array_index + i] = lru_count[array_index + i] + 1;
        operation = "Miss";
        *missCountPtr += 1;
        *clockCounterPtr += memoryPenalty;

    }

      cout << operation << endl;

      return operation;

    

}

void replaceBlock(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr){
    int max = lru_count[index];
    int maxIndex = index;

    for(int i = 0; i < associativity; i++){

        if(max < lru_count[index + i] ){
            max = lru_count[index + i];
            maxIndex = index + i;
        }

        if(cache_array[index + i] == -1){
            cache_array[index + i] = tag;
            *blockPtr = index + i;
            break;
        }

        if(i == (associativity - 1)){
            cache_array[maxIndex] = tag;
            *blockPtr = maxIndex;
        }
    }  

}

void read(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty, int cacheAccessTime, int* readMiss, int* readHit ){

   int array_index = index * associativity;

   string operation = checkHit(index, associativity, tag, array_index, cache_array, lru_count, blockPtr, hitCountPtr, missCountPtr, clockCounterPtr, memoryPenalty, cacheAccessTime);

     if(operation == "Miss"){
        replaceBlock(array_index, associativity, tag, cache_array, lru_count, blockPtr);
        *readMiss += 1;
     }
     else{
        *readHit += 1;
     }
}


void write(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* dityBit_array, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty, int cacheAccessTime, string writeback, int* writeMiss, int* writeHit){

    int array_index = index * associativity;

    string operation = checkHit(index, associativity, tag, array_index, cache_array, lru_count, blockPtr, hitCountPtr, missCountPtr, clockCounterPtr, memoryPenalty, cacheAccessTime); 


    if(writeback == "yes"){
        if(operation == "Miss"){
        replaceBlock(array_index, associativity, tag, cache_array, lru_count, blockPtr); //for write allocate
            *writeMiss += 1;
        }
        else{
            *writeHit += 1;
        }
       dityBit_array[*blockPtr] = 1;
    }

   
 
}


void performance(int* hitCountPtr, int* missCountPtr, int* clockCounterPtr){

    int totalNumberOfAccess = *hitCountPtr + *missCountPtr;

    int averageAccessTime = *clockCounterPtr / totalNumberOfAccess;

    int missRate = (*missCountPtr / totalNumberOfAccess);
    int hitRate = 1 - missRate;

    cout<< "Total number of miss: " <<  *missCountPtr <<endl;
    cout<< "Miss rate: " <<  missRate <<endl;

    cout<< "Total number of hits: " <<  *hitCountPtr <<endl;
    cout<< "Hit rate: " << hitRate<< endl;

    cout<< "Total number of acesses: " <<  totalNumberOfAccess <<endl;

    cout<< "Average Access Time: " << averageAccessTime << endl;


}

