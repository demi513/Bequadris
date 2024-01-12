#include "level.h"
#include <cstdlib>
#include "playerBlock.h"
#include "board.h"

std::map<char, std::vector<std::pair<int,int>>> Level:: blockOrder = {
    {'I', {{0,3},{1,3},{2,3},{3,3}}},
    {'J', {{0,3},{1,3},{2,3},{0,2}}},
    {'L', {{0,3},{1,3},{2,3},{2,2}}},
    {'O', {{0,2},{0,3},{1,2},{1,3}}},
    {'S', {{0,3},{1,3},{1,2},{2,2}}},
    {'Z', {{0,2},{1,2},{1,3},{2,3}}},
    {'T', {{0,3},{1,3},{2,3},{1,2}}},
    {'*', {{Board::width/2, 0}}}
};

std::unique_ptr<PlayerBlock> Level::createBlock(char blockType){
    return std::make_unique<PlayerBlock> (blockType, level, blockOrder[blockType]);
}

int Level::getLevel() { return level;}

void Level::levelUp() {if (level < maxLevel) {++level;} ; isRandom=true; }
void Level::levelDown() { if (level > 0) {--level;} isRandom=true; }

    
Level::Level(int startLevel, std::string filename):
    level{startLevel}, cycle{filename}, noRandomCycle{filename}
    {}


void Level::noRandom(std::string filename){
    if (level < 3){return;}
    noRandomCycle = std::ifstream{filename};
    isRandom = false;
}

void Level::random(){ 
    if (level < 3) {return;} 
    isRandom = true;
}


std::unique_ptr<PlayerBlock> Level::generateBlock() {    
    if (!level) { 
        char next;
        cycle >> next;
        if (cycle.eof()) {
            cycle.clear();
            cycle.seekg(0, std::ios::beg);
            cycle >> next;
        }        
        return createBlock(next);
    }
    if (isRandom) {
        int sample = rand() % odds[level].first;
        for (auto duo : odds[level].second){
            if (duo.first >= sample){
                return createBlock(duo.second);
            }
        }
    }
    
    char next;
    noRandomCycle >> next;
    if (noRandomCycle.eof()) {
        noRandomCycle.clear();
        noRandomCycle.seekg(0, std::ios::beg);
        noRandomCycle >> next;
    }

    return createBlock(next);


}

void Level::reset(int startLevel){
    level = startLevel;
    isRandom = true;
    cycle.clear();
    cycle.seekg(0, std::ios::beg);
    
}

