#include "text.h"
#include <iomanip>
#include "board.h"

Text::Text(Board *subject): subject{subject} { subject->attach(this); }


Text::~Text(){ subject->detach(this); }


void Text::notify(){
  out << "HighScore" << std::setw(Board::width - 9) << subject->getHighScore() << "\n";
  out << "Level:" << std::setw(Board::width - 6) << subject->getLevel() << "\n";
  out << "Score:" << std::setw(Board::width - 6) << subject->getScore() << "\n";
  out << std::string (Board::width, '-') << "\n";
  const auto &arr = subject->getArray();
  for (int y = 0; y < Board::height; ++y){
    for (int x = 0; x < Board::width; ++x){
      out << arr[x][y];
    }
    out << "\n";
  }
  out << std::string (Board::width, '-') << "\n";
  out << "Next:" + std::string(Board::width - 5, ' ') << "\n";
  for (int y = subject->getTop(); y < subject->getBot() + 1; ++y) {
    for (int x = subject->getLeft(); x < subject->getRight() + 1; ++x){
      out << subject->getCharNextBlock(x, y);
    }
    out << "\n";
    
  }
  out << "\n";
}

