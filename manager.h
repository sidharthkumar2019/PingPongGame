#ifndef MANAGER_H
#define MANAGER_H

#include "object.h"
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>

class Manager {
protected:
    int width, height;
    int score1, score2;
    Object *ball;
    bool quit;

public:
    Manager(int w=60, int h=20) {
        quit = false;
        score1 = score2 = 0;
        width = w, height = h;

        ball = new Ball (w/2, h/2);
    }

    ~Manager() {
        delete ball;
    }
};

class Manager_2player: public Manager {
    char up1, down1, up2, down2;
    Object *p1, *p2;

public: 
    Manager_2player (int w=60, int h=20) {
        Manager(w, h);
        up1 = 'w', down1 = 's';
        up2 = 'i', down2 = 'k';
        
        p1 = new Bat (1, h/2-3);
        p2 = new Bat (w-2, h/2-3);
    }  

    void scoreUp (Object *player) {
        if (player == p1) 
            score1 ++;
        else if (player == p2)
            score2 ++;

        ball->reset();
        p1->reset();
        p2->reset();
    }

    void draw () {
        system("clear");

        if ( score1 >= 10 ) {
            std::cout << "Player 1 won\n";
            return;
        }

        if ( score2 >= 10 ) {
            std::cout << "Player 2 won \n";
            return;
        }

        for (int i=0 ; i<width; i++)
            std::cout << "\u2592";
        std::cout << "\n";

        for (int i=0 ; i<height ; i++) {
            for (int j=0 ; j<width ; j++) {

                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = p1->getX();
                int player1y = p1->getY();
                int player2x = p2->getX();
                int player2y = p2->getY();

                if ( j==0 or j==width-1 )
                    std::cout << "\u2592";
                    
                else if ( ballx == j and bally == i )
                    std::cout << "\u25C9";    // ball
                else if ( player1x == j and player1y == i )
                    std::cout << "\u2589";    // player 1
                else if ( player1x == j and player1y+1 == i )
                    std::cout << "\u2589";    // player 1
                else if ( player1x == j and player1y+2 == i )
                    std::cout << "\u2589";    // player 1
                else if ( player1x == j and player1y+3 == i )
                    std::cout << "\u2589";    // player 1
                    
                else if ( player2x == j and player2y == i ) {
                    std::cout << "\u2589";    // player 2
                }
                else if ( player2x == j and player2y+1 == i ) {
                    std::cout << "\u2589";    // player 2
                }
                else if ( player2x == j and player2y+2 == i ) {
                    std::cout << "\u2589";    // player 2
                }
                else if ( player2x == j and player2y+3 == i ) {
                    std::cout << "\u2589";    // player 2
                }
                else if ( j == width/2 ) {
                    std::cout << "\u2502";
                }
                else 
                    std::cout << " ";
            }
            std::cout << "\n";
        }

        for (int i=0 ; i<width ; i++)
            std::cout << "\u2592";
        std::cout << "\n";

        for (int i=0 ; i<width ; i++)
            if ( i==width/2-2 ) {
                std::cout << score1 << " - " << score2 << "\n";
                break;
            }         
            else std::cout << " ";   
            
        std::cout << "Player 1 controls: 'w' - UP | 's' - DOWN\n";
        std::cout << "Player 2 controls: 'i' - UP | 'k' - DOWN\n";
    }

    void input () {
        ball->move();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = p1->getX();
        int player1y = p1->getY();
        int player2x = p2->getX();
        int player2y = p2->getY();

        if ( kbhit() ) {
            char curr = getch();

            if ( curr == up1 ) 
                if ( player1y > 0 )
                    p1->moveUp();
            
            if ( curr == up2 ) 
                if ( player2y > 0 )
                    p2->moveUp();
            
            if ( curr == down1 ) 
                if ( player1y + 4 < height )
                    p1->moveDown();
            
            if ( curr == down2 ) 
                if ( player2y + 4 < height )
                    p2->moveDown();
            
            if ( ball->getDir() == STOP )
                ball->ranDir();

            if ( curr == 'q' )
                quit = true;
        }   
    }

