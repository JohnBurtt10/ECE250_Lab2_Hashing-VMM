#include "Open.hpp"
// Constructor 
Open::Open(int N, int P)
{
    this->memorySize = N; 
    this->pageSize = P;
    this->array = new Process[N/P]; 
    this->memory = new int[N];
}

// Destructor 
Open::~Open() {
    delete []this->memory;
    delete []array; 
}

void Open::Insert(unsigned int PID) {

    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
     if (secondaryHashFunction % 2 == 0) { 
        secondaryHashFunction++;
    }
    int i = 0; 
    while (i < m) { 
        if (this->array[(primaryHashFunction + i * secondaryHashFunction) % m].PID == 0) {
            this->array[(primaryHashFunction + i * secondaryHashFunction) % m] = Process(PID, ((primaryHashFunction + i * secondaryHashFunction) % m) * pageSize);
            std::cout << "success" << std::endl;
            return;
        }
        i++;
    }
    std::cout << "failure" << std::endl;
    return;
}
        
void Open::Search(unsigned int PID) {
    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
    if (secondaryHashFunction % 2 == 0) { 
        secondaryHashFunction++;
    }
    int i = 0; 
    while (i < m) {
        if (this->array[(primaryHashFunction + i * secondaryHashFunction) % m].PID == PID) { 
                std::cout << "found " << PID << " in " << (primaryHashFunction + i * secondaryHashFunction) % m << std::endl;
                return;
        }
        i++;
    } 
    std::cout << "not found" << std::endl;
}

void Open::Write(unsigned int PID, unsigned int ADDR, int x) {
    // Checks if a process with the given PID exists
    Process Process = this->Get(PID);
    if (Process.PID == 0) {
        std::cout << "failure" << std::endl;
        return;
    }
    // Checks if ADDR is within the virtual address space allocated to the process
    if (ADDR < this->pageSize && ADDR >= 0) {
        this->memory[Process.physicalADDR+ADDR] = x;
        std::cout << "success" << std::endl;
        return;
    }
    else { 
        std::cout << "failure" << std::endl;
        return;
    }
}

void Open::Read(unsigned int PID, unsigned int ADDR) {
    Process Process = this->Get(PID);
    if (Process.PID == 0) {
        std::cout << "failure" << std::endl;
        return;
    }
    // Checks if ADDR is within the virtual address space allocated to the process
    if (ADDR < this->pageSize && ADDR >= 0) {
        std::cout << ADDR << " " << this->memory[Process.physicalADDR + ADDR] << std::endl;
        return;
    }
    else { 
        std::cout << "failure" << std::endl;
        return;
    }
}

void Open::Delete(unsigned int PID) { 
    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
     if (secondaryHashFunction % 2 == 0) { 
        secondaryHashFunction++;
    }
    int i = 0; 
    while (i < m) {
        if (this->array[(primaryHashFunction + i * secondaryHashFunction) % m].PID == PID) { 
            this->array[(primaryHashFunction + i * secondaryHashFunction) % m] = Process(0); 
            std::cout << "success" << std::endl;
            return;
        }
    i++;
    }
    std::cout << "failure" << std::endl;
    return;

}

// helper function
Process Open::Get(unsigned int PID) { 
    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
     if (secondaryHashFunction % 2 == 0) { 
        secondaryHashFunction++;
    }
    int i = 0; 
    while (i < m) {
        if (this->array[(primaryHashFunction + i * secondaryHashFunction) % m].PID == PID) { 
            return this->array[(primaryHashFunction + i * secondaryHashFunction) % m]; 
        }
    i++;
    }
    return Process(0);
    }