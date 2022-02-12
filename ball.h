#ifndef BALL_H
#define BALL_H

enum eDir {STOP=0, LEFT=1, UPLEFT=2, DOWNLEFT=3, RIGHT=4, UPRIGHT=5, DOWNRIGHT=6};

class Ball {
    int x, y;
    int originalX, originalY;
    eDir direction;

    public:
    Ball (int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX; y = posY;
        direction = STOP;
    }   

    void reset () {
        x = originalX; y = originalY;   
        direction = STOP;
    }

    void changeDir (eDir d) {
        direction = d;
    }

    void ranDir() {
        direction = (eDir)((rand() % 6)+1);
    }
    
    inline int getX() {return x;}
    inline int getY() {return y;}
    inline int getDir() {return direction;}

    void move() {
        switch (direction)
        {
            case STOP:
                break;
            
            case LEFT:
                x--;
                break;
            
            case RIGHT:
                x++;
                break;
            
            case UPLEFT:
                x--; y--;
                break;
            
            case DOWNLEFT:
                x--; y++;
                break;
            
            case UPRIGHT:
                x++; y--;
                break;
            
            case DOWNRIGHT:
                x++; y++;
                break;
            
            default:
                break;
        }
    }
};

#endif