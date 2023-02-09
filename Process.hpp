#ifndef Process_h
#define Process_h
#include <iostream>
#include <cstdlib>
class Process {
private:
public:
    unsigned int PID;
    unsigned int physicalADDR; 
    bool deleted = false; 


    // Constructor 
    Process(unsigned int PID = 0, unsigned int physicalADDR = 0, bool deleted = false); 

};
#endif