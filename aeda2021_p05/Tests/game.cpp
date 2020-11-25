#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game()
{

}

Game::Game(list<Kid>& l2)
{
    kids = l2;
}

void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}

list<Kid> Game::getKids() const
{
    return kids;
}

string Game::write() const
{
    string res;

    list<Kid>::const_iterator it;
    for(it = kids.begin(); it != kids.end(); it++){
        res += it->write() + "\n";
    }
    return res;
}

Kid& Game::loseGame(string phrase)
{
    // Last to stay loses

    int nr = numberOfWords(phrase);
    list<Kid>::const_iterator it = kids.begin();

    while (kids.size() != 1) {
        int size = kids.size();
        for (int i = 0; i < (nr - 1) % size; i++) {
            it++;
            if ( it == kids.end())
                it = kids.begin();
        }
        it = kids.erase(it);
        if ( it == kids.end())
            it = kids.begin();
    }

    Kid *k1 = new Kid(*it);

    return *k1;
}

list<Kid>& Game::reverse()
{
    list<Kid> temp;
    list<Kid>::reverse_iterator it;
    for(it = kids.rbegin(); it != kids.rend(); it++){
        temp.push_back(*it);
    }
    kids = temp;
    return kids;
}

list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;

    list<Kid>::const_iterator it;
    for(it = kids.begin(); it != kids.end(); it++){
        if(it->getAge() > id) {
            res.push_back(*it);
            it = kids.erase(it);
        }
    }
    return res;
}

void Game::setKids(const list<Kid>& l1)
{
    kids = l1;
}

bool Game::operator==(Game& g2)
{
    list<Kid> kids2 = g2.getKids();

    if (kids == kids2)
	    return true;
    return false;
}

list<Kid> Game::shuffle() const
{
    list<Kid> res;
    list<Kid>::const_iterator itpos = kids.begin();

    list<int> randNr;
    for(int i = 0; i < kids.size(); i++){
        int posRand = (rand() % kids.size());
        while(find(randNr.begin(), randNr.end(), posRand) != randNr.end())
            posRand = (rand() % kids.size());

        randNr.push_back(posRand);
        for (int pos = 0; pos != posRand; pos++) {
            itpos++;
        }
        res.push_back(*itpos);
        itpos = kids.begin();
    }

    return res;
}
