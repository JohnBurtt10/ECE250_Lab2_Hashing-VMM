#include "OpenHash.hpp"
// Constructor 
OpenHash::OpenHash(int N, int P)
{
    this->memorySize = N; 
    this->pageSize = P;
    this->array = new Process[N/P]; 
    this->memory = new int[N];
}

// Destructor 
OpenHash::~OpenHash() {
    delete []this->memory;
    delete []array; 
}

void OpenHash::Insert(unsigned int PID) {
    // Checks if a process with the given PID exists
    Process getProcess = this->Get(PID);
    if (getProcess.PID != 0) {
        std::cout << "failure" << std::endl;
        return;
    }

    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
    unsigned int hash;
    if (secondaryHashFunction % 2 == 0) {secondaryHashFunction++;}
    int i = 0; 
    while (i < m) { 
        hash = (primaryHashFunction + i * secondaryHashFunction) % m; 
        if (this->array[hash].PID == 0) {
            this->array[hash] = Process(PID, hash * pageSize);
            std::cout << "success" << std::endl;
            return;
        }
        i++;
    }
    std::cout << "failure" << std::endl;
}
        
void OpenHash::Search(unsigned int PID) {
    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
    if (secondaryHashFunction % 2 == 0) {secondaryHashFunction++;}
    unsigned int hash; 
    int i = 0; 
    while (i < m) {
        hash = (primaryHashFunction + i * secondaryHashFunction) % m; 
        if (this->array[hash].PID == 0 && this->array[hash].deleted == false) {
            std::cout << "not found" << std::endl;
            return;
        }
        if (this->array[hash].PID == PID) { 
                std::cout << "found " << PID << " in " << hash << std::endl;
                return;
        }
        i++;
    } 
    std::cout << "not found" << std::endl;
}

void OpenHash::Write(unsigned int PID, unsigned int ADDR, int x) {
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

void OpenHash::Read(unsigned int PID, unsigned int ADDR) {
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

void OpenHash::Delete(unsigned int PID) { 
    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
    if (secondaryHashFunction % 2 == 0) {secondaryHashFunction++;}
    unsigned int hash; 
    int i = 0; 
    while (i < m) {
        hash = (primaryHashFunction + i * secondaryHashFunction) % m; 
        if (this->array[hash].PID == PID) { 
            this->array[hash] = Process(0, 0, true); 
            std::cout << "success" << std::endl;
            return;
        }
    i++;
    }
    std::cout << "failure" << std::endl;
    return;

}

// helper function
Process OpenHash::Get(unsigned int PID) { 
    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int primaryHashFunction = PID % m;
    unsigned int secondaryHashFunction = (PID/m) % m; 
    if (secondaryHashFunction % 2 == 0) {secondaryHashFunction++;}
    unsigned int hash; 
    int i = 0; 
    while (i < m) {
        hash = (primaryHashFunction + i * secondaryHashFunction) % m;
        // Check if the process is not yet initialized in which case we can immediately determine that 
        // the process with PID of parameter PID does not exist
        if (this->array[hash].PID == 0 && this->array[hash].deleted == false) {
            return Process(0);
        }
        if (this->array[hash].PID == PID) { 
            return this->array[hash]; 
        }
        i++;
    }
    return Process(0);
}