    void logic () {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = p1->getX();
        int player1y = p1->getY();
        int player2x = p2->getX();
        int player2y = p2->getY();

        // left bat        ball,
        if ( ballx == player1x + 1 ) {
            if (bally == player1y or bally == player1y+3)
                // UPRIGHT, DOWNRIGHT
                ball->changeDir((eDir)(rand() % 2 + 5));
            else if (bally == player1y+1 or bally == player1y+2)
                // RIGHT, UPRIGHT, DOWNRIGHT
                ball->changeDir((eDir)(rand() % 3 + 4));
        }

        // right bat        
        if ( ballx == player2x - 1 ) {
            if (bally == player2y or bally == player2y+3)
                // UPLEFT, DOWNLEFT
                ball->changeDir((eDir)(rand() % 2 + 2));
            else if (bally == player2y+1 or bally == player2y+2)
                // LEFT, UPLEFT, DOWNLEFT
                ball->changeDir((eDir)(rand() % 3 + 1));
        }
            

        // bottom wall
        if ( bally >= height-1 )
            ball->changeDir(ball->getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT );

        // top wall
        if ( bally <= 0 )
            ball->changeDir((ball->getDir() == UPRIGHT) ? DOWNRIGHT : DOWNLEFT );

        // right wall 
        if ( ballx == width-1 ) 
            scoreUp(p1);

        // left wall
        if ( ballx == 0 ) 
            scoreUp(p2);
    }

    void run () {
        while (!quit)
        {
            draw();
            input();
            logic();
            usleep(80000); // similar to sleep() but takes input in micro sec
        }
        
    }

    ~Manager_2player() {
        delete p1, p2;
    }
};
// _________________________________________________________________________________________


class Manager_4player: public Manager {
    char up1a, down1a, up1b, down1b, up2a, down2a, up2b, down2b;
    Object *p1a, *p1b, *p2a, *p2b;

public: 
    Manager_4player (int w=60, int h=20) {
        
        Manager(w, h);
        up1a = 'w', down1a = 's';
        up1b = 'f', down1b = 'v';
        up2a = 'i', down2a = 'k';
        up2b = 'j', down2b = 'n';
        
        p1a = new Bat (1, h/2-3);
        p1b = new Bat (1, h/2-3 + 6);
        p2a = new Bat (w-2, h/2-3);
        p2b = new Bat (w-2, h/2-3 + 6);
    }  

    void scoreUp (Object *player) {
        if (player == p1a or player == p1b) 
            score1 ++;
        else if (player == p2a or player == p2b)
            score2 ++;

        ball->reset();
        p1a->reset();
        p1b->reset();
        p2a->reset();
        p2b->reset();
    }

