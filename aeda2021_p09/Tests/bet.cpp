#include "bet.h"
#include <set>
#include <iostream>
#include <sstream>
using namespace std;


bool Bet::contains(unsigned num) const
{
	return numbers.find(num) != numbers.end();
}

void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    /*set<unsigned> s(values.begin(), values.end());
    vector <unsigned> v(s.begin(), s.end());

    for(int i = 0; i < n; i++){
        numbers.insert(v[i]);
    }*/

    int counter = 0;
    typedef unordered_set<unsigned>::iterator it;

    for(int i = 0; i < values.size(); i++){

        pair<it, bool> res = numbers.insert(values[i]);

        if(res.second)
            counter++;
        if(counter == n)
            break;
    }
}

unsigned Bet::countRights(const tabHInt& draw) const
{
    unordered_set<unsigned>::const_iterator it = numbers.begin();
    int counter = 0;

    while(it != numbers.end()){
        if(draw.find(*it) != draw.end())
            counter++;
        it++;
    }

    return counter;
}
