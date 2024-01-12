#ifndef PLAYERBLOCK_H
#define PLAYERBLOCK_H

#include <vector>
#include <memory>
#include "absBlock.h"
#include "block.h"

class PlayerBlock{
    char c;
    int level;
    std::vector<std::pair<int,int>> tiles;
    std::pair<int, int> leftBot;
    std::pair<int, int> rightTop;    

    public:
        PlayerBlock(char c, int level, std::vector<std::pair<int,int>> tiles);
        void translate(int x, int y);
        void rotateC();
        void rotateCC();
        std::unique_ptr<AbsBlock> convert();
        const std::vector<std::pair<int,int>> &getTiles();
        int getLeft();
        int getRight();
        int getBot();
        int getTop(); 
        char getChar(int x, int y);
        char getC();
};




#endif

