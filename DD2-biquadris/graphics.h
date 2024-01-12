#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "observer.h"
#include "board.h"
#include <iostream>
#include "window.h"

class Graphics final: public Observer{
    Board *subject;
    inline static const int tileWidth = 20;
    inline static std::map<char, int> charToColour = {
        {'Z', Xwindow::Red},
        {'S', Xwindow::Green}, 
        {'L', Xwindow::Blue}, 
        {'I', Xwindow::Cyan}, 
        {'O', Xwindow::Yellow}, 
        {'T', Xwindow::Magenta}, 
        {'J', Xwindow::Orange}, 
        {'*', Xwindow::White},
        {'?', Xwindow::Brown},
        {' ', Xwindow::Black}};
    std::unique_ptr<Xwindow> w;
    public:
        Graphics(Board* subject);
        ~Graphics();
        void notify() override;


};

#endif

