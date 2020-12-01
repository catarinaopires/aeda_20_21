#include "player.h"

void Player::addBet(const Bet& b)
{
    bets.insert(b);

}

unsigned Player::betsInNumber(unsigned num) const
{
	int counter;
    unordered_set<Bet, betHash, betHash>::const_iterator it = bets.begin();

    while(it != bets.end()){
        if(it->contains(num))
            counter++;
        it++;
    }
    return counter;
}

tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;

    unordered_set<Bet, betHash, betHash>::const_iterator it = bets.begin();

    while(it != bets.end()){
        if(it->countRights(draw) >= 3)
            res.insert(*it);
        it++;
    }
	return res;
}
