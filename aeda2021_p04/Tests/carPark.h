#ifndef CARPARK_H_
#define CARPARK_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class InfoCard {
public:
    string name;
    bool present;
    int frequency;
    bool operator==(InfoCard right) const{
        return this->name == right.name;
    }
    bool operator<(InfoCard right) const{
        if (this->frequency == right.frequency){
            return this->name < right.name;
        }
        return this->frequency > right.frequency;
    }
};

class CarPark {
    unsigned freePlaces;
    const unsigned  capacity;
    vector<InfoCard> clients;
    const unsigned numMaxClients;
public:
    CarPark(unsigned cap, unsigned nMaxCli);
    unsigned getNumPlaces() const;
    unsigned getNumMaxClients() const;
    unsigned getNumOccupiedPlaces() const;
    vector<InfoCard> getClients() const;
    unsigned getNumClients() const;
    bool addClient(const string & name);
    bool removeClient(const string & name);
    bool enter(const string & name);
    bool leave(const string & name);
    int clientPosition(const string & name) const;
    friend ostream & operator<<(ostream & os, const CarPark & cp);
    unsigned getFrequency(const string &name) const;
    InfoCard getClientAtPos(unsigned p) const;
    void sortClientsByFrequency();
    void sortClientsByName();
    vector<string> clientsBetween(unsigned f1, unsigned f2);
};

class ClientDoesNotExist{
    InfoCard client;
public:
    ClientDoesNotExist(InfoCard i){ client = i;}
    string getName() const {return client.name;}
};

class PositionDoesNotExist{
    unsigned pos;
public:
    PositionDoesNotExist(unsigned p){pos = p;}
    unsigned getPosition() const { return pos;}
};
#endif /*CARPARK_H_*/
