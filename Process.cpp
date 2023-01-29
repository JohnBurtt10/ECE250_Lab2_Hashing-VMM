#include "Process.hpp"
// Constructor 
    Process::Process(unsigned int PID, unsigned int physicalADDR) {
        this->PID = PID;
        this->physicalADDR = physicalADDR; 
    }