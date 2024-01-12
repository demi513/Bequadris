#ifndef TEXT_H
#define TEXT_H
#include "observer.h"
#include <iostream>

class Board;

class Text: public Observer{
    Board* subject;
    std::ostream &out = std::cout;
    public:
        Text(Board *subject);
        ~Text();
        void notify() override;


};


#endif

