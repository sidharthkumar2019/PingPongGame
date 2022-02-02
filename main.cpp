#include<iostream>
#include "manager.h"
using namespace std;

int main () {
    
    cout << "Enter the game mode that you want to play [0: 1v1 | 1: 2v2]: ";
    bool mode;   cin >> mode;

    if ( !mode ) {
        Manager g;
        g.run();
    }
    else {
        Manager_4player g;
        g.run();
    }
    return 0;
}