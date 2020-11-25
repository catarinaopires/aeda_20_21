#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

int CarPark::clientPosition(const string & name) const
{
    InfoCard i;
    i.name = name;

    return sequentialSearch(clients, i);
}

unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);


    if(pos == -1){
        InfoCard i; i.name = name;
        throw (ClientDoesNotExist(i));
    }
    else
        return clients[pos].frequency;
}

// TODO: to modify
bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    clients.push_back(info);
    return true;
}

// TODO: to modify
bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    freePlaces--;

    clients[pos].frequency++;

    return true;
}

// TODO: to modify
bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


InfoCard CarPark::getClientAtPos(unsigned p) const
{
    InfoCard info;

    if(p >= clients.size())
        throw PositionDoesNotExist(p);
    else
        info = clients[p];
    return info;
}

void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

bool sortName(InfoCard left, InfoCard right) {
    return left.name < right.name;
}

void CarPark::sortClientsByName()
{
    sort(clients.begin(), clients.end(), sortName);
}


vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    sortClientsByFrequency();

    vector<string> names;
    for (int i = 0; i < clients.size(); i++){
        if(clients[i].frequency >= f1 && clients[i].frequency <= f2)
            names.push_back(clients[i].name);
    }

    return names;
}


ostream & operator<<(ostream & os, const CarPark & cp)
{
    vector<InfoCard> c = cp.getClients();
    for(int i = 0; i < c.size(); i++){
        os << c[i].name << ", " ;
        if(!c[i].present)
            os << "not ";
        os << "present, " << c[i].frequency << "\n";
    }
    return os;
}


// EXERCÍCIO 2
// a)
// Complexidade espacial: S(n) = 1 (constante)
// Complexidade temporal: T(n) = n^2 = altura*largura

// b)
// Complexidade espacial: S(n) = 1 (constante)
// Complexidade temporal: T(n) = log n