    void draw () {
        system("clear");

        if ( score1 >= 10 ) {
            std::cout << "Team 1 won\n";
            return;
        }

        if ( score2 >= 10 ) {
            std::cout << "Team 2 won \n";
            return;
        }

        for (int i=0 ; i<width; i++)
            std::cout << "\u2592";
        std::cout << "\n";

        for (int i=0 ; i<height ; i++) {
            for (int j=0 ; j<width ; j++) {

                int ballx = ball->getX();
                int bally = ball->getY();
                int player1ax = p1a->getX();
                int player1ay = p1a->getY();
                int player1bx = p1b->getX();
                int player1by = p1b->getY();                
                int player2ax = p2a->getX();
                int player2ay = p2a->getY();
                int player2bx = p2b->getX();
                int player2by = p2b->getY();

                if ( j==0 or j==width-1 )
                    std::cout << "\u2592";
                    
                else if ( ballx == j and bally == i )
                    std::cout << "\u25C9";    // ball
                else if ( (player1ax == j and player1ay == i) or 
                            (player1bx == j and player1by == i) )
                    std::cout << "\u2589";    // team 1
                else if ( (player1ax == j and player1ay+1 == i) or 
                            (player1bx == j and player1by+1 == i) )
                    std::cout << "\u2589";    // team 1
                else if ( (player1ax == j and player1ay+2 == i) or 
                            (player1bx == j and player1by+2 == i) )
                    std::cout << "\u2589";    // team 1
                else if ( (player1ax == j and player1ay+3 == i) or 
                            (player1bx == j and player1by+3 == i) )
                    std::cout << "\u2589";    // team 1
                    
                else if ( (player2ax == j and player2ay == i) or 
                            (player2bx == j and player2by == i) )
                    std::cout << "\u2589";    // team 2
                else if ( (player2ax == j and player2ay+1 == i) or 
                            (player2bx == j and player2by+1 == i) )
                    std::cout << "\u2589";    // team 2
                else if ( (player2ax == j and player2ay+2 == i) or 
                            (player2bx == j and player2by+2 == i) )
                    std::cout << "\u2589";    // team 2
                else if ( (player2ax == j and player2ay+3 == i) or 
                            (player2bx == j and player2by+3 == i) )
                    std::cout << "\u2589";    // team 2
                
                else if ( j == width/2 ) {
                    std::cout << "\u2502";
                }
                else 
                    std::cout << " ";
            }
            std::cout << "\n";
        }

        for (int i=0 ; i<width ; i++)
            std::cout << "\u2592";
        std::cout << "\n";

        for (int i=0 ; i<width ; i++)
            if ( i==width/2-2 ) {
                std::cout << score1 << " - " << score2 << "\n";
                break;
            }         
            else std::cout << " ";   
            
        std::cout << "Team 1 controls: \n";
        std::cout << "                 Player 1 'w' - UP | 's' - DOWN; Player 2 'f' - UP | 'v' - DOWN\n";
        std::cout << "Team 2 controls: \n";
        std::cout << "                 Player 3 'w' - UP | 's' - DOWN; Player 4 'j' - UP | 'n' - DOWN\n";
    }

    void input () {
        ball->move();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1ax = p1a->getX();
        int player1ay = p1a->getY();
        int player1bx = p1b->getX();
        int player1by = p1b->getY();                
        int player2ax = p2a->getX();
        int player2ay = p2a->getY();
        int player2bx = p2b->getX();
        int player2by = p2b->getY();

        if ( kbhit() ) {
            char curr = getch();

            if ( curr == up1a ) 
                if ( player1ay > 0 )
                    p1a->moveUp();
            if ( curr == up1b ) 
                if ( player1by > 0 )
                    p1b->moveUp();
            
            if ( curr == up2a ) 
                if ( player2ay > 0 )
                    p2a->moveUp();
            if ( curr == up2b ) 
                if ( player2by > 0 )
                    p2b->moveUp();
            
            if ( curr == down1a ) 
                if ( player1ay + 4 < height )
                    p1a->moveDown();
            if ( curr == down1b ) 
                if ( player1by + 4 < height )
                    p1b->moveDown();
            
            if ( curr == down2a ) 
                if ( player2ay + 4 < height )
                    p2a->moveDown();
            if ( curr == down2b ) 
                if ( player2by + 4 < height )
                    p2b->moveDown();
            
            if ( ball->getDir() == STOP )
                ball->ranDir();

            if ( curr == 'q' )
                quit = true;
        }   
    }

