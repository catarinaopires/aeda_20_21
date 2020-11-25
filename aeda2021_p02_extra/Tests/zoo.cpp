#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

vector<Animal *> Zoo::getAnimals() const{
    return animals;
}

void Zoo::addAnimal(Animal *a1){
    animals.push_back(a1);
}

string Zoo::getInfo () const{
    string str;

    for(int i=0; i < animals.size(); i++){
            str += animals[i]->getInfo() + " \n";
    }
    return str;
}

bool Zoo::isYoung(string nameA){
    for(int i=0; i < animals.size(); i++){
        if(animals[i]->getName() == nameA)
            return animals[i]->isYoung();
    }

    // If animal does not exist
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    string input;
    string input_name;
    long input_cod;

    int i = 0;
    while (getline(isV, input)) {
        input_name = input;
        getline(isV, input);
        input_cod = stol(input);

        Veterinary *v = new Veterinary(input_name, input_cod);
        veterinarians.push_back(v);

        if (i < animals.size()) {
            animals[i]->setVeterinary(v);
            i++;
        }
    }
}

bool Zoo::removeVeterinary (string nameV){
    for (int i=0; i< veterinarians.size(); i++){
        if(veterinarians[i]->getName() == nameV){

            for(int j = 0; j < animals.size(); j++){
                if(animals[i]->getVeterinary() == veterinarians[i])
                    animals[i]->setVeterinary(veterinarians[i + 1]);
            }
            veterinarians.erase(veterinarians.begin() + i);

            return true;
        }
    }

    return false;
}

bool Zoo::operator < (Zoo& zoo2) const{
    int sumAges = 0;
    int sumAgesZoo2 = 0;
    for(int i=0; i < animals.size(); i++){
        sumAges += animals[i]->getAge();
    }

    for(int i=0; i < zoo2.getAnimals().size(); i++){
        sumAgesZoo2 += zoo2.getAnimals()[i]->getAge();
    }
    return sumAges < sumAgesZoo2;
}


