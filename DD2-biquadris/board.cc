#include "board.h"

void Board::insertTiles(){
    blocks.emplace_back(curBlock->convert());
    curBlock = nullptr;
    updateArray();
}

void Board::updateArray(){
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            charArray[i][j] = ' ';
            freeArray[i][j] = true;
        }
    }
    for (auto &block : blocks) {
        for (auto tile : block->getTiles()){
            charArray[tile.first][tile.second] = block->getC();
            freeArray[tile.first][tile.second] = false;
        }   
    }
    if (curBlock){
        for (auto tile : curBlock->getTiles()){
            charArray[tile.first][tile.second] = curBlock->getC();
        }
    }
    if (isBlind){
        for (int i = blindL; i < blindR; ++i){
            for (int j = blindU; j < blindD; ++j){
                charArray[i][Board::height - 1 - j] = '?';
            }
        }
    }
}

void Board::gravity(){
    curBlock->translate(0, heaviness);
    if (!isFreeAt(curBlock->getTiles())) {curBlock->translate(0, -heaviness); drop();}
    updateArray();
}

void Board::removeEmptyBlocks(){
    for (auto b = blocks.begin(); b != blocks.end();){
        if ((*b)->getTiles().empty()){
            score += ((*b)->getLevel()+1)*((*b)->getLevel()+1);
            blocks.erase(b);
        }else{
            ++b;
        }
    } 
}

void Board::clearRow(int row) {
    for (auto &b : blocks) {
        b->clearRow(row);
    }
}

int Board::getLeft(){ return nextBlock->getLeft(); }
int Board::getRight(){ return nextBlock->getRight(); }
int Board::getBot(){ return nextBlock->getBot(); }
int Board::getTop(){ return nextBlock->getTop(); }


int Board::getScore(){ return score; }
int Board::getLevel(){ return level.getLevel(); }
int Board::getHighScore(){ return highScore; }
char Board::getChar(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) { return ' '; }
    return charArray[x][y];
}


void Board::rotateC(int mult) {
    for (int i = 0; i < mult; ++i) { curBlock->rotateC(); }
    if (!isFreeAt(curBlock->getTiles())) {for (int i = 0; i < mult; ++i) { curBlock->rotateCC(); } return;}
    gravity();
}

void Board::drop() {
    bool keepDropping = true;
    while (keepDropping){
        curBlock->translate(0, 1);
        if (!isFreeAt(curBlock->getTiles())) {curBlock->translate(0, -1); keepDropping = false; }
    }
    insertTiles();
    if (isHeavy){ heaviness -= 2; }
    isHeavy = false;
    isBlind = false;
}

void Board::left(int mult){
    curBlock->translate(-mult, 0);
    if (!isFreeAt(curBlock->getTiles())) {curBlock->translate(mult, 0); return; }
    gravity();
}

void Board::right(int mult){
    curBlock->translate(mult, 0);
    if (!isFreeAt(curBlock->getTiles())) {curBlock->translate(-mult, 0); return; }
    gravity();
}

void Board::down(int mult){
    curBlock->translate(0, mult);
    if (!isFreeAt(curBlock->getTiles())) {curBlock->translate(0, -mult); return; } 
    gravity();
}

void Board::rotateCC(int mult) {
    for (int i = 0; i < mult; ++i) { curBlock->rotateCC(); }
    if (!isFreeAt(curBlock->getTiles())) {for (int i = 0; i < mult; ++i) { curBlock->rotateC(); } return;}
    gravity();
}

bool Board::isFreeAt(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) { return false; }
    return (freeArray[x][y]);
}

bool Board::isFreeAt(const std::vector<std::pair<int,int>> &tiles) {
    for (auto tile : tiles) {
        if (!isFreeAt(tile.first, tile.second)) { return false; }
    }
    return true;
}



const std::array<std::array<char, Board::height>, Board::width> &Board::getArray(){
    updateArray();
    return charArray;
}

void Board::render(){ notifyObservers(); }




void Board::levelEffects(){
    if (level.getLevel() == 3) {heaviness = std::max(1, heaviness);}
    if (level.getLevel() == 4 && !(rounds % 5) && (rounds)) {
        std::unique_ptr<PlayerBlock> temp = level.createBlock('*');
        std::swap(temp, curBlock);  
        if (isGameOver()){ return; }
        drop();
        std::swap(temp, curBlock);
    }
    ++rounds;
}

void Board::force(char blockType){
    nextBlock = level.createBlock(blockType);
}

void Board::blind(){
    isBlind = true;
}

void Board::heavy(){
    heaviness += 2;
    isHeavy = true;
} 


void Board::moveNextToCurBlock(){
    curBlock = std::move(nextBlock);
}

void Board::generateNextBlock(){
    nextBlock = std::move(level.generateBlock());
}

void Board::setCurBlock(char c) {
    curBlock = level.createBlock(c);
}

char Board::getCharNextBlock(int x, int y) { return nextBlock->getChar(x, y); }



bool Board::isEndTurn(){
    return (!curBlock);
}

bool Board::isGameOver(){
    return (!isFreeAt(curBlock->getTiles()));
}

void Board::reset(int startLevel){
    rounds = 0;
    highScore = std::max(score, highScore);
    level.reset(startLevel);
    score = 0;
    heaviness = 0;
    curBlock = nullptr;
    nextBlock = std::move(level.generateBlock());
    isHeavy = false;
    blocks.clear();
    updateArray();
}

    

void Board::random(){ level.random(); }

void Board::noRandom(std::string filename){ level.noRandom(filename); }



void Board::levelUp() {
    level.levelUp();
}

void Board::levelDown() {
    level.levelDown();
}



int Board::clearRows(){
    int linesCleared = 0;
    for (int y = 0; y < Board::height; ++y){
        bool isFull = true;
        for (int x = 0; x < Board::width; ++x){
            if (freeArray[x][y]) {isFull = false; break;}
        }
        if (isFull){ clearRow(y); ++linesCleared ;}        
    }
    if (linesCleared){ rounds = 0 ; score += ((linesCleared + level.getLevel()) * (linesCleared + level.getLevel()));}
    removeEmptyBlocks();
    updateArray();
    return linesCleared;
}


Board::Board(int numLevel, std::string scriptfile, int id):
    Subject{},
    level{numLevel, scriptfile},
    id{id}

{
    curBlock = nullptr;
    nextBlock = std::move(level.generateBlock());
    updateArray();
}

