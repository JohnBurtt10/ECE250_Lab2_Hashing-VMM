#include "OrderedHash.hpp"
#include "OpenHash.hpp"
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
    OrderedHash *orderedHash;
    OpenHash *openHash; 
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
                openHash = new OpenHash(N, P); 
            }
            else { 
                orderedHash = new OrderedHash(N, P);
            }
        std::cout << "success" << std::endl; 
        } else if (cmd == "INSERT") { 
            cin >> PID; 
            if (flag) { 
                openHash->Insert(PID);
            } 
            else { 
                orderedHash->Insert(PID);
            }
        } else if (cmd == "SEARCH") {
            cin >> PID;
            if (flag) { 
                openHash->Search(PID);
            }
            else { 
                orderedHash->Search(PID); 
            }
        } else if (cmd == "WRITE") { 
            cin >> PID; 
            cin >> ADDR; 
            cin >> x;
            if (flag) { 
                openHash->Write(PID, ADDR, x);
            }
            else { 
                orderedHash->Write(PID, ADDR, x);
            }
        } else if (cmd == "READ") {
            cin >> PID; 
            cin >> ADDR; 
            if (flag) { 
                openHash->Read(PID, ADDR); 
                }
            else { 
                orderedHash->Read(PID, ADDR);
            }
            } 
            else if (cmd == "DELETE") { 
            cin >> PID; 
            if (flag) { 
                openHash->Delete(PID);
            }
            else { 
                orderedHash->Delete(PID);
            }
        } 
        else if (cmd == "PRINT") {
            cin >> m;
            if (!flag) { 
                orderedHash->Print(m);
            }
        }
        else if (cmd == "END") { 
            break;
        }
    }
    if (flag) { 
        delete openHash;
    }
    else { 
        delete orderedHash;
    }
    return 0;

}