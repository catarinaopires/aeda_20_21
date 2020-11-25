#include "animal.h"
#include <sstream>
using namespace std;

Animal::Animal(string name, int age) {
    this->name = name;
    this->age = age;

    // Update youngest variable
    if(age < youngest)
        youngest = age;
}

// Initialize static variable
int Animal::youngest = 9999999;

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}


int Animal::getYoungest(){

    return youngest;
}


void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}
#include<iostream>

string Animal::getInfo() const{
    string str;

    str = name + ", " + to_string(age);
    if(getVeterinary())
        str += ", " + getVeterinary()->getInfo();

    return str;
}

Dog::Dog(string name, int age, string breed): Animal(name, age){
    this->breed = breed;
}

bool Dog::isYoung ()const{
    return age < 5;
}

string Dog::getInfo() const{
    string str = Animal::getInfo() + ", " + breed;
    return str;
}

Flying::Flying(int maxv, int maxa){
    maxVelocity = maxv;
    maxAltitude = maxa;
}

string Flying::getInfo() const{
    string str = ", " + to_string(maxVelocity) + ", " + to_string(maxAltitude);
    return str;
}

int Flying::getMaxVelocity() const{
    return maxVelocity;
}

int Flying::getMaxAltitude() const{
    return maxAltitude;
}

Bat::Bat(string name, int age, int maxv, int maxa): Animal(name, age), Flying(maxv, maxa){}

bool Bat::isYoung ()const{
    return age < 4;
}

string Bat::getInfo() const{
    string str = Animal::getInfo() + Flying::getInfo();
    return str;
}