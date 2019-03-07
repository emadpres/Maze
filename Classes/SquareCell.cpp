#include "SquareCell.h"

USING_NS_CC;

SquareCell::SquareCell(int i, int j)
{
    m_i = i;
    m_j = j;

    for(int i=0; i<4; i++)
        walls[i] = false;
    m_isVisited = false;
}


void SquareCell::Visit()
{
    m_isVisited = true;
}

//cocos2d::Rect SquareCell::getArea() {
//    Vec2 start = Vec2(m_i * m_w, m_j * m_w);
//    Vec2 destination = start + Vec2(0.95*m_w, 0.95*m_w);
//    return Rect(start, destination);
//}

