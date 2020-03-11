#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "BookBot.h"
#include "sanitize.h"

using namespace std;

bool BookBot::isEndPunctuation(const char character){
  if ((character == '.') || (character == '?') || (character == '!')){
    return true;
  }
  else{
    return false;
  }
}


BookBot::BookBot(const unsigned int seed){
  srand(seed);
}


void BookBot::readIn(const string & filename){
  ifstream inFile(filename);
    string word1,word2;
    word1 = "^";

  while(inFile>>word2){

        sanitize(word2);

        if(isEndPunctuation(word2[word2.size()-1])){

        string punctuation (1, word2[word2.size()-1]);
        word2 = word2.substr(0,word2.size()-1);

        markov_chain[word1].push_back(word2);
        markov_chain[word2].push_back(punctuation);

        word1 = "^";

        }

        else  {

          markov_chain[word1].push_back(word2);
          word1 = word2;

        }
}

      markov_chain["."].push_back("$");
      markov_chain["?"].push_back("$");
      markov_chain["!"].push_back("$");
}


 vector<string>BookBot::getValues(const string & key){
   return markov_chain[key];
 }

string BookBot::generateSentence(){
  string sentence = "";
  string key_ = "^";

  string word_pick;
  vector<string> words;

  while(key_ != "$"){
     words = markov_chain[key_];
    word_pick = words[(rand()% words.size())];

    if(word_pick != "$"){
    if(isEndPunctuation(word_pick.back())){
      sentence.pop_back();
   }
    sentence = sentence + word_pick + " ";
  }
  key_ = word_pick;
  }
  sentence.pop_back();
  return sentence;
}
