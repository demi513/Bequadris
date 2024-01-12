#ifndef EXPLODING_BLOCK_H
#define EXPLODING_BLOCK_H

#include "absBlock.h"

class ExplodingBlock: public AbsBlock{
    int lifespan;

    void update() override;

};

#endif

