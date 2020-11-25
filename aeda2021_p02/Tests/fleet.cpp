#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1){
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const{
    return (int)vehicles.size();
}


int Fleet::lowestYear() const{

    if(numVehicles() > 0) {
        int lowestY = vehicles[0]->getYear();
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i]->getYear() < lowestY)
                lowestY = vehicles[i]->getYear();
        }
        return lowestY;
    }
    else
        return 0;
}

ostream & operator<<(ostream & o, const Fleet & f){
    for (int i = 0; i < f.numVehicles(); i++){
        f.getVehicles()[i]->info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator () (int yearM) const{
    vector<Vehicle *> vYearM;

    for(int i = 0; i < vehicles.size(); i++){
        if(vehicles[i]->getYear() == yearM)
            vYearM.push_back(vehicles[i]);
    }

    return vYearM;
}

float Fleet::totalTax() const{
    float total = 0.0;

    for(int i = 0; i < vehicles.size(); i++)
            total += vehicles[i]->calculateTax();

    return total;
}

unsigned Fleet::removeOldVehicles(int y1){
    unsigned nrRemoved = 0;

    for(int i = 0; i < vehicles.size(); i++){
        if(vehicles[i]->getYear() <= y1){
            vehicles.erase(vehicles.begin() + i);
            i--;        // decrement the counter to prevent missing adjacent cars
            nrRemoved++;
        }
    }
    return nrRemoved;
}
