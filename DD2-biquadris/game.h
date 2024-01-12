#ifndef GAME_H
#define GAME_H
#include <memory>
#include "trie.h"
#include <vector>
#include "observer.h"
#include "board.h"

class Game{
    int turn = 0;
    static const int numPlayers = 2;
    std::array<std::unique_ptr<Board>, numPlayers> boards;
    std::vector<std::unique_ptr<Observer>> observers;
    Trie trieCmd;
    int startLevel;
    

    void gameOver();
    void render();
    void processEffects(std::istream &in);
    void processCommands(std::istream &in);
    void reset();


    public:
        void update();
        
        Game(std::string scriptfile1, std::string scriptfile2,int startLevel, bool textonly);

};


#endif

