#include "explodingBlock.h"


void ExplodingBlock::update(){
    if (lifespan) {--lifespan; return;}
    tiles.clear();
}

