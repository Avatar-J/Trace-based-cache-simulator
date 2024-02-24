#include <iostream>


using namespace std;



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


    

         //int IndexOfSets = (address/blockSize) % numberOfBlocks;


        
    return 0;
}








