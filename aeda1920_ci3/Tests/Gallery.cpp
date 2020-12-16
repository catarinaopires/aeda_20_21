#include "Gallery.h"
#include <ostream>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> temp;
    BSTItrIn<PaintCatalogItem> it(catalog);

    while(!it.isAtEnd()){
        if(it.retrieve().getAuthor() == a){
            temp.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    return temp;
}

vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> temp;
    BSTItrIn<PaintCatalogItem> it(catalog);

    while(!it.isAtEnd()){
        if(it.retrieve().getYear() >= y1 && it.retrieve().getYear() <= y2){
            temp.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    return temp;
}

bool Gallery::updateTitle(Paint* p, string tnew) {
    BSTItrIn<PaintCatalogItem> it(catalog);
    PaintCatalogItem old(p);
    while(!it.isAtEnd()){
        if(it.retrieve() == old){
            Paint* newPaint = new Paint(p->getAuthor(), tnew, p->getYear(), p->getPrice());
            PaintCatalogItem newC(newPaint);
            catalog.remove(it.retrieve());
            catalog.insert(newC);
            return true;
        }
        it.advance();
    }
    return false;
}

int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for(int i = 0; i < collection.size(); i++){
        pair<HashTableAuthorRecord::iterator, bool> res = authorRecords.insert(AuthorRecord(collection[i]->getAuthor()));
        if(!res.second){
            AuthorRecord a = *res.first;
            authorRecords.erase(res.first);
            a.addAvaliablePaint();
            authorRecords.insert(a);
        }
    }
    return authorRecords.size();
}

double Gallery::totalSells() const {
    double money = 0.0;

    for(auto a: authorRecords){
        money += a.getTotalSells();
    }
    return money;
}

double Gallery::sellPaint(string a, string t) {
    for(int i = 0; i < collection.size(); i++){
        if(collection[i]->getAuthor() == a && collection[i]->getTitle() == t){
            for(auto &author: authorRecords){

                if(author.getAuthor() == a){
                    AuthorRecord temp = author;
                    authorRecords.erase(author);
                    temp.subAvailablePaint();
                    temp.setTotalSells(temp.getTotalSells()+collection[i]->getPrice());
                    authorRecords.insert(temp);
                }
            }
            double price = collection[i]->getPrice();
            collection.erase(collection.begin()+i);
            i--;
            return price;
        }
    }
    return 0.0;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> v;
    priority_queue<ExhibitionItem> temp;
    int counter = 0, year;

    if(n >= 1){
        v.push_back(paintsToShow.top().getPaint());
        year = paintsToShow.top().getYear();
        counter++;
        paintsToShow.pop();
    }

    while(!paintsToShow.empty()){
        if(counter < maxPerYear){
            if(paintsToShow.top().getYear() == year){
                counter++;
            }
            else{
                year = paintsToShow.top().getYear();
                counter = 1;
            }
            v.push_back(paintsToShow.top().getPaint());
            paintsToShow.pop();
        }
        else{
            if(paintsToShow.top().getYear() == year){
                temp.push(paintsToShow.top());
            }
            else{
                v.push_back(paintsToShow.top().getPaint());
                year = paintsToShow.top().getYear();
                counter = 1;
            }
            paintsToShow.pop();
        }

        if(v.size() == n){
            break;
        }
    }

    while(!paintsToShow.empty()){
        temp.push(paintsToShow.top());
        paintsToShow.pop();
    }

    paintsToShow = temp;
    return v;
}

int Gallery::itemExibitionOrder(string a, string t) {
    int order = 1;

    priority_queue<ExhibitionItem> temp = paintsToShow;
    while(!temp.empty()){
        if(temp.top().getAuthor() == a && temp.top().getTitle() == t){
            return order;
        }
        order++;
        temp.pop();
    }

    return 0;
}

