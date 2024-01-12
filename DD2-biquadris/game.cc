#include "game.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "text.h"
#include "graphics.h"


void Game::processCommands(std::istream &in){
    std::string s;
    while(in >> s){ 
        std::string cmd;
        int mult = 1;
        if(isdigit(s[0])){
            std::istringstream iss{s};
            iss >> mult;
            iss >> cmd;
            
        }
        else{cmd = s;}
        int i=0;
        while (cmd[i]) { cmd[i] = tolower(cmd[i]); ++i;}
        cmd = trieCmd.find(cmd);
        std::istringstream iss {cmd}; 
        while (iss >> cmd){
            if(cmd == ""){ continue; }
            if(cmd == "rename"){
                std::string macro_cmd;
                std::string full_cmd;
                if (!(iss >> macro_cmd >> full_cmd)){ in >> macro_cmd >> full_cmd; }
                trieCmd.add_command(macro_cmd, full_cmd);
            }
            else if(cmd == "restart"){
                reset();
                return;
            }
            else if(cmd == "random"){ boards[turn]->random(); }
            else if(cmd == "i"){ boards[turn]->setCurBlock('I');}
            else if(cmd == "j"){ boards[turn]->setCurBlock('J');}
            else if(cmd == "l"){ boards[turn]->setCurBlock('L');}
            else if(cmd == "s"){ boards[turn]->setCurBlock('S');}
            else if(cmd == "z"){ boards[turn]->setCurBlock('Z');}
            else if(cmd == "o"){ boards[turn]->setCurBlock('O');}
            else if(cmd == "t"){ boards[turn]->setCurBlock('T');}
            else if(cmd == "norandom"){ 
                std::string filename;
                if (!(iss >> filename)){ in >> filename; }
                boards[turn]->noRandom(filename);
            }    
            else if(cmd == "left"){ boards[turn]->left(mult); }
            else if(cmd == "right"){ boards[turn]->right(mult); }
            else if(cmd == "down"){ boards[turn]->down(mult); }
            else if(cmd == "clockwise"){ boards[turn]->rotateC(mult); }
            else if(cmd == "counterclockwise"){ boards[turn]->rotateCC(mult); }
            else if(cmd == "drop"){ boards[turn]->drop(); }
            else if(cmd == "levelup"){ boards[turn]->levelUp(); }
            else if(cmd == "leveldown"){ boards[turn]->levelDown(); }
            
            // we can't use sequence to change turns
            else if(cmd == "sequence"){
                std::string filename;
                if (!(iss >> filename)){ in >> filename; }
                std::ifstream ifs {filename};
                processCommands(ifs);
            }
            render();
            if (boards[turn]->isEndTurn()){ return; }

        }
    }
}

void Game::processEffects(std::istream &in){
    std::string effect;
    while(in >> effect){
        effect = trieCmd.find(effect);
        if (effect == "blind" || effect == "heavy" || effect == "force") { break; }
    }

    for (int player = 0; player < numPlayers; ++player){
        if (player == turn) { continue; }
        if (effect == "blind") {boards[player]->blind();}
        if (effect == "heavy") {boards[player]->heavy();}
        if (effect == "force") {char blockType; in >> blockType; boards[player]->force(blockType);}
    }
}

void Game::update(){
    boards[turn]->moveNextToCurBlock();
    if (boards[turn]->isGameOver()){gameOver(); return; }
    boards[turn]->generateNextBlock();
    boards[turn]->levelEffects();
    if (boards[turn]->isGameOver()){gameOver(); return; }
    render();
    processCommands(std::cin);
    int cleared = boards[turn]->clearRows();
    if(cleared){
        render();
        if (cleared >= 2){
            processEffects(std::cin);   
            render(); 
        }
    }
    turn = (turn + 1) % numPlayers;
}




void Game::reset(){
    turn = numPlayers - 1;
    for (auto &b : boards) {b->reset(startLevel);}
}

void Game::gameOver(){
    reset();
}

Game::Game(std::string scriptfile1, std::string scriptfile2,int startLevel, bool textonly):
    startLevel{startLevel}, boards{}
{
    std::vector<std::string> commands{"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup",
                                      "leveldown", "norandom", "random", "sequence", "restart", "rename", "blind", "heavy", "force",
                                      "i","j","l","s","z","o","t"};

    for(auto cmd : commands){
        trieCmd.add_command(cmd, cmd);
    }
    for (int i = 0; i < numPlayers; ++i) {
        boards[i] = std::make_unique<Board> (startLevel,(i==0?scriptfile1:scriptfile2), i);
        observers.emplace_back(std::make_unique<Text> (boards[i].get()));
        if (!textonly){
           observers.emplace_back(std::make_unique<Graphics> (boards[i].get()));
        }
    }


}
void Game::render(){
    for (auto &b: boards){ b->render(); }
}

