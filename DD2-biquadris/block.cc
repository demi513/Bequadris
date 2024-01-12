#include "block.h"

void Block::update(){}


Block::Block(char c, int level, std::vector<std::pair<int,int>> tiles):
    AbsBlock{c, level, tiles}
    {}