    void logic () {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1ax = p1a->getX();
        int player1ay = p1a->getY();
        int player1bx = p1b->getX();
        int player1by = p1b->getY();                
        int player2ax = p2a->getX();
        int player2ay = p2a->getY();
        int player2bx = p2b->getX();
        int player2by = p2b->getY();

        // left bats
        if ( (ballx == player1ax + 1) or (ballx == player1bx + 1) )  {
            if ((bally == player1ay) or (bally == player1ay+3) or
                (bally == player1by) or (bally == player1by+3))
                // UPRIGHT, DOWNRIGHT
                ball->changeDir((eDir)(rand() % 2 + 5));
            else if ((bally == player1ay + 1) or (bally == player1ay + 2)
                    or (bally == player1by + 1) or (bally == player1by + 2))
                // UPRIGHT, DOWNRIGHT, RIGHT
                ball->changeDir((eDir)(rand() % 3 + 4));
        }
            
        // right bats
        if ( (ballx == player2ax - 1) or (ballx == player2bx - 1) ) {
            if ((bally == player2ay) or (bally == player2ay + 3)
                or (bally == player2by) or (bally == player2by + 3))
                ball->changeDir((eDir)(rand() % 2 + 2));
            else if ((bally == player2ay + 1) or (bally == player2ay + 2)
                    or (bally == player2by + 1) or (bally == player2by + 2))
                ball->changeDir((eDir)(rand() % 3 + 1));
        }
            
        
        // bottom wall
        if ( bally >= height-1 )
            ball->changeDir(ball->getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT );

        // top wall
        if ( bally <= 0 )
            ball->changeDir((ball->getDir() == UPRIGHT) ? DOWNRIGHT : DOWNLEFT );

        // right wall 
        if ( ballx == width-1 ) 
            scoreUp(p1a);

        // left wall
        if ( ballx == 0 ) 
            scoreUp(p2a);
    }

    void run () {
        while (!quit)
        {
            draw();
            input();
            logic();
            usleep(80000);
        }
        
    }
    
    ~Manager_4player() {
        delete p1a, p1b, p2a, p2b;
    }
};

//____________________________________________________________________________________________

class Manager_1Player: public Manager {
    int difficulty;
    char up1, down1;
    Object *p1, *p2;

public: 
    Manager_1Player ( int diff = 1, int w=60, int h=20 ) {
        
        Manager(w,h);
        up1 = 'w', down1 = 's';
        difficulty = diff;

        p1 = new Bat (1, h/2-3);
        p2 = new Bat (w-2, h/2-3);
    }  

    void scoreUp (Object *player) {
        if (player == p1) 
            score1 ++;
        else if (player == p2)
            score2 ++;

        ball->reset();
        p1->reset();
        p2->reset();
    }

    void draw () {
        system("clear");

        if ( score1 >= 10 ) {
            std::cout << "You won\n";
            return;
        }

        if ( score2 >= 10 ) {
            std::cout << "Computer won \n";
            return;
        }

        for (int i=0 ; i<width; i++)
            std::cout << "\u2592";
        std::cout << "\n";

        for (int i=0 ; i<height ; i++) {
            for (int j=0 ; j<width ; j++) {

                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = p1->getX();
                int player1y = p1->getY();
                int player2x = p2->getX();
                int player2y = p2->getY();

                if ( j==0 or j==width-1 )
                    std::cout << "\u2592";
                    
                else if ( ballx == j and bally == i )
                    std::cout << "\u25C9";    // ball
                else if ( player1x == j and player1y == i )
                    std::cout << "\u2589";    // you
                else if ( player1x == j and player1y+1 == i )
                    std::cout << "\u2589";    // you
                else if ( player1x == j and player1y+2 == i )
                    std::cout << "\u2589";    // you
                else if ( player1x == j and player1y+3 == i )
                    std::cout << "\u2589";    // you
                    
                else if ( player2x == j and player2y == i ) {
                    std::cout << "\u2589";    // computer
                }
                else if ( player2x == j and player2y+1 == i ) {
                    std::cout << "\u2589";    // computer
                }
                else if ( player2x == j and player2y+2 == i ) {
                    std::cout << "\u2589";    // computer
                }
                else if ( player2x == j and player2y+3 == i ) {
                    std::cout << "\u2589";    // computer
                }
                else if ( j == width/2 ) {
                    std::cout << "\u2502";
                }
                else 
                    std::cout << " ";
            }
            std::cout << "\n";
        }

        for (int i=0 ; i<width ; i++)
            std::cout << "\u2592";
        std::cout << "\n";

        for (int i=0 ; i<width ; i++)
            if ( i==width/2-2 ) {
                std::cout << score1 << " - " << score2 << "\n";
                break;
            }         
            else std::cout << " ";   
            
        std::cout << "Controls: 'w' - UP | 's' - DOWN\n";
    }

