#include "trie.h"
#include "game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "board.h"
#include "text.h"
#include "graphics.h"

int main(int argc, char* argv[]){
    bool textonly = false;
    int startlevel = 0;
    std::string scriptfile1 = "sequence1.txt";
    std::string scriptfile2 = "sequence2.txt";
    std::srand(0);

    //detect command line args
    for (int i = 1; i < argc; ++i) {
        std::string arg {argv[i]};
        if (arg == "-text") { textonly = true;} 
        else if (arg == "-seed") { std::srand(std::stoi(std::string{argv[++i]})); } 
        else if (arg == "-scriptfile1") { scriptfile1 = std::string{argv[++i]};} 
        else if (arg == "-scriptfile2") { scriptfile2 = std::string{argv[++i]};} 
        else if (arg == "-startlevel") {startlevel = std::stoi(std::string{argv[++i]});}
    }

    Game g {scriptfile1, scriptfile2, startlevel, textonly};
    while (!std::cin.eof()){
        g.update();
    }

}

