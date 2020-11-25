#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

Client::Client() {
    numGifts = (rand() % 5) + 1;
}

unsigned Client::getNumGifts() const {
    return numGifts;
}

Counter::Counter(unsigned wt): wrappingTime(wt) {
    numAttendedClients = 0;
    actualTime = 0;
    nextEnter = (rand() % 20) + 1;
    nextLeave = 0;
}

unsigned Counter::getActualTime() const {
    return actualTime;
}

unsigned Counter::getNextEnter() const {
    return nextEnter;
}

unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

unsigned Counter::getNextLeave() const {
    return nextLeave;
}

Client & Counter::getNextClient() {
    if(clients.empty())
        throw EmptyQueue();
    return clients.front();
}

void Counter::enter()
{
    Client c;
    cout << "Actual Time: " << actualTime << endl;

    if(clients.empty()){
        nextLeave = actualTime + c.getNumGifts() * wrappingTime;
    }
    clients.push(c);

    nextEnter = actualTime + (rand() % 20) + 1;

    cout << "new customer arrived with " << c.getNumGifts() << " gifts" << endl;
}

void Counter::leave()
{

    try {
        getNextClient();
        cout << "Actual Time: " << actualTime << endl;
    }
    catch (EmptyQueue &e) {
        cout << e.getMsg() << endl;
        return;
    }

    Client& c = clients.front();
    clients.pop();

    cout << "customer who left had " << c.getNumGifts() << " gifts" << endl;
    numAttendedClients++;

    if(!clients.empty())
        nextLeave = actualTime + clients.front().getNumGifts() * wrappingTime;

}

void Counter:: nextEvent()
{
    if(!clients.empty()) {
        if (nextEnter < nextLeave) {
            actualTime = nextEnter;
            enter();
        }
        else{
            actualTime = nextLeave;
            leave();
        }
    }
    else{
        actualTime = nextEnter;
        enter();
    }
}

ostream & operator << (ostream & out, const Counter & c2)
{
    out << "Number of attended clients: " << c2.getNumAttendedClients() << endl;
    out << "Number of clients waiting: " << c2.clients.size() << endl;
    return out;
}


