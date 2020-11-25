#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


class WordInexistent
{
    string wordBefore,mBefore,wordAfter, mAfter;
public:
    WordInexistent(string wordBefore, string mBefore, string wordAfter, string mAfter){
        this->wordBefore = wordBefore;
        this->mBefore = mBefore;
        this->mAfter = mAfter;
        this->wordAfter = wordAfter;
    }
    string getWordBefore() const {return wordBefore; }
    string getMeaningBefore() const { return mBefore; }
    string getWordAfter() const { return wordAfter; }
    string getMeaningAfter() const { return mAfter; }
};

#endif