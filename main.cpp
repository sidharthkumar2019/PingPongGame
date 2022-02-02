#include<iostream>
#include "manager.h"
using namespace std;

int main () {
    
    cout << "Enter the game mode that you want to play [0: v Comp | 1: 1v1 | 2: 2v2]: ";
    int mode;   cin >> mode;

    if ( mode == 1 ) {
        Manager_1Player g;
        g.run();
    }
    else if ( mode == 2 ) {
        Manager_4player g;
        g.run();
    }
    else {
        cout << "\nChoose the difficulty level [0: easy | 1: normal | 2: unbeatable]: ";
        int diff;   cin >> diff;
        Manager_1Player g(diff);
        g.run();
    }
    return 0;
}