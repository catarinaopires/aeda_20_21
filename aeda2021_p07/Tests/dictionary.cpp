#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.getWord();
}

void Dictionary::readDictionary(ifstream &f)
{
    string line, m;

    while(getline(f,line )){
        getline(f,m );
        words.insert(WordMeaning(line, m));
    }
     return;
}

string Dictionary::searchFor(string word) const
{
    WordMeaning w(word, "");
    WordMeaning w1 = words.find(w);
    string tempW = "", tempM = "";

    string wordBefore,mBefore,wordAfter = "", mAfter= "";

    if(w1.getMeaning() == ""){
        BSTItrIn<WordMeaning> it(words);

        while(!it.isAtEnd()){
            if(it.retrieve().getWord() < word){
                tempW = it.retrieve().getWord();
                tempM = it.retrieve().getMeaning();
                it.advance();
            }
            else
                break;
        }
        wordBefore = tempW;
        mBefore = tempM;

        if(!it.isAtEnd()){
            tempW = it.retrieve().getWord();
            tempM = it.retrieve().getMeaning();
            wordAfter = tempW;
            mAfter = tempM;
        }

        throw WordInexistent(wordBefore, mBefore,wordAfter, mAfter);
    }
    else
        return w1.getMeaning();
}

bool Dictionary::correct(string word, string newMeaning)
{
    WordMeaning w(word, "");
    WordMeaning w1 = words.find(w);

    if(w1.getMeaning() == ""){
        WordMeaning newWord(word, newMeaning);
        words.insert(newWord);
        return false;
    }
    words.remove(w1);
    WordMeaning newWord(word, newMeaning);
    words.insert(newWord);
    return true;
}

void Dictionary::print() const
{
    for(auto it = words.begin(); it != words.end(); it++){
        cout << (*it).getWord() << endl;
        cout << (*it).getMeaning() << endl;
    }
}

