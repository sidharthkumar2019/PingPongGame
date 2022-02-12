#ifndef OBJ_H
#define OBJ_H
#include <cstdlib>  // for rand()

enum eDir {STOP=0, LEFT=1, UPLEFT=2, DOWNLEFT=3, RIGHT=4, UPRIGHT=5, DOWNRIGHT=6};

class Object {  // Abstract base class
protected:
    int x, y;
    int originalX, originalY;

public:

    inline int getX() {return x;}
    inline int getY() {return y;}

    virtual void reset() = 0;
    virtual void move() = 0;
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual int getDir() = 0;
    virtual void ranDir() = 0;
    virtual void changeDir(eDir d) = 0;
};



class Ball : public Object {
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
    
    inline int getDir() {return direction;}

    inline void moveUp() {}
    inline void moveDown() {}
    

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

class Bat: public Object {
public:
    Bat() {}
    Bat (int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX; y = posY;
    }

    inline void reset () { x = originalX; y = originalY; }
    inline void moveUp() { y-=1; }
    inline void moveDown() { y+=1; }
    
    // Following are defined just so we don't get any errors while compiling
    inline void move() {}
    inline void ranDir() {}
    inline int getDir() {return 0;}
    inline void changeDir(eDir d) {}
};

#endif