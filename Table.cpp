#include "Table.hpp"
// Constructor 
Table::Table(int N, int P)
{
    this->memorySize = N; 
    this->pageSize = P;
    array = new std::vector<Process>[N/P]{std::vector<Process>(0,Process(0))}; 
    this->memory = new int[N];
}

// Destructor 
Table::~Table() {
    delete []this->memory;
    delete []array; 
}

void Table::Insert(unsigned int PID) {

    if (this->randomCounter == (this->memorySize/this->pageSize)) {
        std::cout << "failure" << std::endl;
        return;

    }
    if (this->array[PID%(this->memorySize/this->pageSize)].empty()) {
        this->array[PID%(this->memorySize/this->pageSize)].push_back(Process(PID, this->randomCounter*this->pageSize));
        this->randomCounter++; 
        std::cout << "success" << std::endl;
        return;
    }    
        // Displaying element at each column,
        // begin() is the starting iterator,
        // end() is the ending iterator
        int i =0; 
        for (auto it = this->array[PID%(this->memorySize/this->pageSize)].begin();
             it != this->array[PID%(this->memorySize/this->pageSize)].end(); it++) {
            if (PID == it->PID) { 
                std::cout << "failure" << std::endl;
                return; 
            }
            else if (PID > it->PID) { 
                this->array[PID%(this->memorySize/this->pageSize)].insert(this->array[PID%(this->memorySize/this->pageSize)].begin()+i, Process(PID));
                this->randomCounter++;
                std::cout << "success" << std::endl;
                return;
            }
            i++; 
        }
    }
        

void Table::Search(unsigned int PID) {
    Process Process = this->Get(PID);
    if (Process.PID == 0) {
        std::cout << "not found" << std::endl;
        return;
    }
    std::cout << "found " << PID << " in " << PID%(this->memorySize/this->pageSize) << std::endl;
    
}

void Table::Write(unsigned int PID, unsigned int ADDR, int x) {
    // Checks if a process with the given PID exists
    Process Process = this->Get(PID);
    if (Process.PID == 0) {
        std::cout << "failure because can't find process" << std::endl;
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

void Table::Read(unsigned int PID, unsigned int ADDR) {
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

void Table::Delete(unsigned int PID) { 
    int i = 0;
    for (auto it = this->array[PID%(this->memorySize/this->pageSize)].begin();
    it != this->array[PID%(this->memorySize/this->pageSize)].end(); it++) {
        if (PID == it->PID) { 
              this->array[PID%this->memorySize/this->pageSize].erase(this->array[PID%this->memorySize/this->pageSize].begin() + i); 
            std::cout << "success" << std::endl;
            return; 
        }
        i++; 
    }
    std::cout << "failure" << std::endl;
    return;

}

void Table::Print(unsigned int m) {
    if (this->array[m].empty()) { 
        std::cout << "chain is empty" << std::endl;
        return;
    }
    for (auto it = this->array[m].begin();
    it != this->array[m].end(); it++) {
        std::cout << it->PID; 
    }
    std::cout << std::endl;
    return; 
}

// helper function
Process Table::Get(unsigned int PID) { 
    for (auto it = this->array[PID%(this->memorySize/this->pageSize)].begin();
        it != this->array[PID%(this->memorySize/this->pageSize)].end(); it++) {
            if (PID == it->PID) { 
                return *it; 
            }
        }
    return Process(0);
}