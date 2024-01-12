#include "graphics.h"
#include "board.h"


Graphics::Graphics(Board *subject):
    subject{subject} {
    w = std::make_unique<Xwindow>(tileWidth * (Board::width + 2), tileWidth * (Board::height + 9));
    subject->attach(this);
}

Graphics::~Graphics(){subject->detach(this); }


#include <iostream>

void Graphics::notify(){
    std::string s;

    w->fillRectangle(0,0, tileWidth * (Board::width + 2), tileWidth * (Board::height + 9), Xwindow::White );


    std::string highScoreMes = "High Score: " + std::to_string(subject->getHighScore());
    w->drawString(tileWidth, tileWidth, highScoreMes);
    

    std::string currentLevelMes = "Level: " + std::to_string(subject->getLevel());
    w->drawString(tileWidth, tileWidth * 2, currentLevelMes);


    std::string currentScoreMes = "Score: " + std::to_string(subject->getScore());
    w->drawString(tileWidth, tileWidth * 3, currentScoreMes);



    const auto &arr = subject->getArray();
    for (int y = 0; y < Board::height; ++y) {
        for (int x = 0; x < Board::width; ++x) {
            w->fillRectangle(tileWidth * (x+1), tileWidth * (y + 4) , tileWidth, tileWidth, charToColour[arr[x][y]]);    
        }

    }
    



    w->drawString(tileWidth, tileWidth * (Board::height + 5), "Next: ");

    
    for (int y = subject->getTop(); y < subject->getBot() + 1; ++y) {
        for (int x = subject->getLeft(); x < subject->getRight() + 1; ++x){
            if (subject->getCharNextBlock(x, y) == ' ') { continue; }
            w->fillRectangle(tileWidth * (1 + x - subject->getLeft()), tileWidth * (Board::height + 6 + y - subject->getTop()), tileWidth, tileWidth, charToColour[subject->getCharNextBlock(x, y)]);
        }
    }
}


