#include <vector> 
#include <iostream>
#include <cstdlib>
#include "Process.hpp"
using namespace std;
class Table {
private:
int *memory;
public:
    vector<Process>* array;
    int memorySize; 
    int pageSize;
    int randomCounter = 0;
    // Constructor 
    Table(int N, int P); 
    ~Table();
    void Insert(unsigned int PID = 0); 
    void Search(unsigned int PID); 
    void Write(unsigned int PID, unsigned int ADDR, int x);
    void Read(unsigned int PID, unsigned int ADDR);
    void Delete(unsigned int PID);
    void Print(unsigned int PID); 
    Process Get(unsigned int PID);



};