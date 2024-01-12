#include "trie.h"
#include <iostream>
#include <string>
#include <utility>
#include <memory>  


TrieNode::TrieNode(): 
    words{0}, 
    isWord{false}, 
    command{""},
    letters{emptyLetters}
    {    
}
TrieNode::~TrieNode(){}

Trie::Trie():
    //root{std::shared_ptr<TrieNode> (new TrieNode())}{}
    root{std::make_shared<TrieNode> ()}{}
Trie::~Trie(){}


bool Trie::isInside(const std::string &word){
    std::shared_ptr<TrieNode> current {root};
    if(!current){return false;}
    for(char const &c: word){
        int index = c - 'a';
        if (!current->letters[index]){return false;}
        current = current->letters[index];
    }
    return current->isWord;
}  

void Trie::insert(const std::string& word){

    std::shared_ptr<TrieNode> current = root;
    

    if (isInside(word)){return;}

    for(const char &c: word){
        int index = c - 'a';
        current->words += 1;
        if (!(current->letters[index])) {current->letters[index] = std::make_shared<TrieNode> ();}
        current = current->letters[index];
    }
    current->isWord = true;
    ++current->words;   
}


std::string Trie::find(const std::string &word) const{
    std::shared_ptr<TrieNode> current = root;
    for(const char &c: word){
        int index = c - 'a';
        if (!current->words) {return "";}
        if (!current->letters[index]){return "";}
        current = current->letters[index];
    }
    if(current->isWord) { return current->command; }
    else if(current->words != 1){return "";}
    while(current->words == 1){
        if(current->isWord){return current->command;}
        else{
            for(int i = 0; i < TrieNode::NUM_CHARS; ++i){
                if(current->letters[i]){
                    current = current->letters[i];
                    break;
                }
            }
        }
    }
    return "";
}

void Trie::add_command(const std::string word, const std::string cmd){
    insert(word);
    std::shared_ptr<TrieNode> current = root;
    for(const char &c: word){
        int index = c - 'a';
        current = current->letters[index];
    }
    current->command = cmd;
}
