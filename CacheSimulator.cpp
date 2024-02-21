#include <iostream>
#include <string>

using namespace std;

void checkHit(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty ); 
void replaceBlock(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr);
void writeBack(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* dityBit_array, int* hitCountPtr, int* missCountPtr, int memoryPenalty);
void performance(int* hitCountPtr, int* missCountPtr, int* clockCounterPtr);

int main(){

        int cacheSize =0;
        int associativity = 0;
        int blockSize{0};
        int address{0};
        int memoryPenalty;

        int blockIndex;
        int* blockPtr = &blockIndex;

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

        cout << "Memory Penalty: " ;
        cin >> memoryPenalty;


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

void checkHit(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty){

    int array_index = index * associativity;
    string operation = "";
    

    for(int i = 0; i < associativity; i++){

        if( cache_array[array_index + i] == tag){
            operation = "Hit";
            lru_count[array_index + i] = 0;
            *blockPtr = array_index + i;
            *hitCountPtr += 1;
            *clockCounterPtr += 1;
            break;              
        }

        lru_count[array_index + i] = lru_count[array_index + i] + 1;
        operation = "Miss";
        *missCountPtr += 1;
        *clockCounterPtr += memoryPenalty;

    }

      cout << operation << endl;

     if(operation == "Miss"){
        replaceBlock(array_index, associativity, tag, cache_array, lru_count, blockPtr);

     }

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
            cache_array[maxIndex] == tag;
            *blockPtr = maxIndex;
        }
    }  

}

void writeBack(int index, int associativity, int tag, int* cache_array, int* lru_count, int* blockPtr, int* dityBit_array, int* hitCountPtr, int* missCountPtr, int* clockCounterPtr, int memoryPenalty){

    checkHit(index, associativity, tag, cache_array, lru_count, blockPtr, hitCountPtr, missCountPtr, clockCounterPtr, memoryPenalty); //for write allocate

    dityBit_array[*blockPtr] = 1;

    
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

