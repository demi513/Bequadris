#ifndef BLOCK_H
#define BLOCK_H

#include "absBlock.h"

class Block : public AbsBlock {
    public:
        Block(char c, int level, std::vector<std::pair<int,int>> tiles);
        void update() override;
};

#endif
