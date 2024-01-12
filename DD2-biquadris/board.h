#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include "subject.h"
#include "playerBlock.h"
#include "level.h"
#include "absBlock.h"

class Board: public Subject{
    public:
        static const int width = 11;
        static const int height = 18;
    private:
        inline static const int blindL = 2;
        inline static const int blindR = 9;
        inline static const int blindU = 2;
        inline static const int blindD = 12;
        inline static int highScore = 0;
        int rounds = 0;
        // might not be allowed
        Level level;
        const int id;
        int score = 0;
        int heaviness = 0;
        std::unique_ptr<PlayerBlock> curBlock;
        std::unique_ptr<PlayerBlock> nextBlock;
       

        bool isHeavy = false;
        bool isBlind = false;
        std::vector<std::unique_ptr<AbsBlock>> blocks;  
        std::array<std::array<char, height>, width> charArray;
        std::array<std::array<bool, height>, width> freeArray;

    
        void insertTiles();
        void updateArray();
        void gravity();
        void removeEmptyBlocks();
        void clearRow(int row);
        bool isFreeAt(int x, int y);
        bool isFreeAt(const std::vector<std::pair<int,int>> &tiles);
    
    public:
        int getLeft();
        int getRight();
        int getBot();
        int getTop(); 

        int getHighScore();
        int getScore();
        int getLevel();
        char getChar(int x, int y);

        void rotateC(int mult);
        void rotateCC(int mult);
        void drop();
        void left(int mult);
        void right(int mult);
        void down(int mult);


        const std::array<std::array<char, height>, width> &getArray();
        void render();

        void levelEffects();
        void heavy();
        void force(char blockType);
        void blind();
        
        void generateNextBlock();
        char getCharNextBlock(int x, int y);
        void moveNextToCurBlock();
        void setCurBlock(char c);

        void levelUp();
        void levelDown();

        bool isEndTurn();
        bool isGameOver();
        void reset(int startLevel);

        int clearRows();
        
        void noRandom(std::string filename);
        void random();

        Board(int numLevel, std::string scriptfile,int id);
};


#endif

