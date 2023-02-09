#include <vector> 
#include <iostream>
#include <cstdlib>
#include "Process.hpp"
using namespace std;
class OpenHash {
private:
int *memory;
public:
    Process *array;
    int memorySize; 
    int pageSize;
    // int randomCounter = 0;
    // Constructor 
    OpenHash(int N, int P); 
    ~OpenHash();
    void Insert(unsigned int PID = 0); 
    void Search(unsigned int PID); 
    void Write(unsigned int PID, unsigned int ADDR, int x);
    void Read(unsigned int PID, unsigned int ADDR);
    void Delete(unsigned int PID);
    void Print(unsigned int PID); 
    Process Get(unsigned int PID);


};