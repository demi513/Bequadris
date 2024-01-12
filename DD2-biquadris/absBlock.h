#ifndef ABS_BLOCK_H
#define ABS_BLOCK_H

#include <memory>
#include <vector>

class AbsBlock {
    char c;
    int level;
    protected:
        std::vector<std::pair<int,int>> tiles;

    public:
        const std::vector<std::pair<int,int>> &getTiles();
        virtual void update() = 0;        
        int getLevel();
        void clearRow(int row);
        char getC();

        AbsBlock(char c, int level, std::vector<std::pair<int,int>> tiles);
        virtual ~AbsBlock() = 0;
};



#endif

