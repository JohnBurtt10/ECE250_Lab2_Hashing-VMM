#include "Process.hpp"
// Constructor 
    Process::Process(unsigned int PID, unsigned int physicalADDR, bool deleted) {
        this->PID = PID;
        this->physicalADDR = physicalADDR; 
        this->deleted = deleted;
    }