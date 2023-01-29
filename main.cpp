#include "Table.hpp"
#include "Open.hpp"
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
    Open *open; 
    bool flag; 
    while (cin >> cmd) {
        if (cmd == "OPEN") { 
            flag = true; 
        }
        else if (cmd == "ORDERED") { 
            flag = false;
        }
        else if (cmd == "M") {
            cin >> N; 
            cin >> P; 
            if (flag) { 
                open = new Open(N, P); 
            }
            else { 
                table = new Table(N, P);
            }
        std::cout << "success" << std::endl; 
        } else if (cmd == "INSERT") { 
            cin >> PID; 
            if (flag) { 
                open->Insert(PID);
            } 
            else { 
                table->Insert(PID);
            }
        } else if (cmd == "SEARCH") {
            cin >> PID;
            if (flag) { 
                open->Search(PID);
            }
            else { 
                table->Search(PID); 
            }
        } else if (cmd == "WRITE") { 
            cin >> PID; 
            cin >> ADDR; 
            cin >> x;
            if (flag) { 
                open->Write(PID, ADDR, x);
            }
            else { 
                table->Write(PID, ADDR, x);
            }
        } else if (cmd == "READ") {
            cin >> PID; 
            cin >> ADDR; 
            if (flag) { 
                open->Read(PID, ADDR); 
                }
            else { 
                table->Read(PID, ADDR);
            }
            } 
            else if (cmd == "DELETE") { 
            cin >> PID; 
            if (flag) { 
                open->Delete(PID);
            }
            else { 
                table->Delete(PID);
            }
        } 
        else if (cmd == "PRINT") {
            cin >> m;
            if (!flag) { 
                table->Print(m);
            }
        }
        else if (cmd == "END") { 
            break;
        }
    }
    if (flag) { 
        delete open;
    }
    else { 
        delete table;
    }
    return 0;

}