//
// Created by Tiago on 16/11/2019.
//

#include "Purchase.h"
#include <stack>

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
    return client;
}

list< stack<Article*> > Purchase::getBags() const {
    return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

    Article *a = new Article(client, barCode);
    a->setPresent(present); a->setDeliverHome(deliverHome);
    return a;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

    auto it  = bags.end();
    it--;
    if((*it).size() < BAG_SIZE){
        (*it).push(article);
    }
    else{
        stack<Article*> b;
        b.push(article);
        bags.push_back(b);
    }
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

    vector<Article*> res;

    for(auto it = bags.begin(); it != bags.end(); it++){
        stack<Article*> s;
        while(!(*it).empty()){
            if((*it).top()->getPresent()){
                res.push_back((*it).top());
                (*it).pop();
            }
            else{
                s.push((*it).top());
                (*it).pop();
            }

        }

        while (!s.empty()) {
            (*it).push(s.top());
            s.pop();
        }
    }
    return res;
}

