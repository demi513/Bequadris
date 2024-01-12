#include "block.h"


AbsBlock::AbsBlock(char c, int level, std::vector<std::pair<int,int>> tiles):
    c{c}, level{level}, tiles{tiles}
    {}

AbsBlock::~AbsBlock(){}

const std::vector<std::pair<int,int>> &AbsBlock::getTiles(){
    return tiles;
}

int AbsBlock::getLevel(){
    return level;
}

void AbsBlock::clearRow(int row){
    for (auto tile = tiles.begin(); tile != tiles.end();){
        if (tile->second == row){tiles.erase(tile);}
        else if (tile->second < row){tile->second++; ++tile;}
        else {++tile;}
    }
}

char AbsBlock::getC(){ return c; }
