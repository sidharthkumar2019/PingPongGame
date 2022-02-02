#ifndef BAT_H
#define BAT_H

class Bat {
    int x, y, originalX, originalY;
public:
    Bat (int posX=0, int posY=0) {
        x =  originalX = posX;
        y = originalY = posY;
    }

    inline void reset () { x = originalX; y = originalY; }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveUp() { y-=1; }
    inline void moveDown() { y+=1; }
    
};

#endif