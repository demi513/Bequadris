#include "playerBlock.h"


PlayerBlock::PlayerBlock(char c, int level, std::vector<std::pair<int,int>> tiles):
    c{c}, level{level}, tiles{tiles}, leftBot{std::make_pair(INT32_MAX, 0)}, rightTop{std::make_pair(0, INT32_MAX)}
    {
        for (auto &tile : tiles){
            
            leftBot.first = std::min(tile.first, leftBot.first);
            leftBot.second = std::max(tile.second, leftBot.second);
            rightTop.first = std::max(tile.first, rightTop.first);
            rightTop.second = std::min(tile.second, rightTop.second);

        }

    }

std::unique_ptr<AbsBlock> PlayerBlock::convert(){
   return std::make_unique<Block> (c, level, tiles);


}


void PlayerBlock::translate(int x, int y){
    for (auto &tile : tiles ) {
        tile.first += x;
        tile.second += y;
    }
    leftBot.first += x;
    leftBot.second += y;
    rightTop.first += x;
    rightTop.second += y;
}

const std::vector<std::pair<int,int>> & PlayerBlock::getTiles(){ return tiles; }

#include <iostream>

void PlayerBlock::rotateC(){
    for (auto &tile : tiles ) {
        int oldX = tile.first;
        int oldY = tile.second;
        tile.first = leftBot.first + (leftBot.second - oldY);
        tile.second = leftBot.second + (oldX - leftBot.first) - rightTop.first + leftBot.first;
    
    }
    int old_rightTop_first = rightTop.first;
    int old_rightTop_second = rightTop.second;
    rightTop.first = leftBot.first + (leftBot.second - old_rightTop_second);
    rightTop.second = leftBot.second - (old_rightTop_first - leftBot.first);    
}

void PlayerBlock::rotateCC(){
    for (auto &tile : tiles ){
        int oldX = tile.first;
        int oldY = tile.second;
        tile.first = leftBot.first - (leftBot.second - oldY) + leftBot.second - rightTop.second;
        tile.second = leftBot.second - (oldX - leftBot.first);
    }
    int old_rightTop_first = rightTop.first;
    int old_rightTop_second = rightTop.second;
    rightTop.first = leftBot.first + (leftBot.second - old_rightTop_second);
    rightTop.second = leftBot.second - (old_rightTop_first - leftBot.first);
}

/*int PlayerBlock::addHeaviness(int h){
    heaviness+=h;
    return heaviness;
}*/



char PlayerBlock::getChar(int x, int y) {
    for (auto tile : tiles){
        if (tile.first == x && tile.second == y){ return c; }
    }
    return ' ';
}

char PlayerBlock::getC(){
    return c;
}
int PlayerBlock::getLeft(){ return leftBot.first; }
int PlayerBlock::getRight(){ return rightTop.first; }
int PlayerBlock::getBot(){ return leftBot.second; }
int PlayerBlock::getTop(){ return rightTop.second; }