    void input () {
        ball->move();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = p1->getX();
        int player1y = p1->getY();
        int player2x = p2->getX();
        int player2y = p2->getY();

        if ( kbhit() ) {
            char curr = getch();

            if ( curr == up1 ) 
                if ( player1y > 0 )
                    p1->moveUp();
            
            if ( curr == down1 ) 
                if ( player1y + 4 < height )
                    p1->moveDown();
            
            if ( ball->getDir() == STOP )
                ball->ranDir();

            if ( curr == 'q' )
                quit = true;
        }

        // move the 2nd bat
        if ( difficulty == 2 ) {
            if ( ball->getDir() == RIGHT) {
                int diff = bally - player2y;
                // if ( 0 <= diff and diff <= 3 );
                if ( 3 < diff and (player2y+4 < height)) 
                    p2->moveDown();
                else if ( diff < 0 and player2y > 0 )
                    p2->moveUp();
            }
            else {
                if ( bally < player2y and player2y > 0 )
                    p2->moveUp();
                else if ( bally > player2y and player2y+4 < height )
                    p2->moveDown();
            }
        }
        else if ( difficulty == 1 ) {
            if ( ball->getDir() == RIGHT) {
                int diff = bally - player2y;
                // if ( 0 <= diff and diff <= 3 );
                if ( 3 < diff and (player2y+4 < height)) 
                    p2->moveDown();
                else if ( diff < 0 and player2y > 0 )
                    p2->moveUp();
            }
            else {
                if ( bally < player2y+2 and player2y > 0 )
                    p2->moveUp();
                else if ( bally > player2y+4 and player2y+4 < height )
                    p2->moveDown();
            }
        }
        else {
            if ( ball->getDir() == RIGHT) {
                int diff = bally - player2y;
                // if ( 0 <= diff and diff <= 3 );
                if ( 3 < diff and (player2y+4 < height)) 
                    p2->moveDown();
                else if ( diff < 0 and player2y > 0 )
                    p2->moveUp();
            }
            else {
                if ( bally < player2y+4 and player2y > 0 )
                    p2->moveUp();
                else if ( bally > player2y+5 and player2y+4 < height )
                    p2->moveDown();
            }
        }
    }

    void logic () {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = p1->getX();
        int player1y = p1->getY();
        int player2x = p2->getX();
        int player2y = p2->getY();

        // left bat        
        if ( ballx == player1x + 1 ) {
            if (bally == player1y or bally == player1y+3)
                // UPRIGHT, DOWNRIGHT
                ball->changeDir((eDir)(rand() % 2 + 5));
            else if (bally == player1y+1 or bally == player1y+2)
                // RIGHT, UPRIGHT, DOWNRIGHT
                ball->changeDir((eDir)(rand() % 3 + 4));
        }

        // right bat        
        if ( ballx == player2x - 1 ) {
            if (bally == player2y or bally == player2y+3)
                // UPLEFT, DOWNLEFT
                ball->changeDir((eDir)(rand() % 2 + 2));
            else if (bally == player2y+1 or bally == player2y+2)
                // LEFT, UPLEFT, DOWNLEFT
                ball->changeDir((eDir)(rand() % 3 + 1));
        }

        // bottom wall
        if ( bally >= height-1 )
            ball->changeDir(ball->getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT );

        // top wall
        if ( bally <= 0 )
            ball->changeDir((ball->getDir() == UPRIGHT) ? DOWNRIGHT : DOWNLEFT );

        // right wall 
        if ( ballx == width-1 ) 
            scoreUp(p1);

        // left wall
        if ( ballx == 0 ) 
            scoreUp(p2);
    }

    void run () {
        while (!quit)
        {
            draw();
            input();
            logic();
            usleep(80000);  // 80000x10^(-6) sec
        }
        
    }

    ~Manager_1Player() {
        delete p1, p2;
    }
};


#endif
