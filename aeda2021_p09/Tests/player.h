#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

struct betHash
{
	int operator() (const Bet& b) const
	{
        int s = 0;
        unordered_set<unsigned>::const_iterator it = b.getNumbers().begin();

        while(it != b.getNumbers().end()){
            s += *it;
            it++;
        }

		return s;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
		return b1.getNumbers() == b2.getNumbers();
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
