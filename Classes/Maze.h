#ifndef __MAZE_H__
#define __MAZE_H__

#include "cocos2d.h"
class SquareCell;

class Maze : public cocos2d::Node
{
    const int grid_width = 400, grid_height = 400;
    const int w = 40;
    int row, col;
public:
    ~Maze();
    CREATE_FUNC(Maze);
    virtual bool init();

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::DrawNode *drawNode;
    int getIndex(int i, int j) { if(i<0||i>=row||j<0||j>=row) return -1; return i*col+j;}
    std::pair<cocos2d::Vec2, cocos2d::Vec2> getCellArea(int index);
    void BtnCallback1(Ref *pSender);
    SquareCell **grid;
    void SetupUI();
    int pickRandomUnvisitedNeighbor(int index);
};

#endif
