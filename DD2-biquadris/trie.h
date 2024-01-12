#ifndef TRIE_H 
#define TRIE_H
#include <string>
#include <memory>

class TrieNode{
  public:
  static const int NUM_CHARS = 26;
  bool isWord;
  int words;
  std::string command;
  std::array<std::shared_ptr<TrieNode>, NUM_CHARS> letters;
  inline static const std::array<std::shared_ptr<TrieNode>, TrieNode::NUM_CHARS> emptyLetters{};

  TrieNode();
  ~TrieNode();
};


class Trie{
    std::shared_ptr<TrieNode> root;
    void insert(const std::string& word);     
    bool isInside(const std::string &word);

  public:
    Trie();
    ~Trie();

    std::string find(const std::string &word) const;


    void add_command(const std::string word, const std::string cmd);
};




#endif


