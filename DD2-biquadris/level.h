#ifndef LEVEL_H
#define LEVEL_H

#include "playerBlock.h"
#include <map>
#include <fstream>

class Level {
    int level;
    bool isRandom = true;
    std::ifstream cycle;
    static std::map<char, std::vector<std::pair<int,int>>> blockOrder;
    inline static std::map<int, std::pair<int, std::vector<std::pair<int, char>>>> odds = {
        // {level, {denominator, {numerator in cdf, character}}}
        {0, {12, {{2, 'I'}, {4, 'J'}, {6, 'L'}, {8, 'O'}, {9, 'S'}, {10, 'Z'}, {12, 'T'}}}},
        {1, {12, {{2, 'I'}, {4, 'J'}, {6, 'L'}, {8, 'O'}, {9, 'S'}, {10, 'Z'}, {12, 'T'}}}},
        {2, {7, {{1, 'I'}, {2, 'J'}, {3, 'L'}, {4, 'O'}, {5, 'S'}, {6, 'Z'}, {7, 'T'}}}}, 
        {3, {9, {{1, 'I'}, {2, 'J'}, {3, 'L'}, {4, 'O'}, {6, 'S'}, {8, 'Z'}, {9, 'T'}}}},
        {4, {9, {{1, 'I'}, {2, 'J'}, {3, 'L'}, {4, 'O'}, {6, 'S'}, {8, 'Z'}, {9, 'T'}}}}
    };
    inline static const int maxLevel = odds.size() - 1;
    std::ifstream noRandomCycle;
    public:
        Level(int startLevel, std::string filename);
        std::unique_ptr<PlayerBlock> createBlock(char blockType);
        int getLevel();
        void levelUp();
        void levelDown();
        std::unique_ptr<PlayerBlock> generateBlock();
        void random();
        void noRandom(std::string filename);
        void reset(int startLevel);
};



#endif

