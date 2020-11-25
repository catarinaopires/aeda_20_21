#ifndef FLEET_H_
#define FLEET_H_

#include <vector>
#include "vehicle.h"
using namespace std;

class Fleet {
	vector<Vehicle *> vehicles;
public:
    vector<Vehicle *> getVehicles() const;
    void addVehicle(Vehicle *v1);
    int numVehicles() const; // retorna o nº de veículos no vector veiculos
    int lowestYear() const;  // retorna o menor ano dos veículos presentes no vetor veículos;
                             // retorna 0 se não existir nenhum veículo
	friend ostream & operator<<(ostream & o, const Fleet & f);
    vector<Vehicle *> operator () (int yearM) const;
    float totalTax() const;
    unsigned removeOldVehicles(int y1);

};


#endif /*FLEET_H_*/
