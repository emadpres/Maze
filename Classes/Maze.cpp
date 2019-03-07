#include "Maze.h"
#include "ui/CocosGUI.h"
#include "SquareCell.h"
#include <iostream>

USING_NS_CC;

bool Maze::init()
{
    if ( !Node::init() )
    {
        return false;
    }

    srand(time(nullptr));

    row = floor(grid_width/w);
    col = floor(grid_height/w);

    grid = new SquareCell*[row*col];
    for(int i=0; i<row; i++) {
        for (int j = 0; j < col; j++) {
            grid[getIndex(i,j)] = new SquareCell(i, j);
        }
    }

    SetupUI();





//    auto closeItem = MenuItemImage::create("CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
//    float y = origin.y + closeItem->getContentSize().height/2;
//    closeItem->setPosition(Vec2(x,y));
//
//
//
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);


    return true;
}


std::pair<Vec2, Vec2> Maze::getCellArea(int index)
{
    int i = index / row;
    int j = index - i*row;
    Vec2 start = origin + Vec2(200,200) + Vec2(j * w, i * w);
    Vec2 destination = start + Vec2(0.95*w, 0.95*w);
    return std::make_pair(start, destination);
}


void Maze::SetupUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    drawNode = DrawNode::create();
    addChild(drawNode,100);
    for(int i=0; i<row*col; i++)
    {
        auto area = getCellArea(i);
        drawNode->drawRect(area.first, area.second, Color4F::WHITE);
    }



    ui::Button *startBtn = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    startBtn->setPosition(origin + startBtn->getContentSize()/2);
    startBtn->addClickEventListener(CC_CALLBACK_1(Maze::BtnCallback1,this));
    addChild(startBtn);
}

void Maze::BtnCallback1(Ref *pSender)
{

    static int next_cell_index = 0;

    auto scheduler = Director::getInstance()->getScheduler();

    scheduler->schedule([&](float dt){
            if(next_cell_index==-1) {
                Director::getInstance()->getScheduler()->unschedule("DFS", this);
                return;
            }
            auto cur_cell = grid[next_cell_index];
            cur_cell->Visit();
            auto area = getCellArea(next_cell_index);
            drawNode->drawSolidRect(area.first, area.second, Color4F::RED);
            next_cell_index = pickRandomUnvisitedNeighbor(next_cell_index);
        },this, 0.1, false, "DFS");
}

int Maze::pickRandomUnvisitedNeighbor(int index)
{
    int cur_i = index / col;
    int cur_j = index - cur_i*col;

    int nCandidates = 0;
    int candidates[] {-1,-1,-1,-1};

    for(int delta_x=-1; delta_x<=1; delta_x++)
        for(int delta_y=-1; delta_y<=1; delta_y++) {
            if (delta_x*delta_y!=0 || delta_x+delta_y==0)
                continue;
            int n = getIndex(cur_i+delta_x, cur_j+delta_y);
            if(n!=-1 && grid[n]->IsVisited()==false)
                candidates[nCandidates++] = n;
        }

    if(nCandidates==0)
        return -1;
    return candidates[rand()%nCandidates];

}

Maze::~Maze()
{
    for(int i=0; i<row; i++) {
        for (int j = 0; j < col; j++) {
            delete grid[getIndex(i,j)];
        }
    }
    delete[] grid;
}