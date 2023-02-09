#include "OrderedHash.hpp"
// Constructor 
OrderedHash::OrderedHash(int N, int P)
{
    this->memorySize = N; 
    this->pageSize = P;
    array = new std::vector<Process>[N/P]{std::vector<Process>(0,Process(0))}; 
    this->memory = new int[N];
    this->availability = new bool[N/P]{}; 
}

// Destructor 
OrderedHash::~OrderedHash() {
    delete []this->memory;
    delete []this->availability;
    delete []array; 
}

void OrderedHash::Insert(unsigned int PID) {
    unsigned int m = this->memorySize/this->pageSize; 
    unsigned int hash = PID%m; 

    int x =0; 
    for (auto it = this->array[hash].begin();
            it != this->array[hash].end(); it++) {
    if (PID == it->PID) { 
        std::cout << "failure" << std::endl;
        return; 
    }
    else if (PID > it->PID) { 
            for (int i =0; i < m; i++) { 
            if (this->availability[i] == false) { 
                    this->array[hash].insert(this->array[hash].begin()+x, Process(PID, i*this->pageSize));
                this->availability[i] = true; 
                std::cout << "success" << std::endl;
                return;
            }
        }
        std::cout << "failure" << std::endl;
        return; 
    }
    x++; 
    }
    // If a process has not already been inserted, meaning it's either the first process to be inserted into the vector, 
    // or the it is to be the process with the smallest PID value and so it is pushed to the back of the vector
    for (int i =0; i < m; i++) { 
        if (this->availability[i] == false) { 
            this->array[hash].push_back(Process(PID, i*this->pageSize));
            this->availability[i] = true; 
            std::cout << "success" << std::endl;
            return;
        }
    }
    std::cout << "failure" << std::endl; 
    return;
    }
        
void OrderedHash::Search(unsigned int PID) {
    Process Process = this->Get(PID);
    if (Process.PID == 0) {
        std::cout << "not found" << std::endl;
        return;
    }
    std::cout << "found " << PID << " in " << PID%(this->memorySize/this->pageSize) << std::endl;
    
}

void OrderedHash::Write(unsigned int PID, unsigned int ADDR, int x) {
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

void OrderedHash::Read(unsigned int PID, unsigned int ADDR) {
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

void OrderedHash::Delete(unsigned int PID) { 
    int i = 0;
    unsigned int hash = PID%(this->memorySize/this->pageSize); 
    for (auto it = this->array[hash].begin();
    it != this->array[hash].end(); it++) {
        if (PID == it->PID) {
            this->availability[it->physicalADDR/this->pageSize] = false;  
            this->array[hash].erase(this->array[hash].begin()+i);
            std::cout << "success" << std::endl;
            return; 
        }
        i++; 
    }
    std::cout << "failure" << std::endl;
    return;

}

void OrderedHash::Print(unsigned int m) {
    if (this->array[m].empty()) { 
        std::cout << "chain is empty" << std::endl;
        return;
    }
    for (auto it = this->array[m].begin();
    it != this->array[m].end(); it++) {
        std::cout << it->PID << " "; 
    }
    std::cout << std::endl;
    return; 
}

// helper function
Process OrderedHash::Get(unsigned int PID) { 
    unsigned int hash = PID%(this->memorySize/this->pageSize); 
    for (auto it = this->array[hash].begin();
        it != this->array[hash].end(); it++) {
            if (PID == it->PID) { 
                return *it; 
            }
        }
    return Process(0);
}