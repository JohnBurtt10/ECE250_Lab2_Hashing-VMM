#include "Table.hpp"
// Constructor 
Table::Table(int N, int P)
{
    this->memorySize = N; 
    this->pageSize = P;
    array = new std::vector<Process>[N/P]{std::vector<Process>(0,Process(0))}; 
    this->memory = new int[N];
    this->availability = new bool[N/P]{}; 
}

// Destructor 
Table::~Table() {
    delete []this->memory;
    delete []this->availability;
    delete []array; 
}

void Table::Insert(unsigned int PID) {

    if (this->array[PID%(this->memorySize/this->pageSize)].empty()) {
        for (int i =0; i < this->memorySize/this->pageSize; i++) { 
            if (this->availability[i] == false) { 
                this->array[PID%(this->memorySize/this->pageSize)].push_back(Process(PID, i*this->pageSize));
                this->availability[i] = true; 
                std::cout << "success" << std::endl;
                return;
            }
        }
        std::cout << "failure" << std::endl;
        return; 
    }    
        // Displaying element at each column,
        // begin() is the starting iterator,
        // end() is the ending iterator
        int x =0; 
        for (auto it = this->array[PID%(this->memorySize/this->pageSize)].begin();
             it != this->array[PID%(this->memorySize/this->pageSize)].end(); it++) {
            if (PID == it->PID) { 
                std::cout << "failure" << std::endl;
                return; 
            }
            else if (PID > it->PID) { 
                for (int i =0; i < this->memorySize/this->pageSize; i++) { 
                    if (this->availability[i] == false) { 
                        this->array[PID%(this->memorySize/this->pageSize)].insert(this->array[PID%(this->memorySize/this->pageSize)].begin()+x, Process(PID, i*this->pageSize));
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
        for (int i =0; i < this->memorySize/this->pageSize; i++) { 
            if (this->availability[i] == false) { 
                this->array[PID%(this->memorySize/this->pageSize)].push_back(Process(PID, i*this->pageSize));
                this->availability[i] = true; 
                std::cout << "success" << std::endl;
                return;
            }
        }
    std::cout << "failure" << std::endl; 
    return;
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
            this->availability[it->physicalADDR/this->pageSize] = false;  
            this->array[PID%(this->memorySize/this->pageSize)].erase(this->array[PID%(this->memorySize/this->pageSize)].begin()+i);
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
        std::cout << it->PID << " "; 
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