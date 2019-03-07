
#ifndef MAZE_SQUARE_CELL_H
#define MAZE_SQUARE_CELL_H

#include <utility>
#include <cocos/math/CCGeometry.h>

class SquareCell {
public:
    SquareCell(int i, int j);
    void Visit();
    bool IsVisited(){return m_isVisited;}
    //cocos2d::Rect getArea();
private:
    int m_i,m_j, m_w;
    bool walls[4];
    bool m_isVisited;

};


#endif
