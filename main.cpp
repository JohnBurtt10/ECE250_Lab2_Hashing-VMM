#include "Table.hpp"
#include <iostream> 
using namespace std; 

int main() {
    string cmd; 
    int N;
    int P;  
    int x;
    unsigned int PID; 
    unsigned int ADDR;
    unsigned int m; 
    Table *table;
    while (cin >> cmd) { 
        if (cmd == "M") {
            cin >> N; 
            cin >> P; 
            table = new Table(N, P); 
            std::cout << "success" << std::endl; 
        } else if (cmd == "INSERT") { 
            // cin >> name; 
            cin >> PID; 
            table->Insert(PID);
        } else if (cmd == "SEARCH") {
            cin >> PID;
            table->Search(PID); 
        } else if (cmd == "WRITE") { 
            cin >> PID; 
            cin >> ADDR; 
            cin >> x;
            table->Write(PID, ADDR, x);
        } else if (cmd == "READ") {
            cin >> PID; 
            cin >> ADDR; 
            table->Read(PID, ADDR);
        } else if (cmd == "DELETE") { 
            table->Delete(PID);
        } else if (cmd == "PRINT") {
            table->Print(m);
        }
        else if (cmd == "END") { 
            break;
        }
    }
    delete table; 
    return 0;

}