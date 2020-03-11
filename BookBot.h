#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

class BookBot {
private:
  map<string,vector<string>> markov_chain;

public:
    BookBot(const unsigned int seed);

    void readIn(const string & filename);
    bool isEndPunctuation(const char character);
    vector<string> getValues(const string & key);
    string generateSentence();
};
