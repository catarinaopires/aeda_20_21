#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y){
    brand = b;
    month = m;
    year = y;
}

string Vehicle::getBrand() const{
    return brand;
}

int Vehicle::getYear() const{
    return year;
}

int Vehicle::getMonth() const{
    return month;
}

int Vehicle::info() const{
    return 3;
}

int Vehicle::info(ostream &o) const{
    o << "Brand: " << brand << "; Month/Year: " << month << "/" << year << endl << endl << endl;;
    return 3;
}

bool Vehicle::operator < (const Vehicle & v) const{
    return (year < v.getYear() || (year == v.getYear() && month < v.getMonth()));
}

MotorVehicle::MotorVehicle(string b, int m, int y,string f,int cyl): Vehicle(b,m,y){
    fuel = f;
    cylinder = cyl;
}

string MotorVehicle::getFuel() const{
    return fuel;
}

int MotorVehicle::getCylinder() const{
    return cylinder;
}


int MotorVehicle::info() const {
    return 5;
}

int MotorVehicle::info(ostream &o) const{
    o << "Brand: " << brand << "; Month/Year: " << month << "/" << year << endl;
    o << "Fuel: " << fuel << "; Cylinder: " << cylinder << endl << endl;;
    return 5;
}

float MotorVehicle::calculateTax() const{
    if (year <= 1995){
            if ((fuel == "gas" && cylinder <= 1000) || (fuel != "gas" && cylinder <= 1500)) return 8.10;
            if ((fuel == "gas" && (cylinder > 1000 && cylinder <= 1300)) ||
            (fuel != "gas" && (cylinder > 1500 && cylinder <= 2000))) return 14.56;

            if ((fuel == "gas" && (cylinder > 1300 && cylinder <= 1750)) ||
            (fuel != "gas" && (cylinder > 2000 && cylinder <= 3000))) return 22.65;

            if ((fuel == "gas" && (cylinder > 1750 && cylinder <= 2600)) ||
            (fuel != "gas" && cylinder > 3000)) return 54.89;

            if (fuel == "gas" && (cylinder > 2600 && cylinder <= 3500)) return 87.13;
            if (fuel == "gas" && cylinder > 3500) return 148.37;
    }
    else{
        if ((fuel == "gas" && cylinder <= 1000) || (fuel != "gas" && cylinder <= 1500)) return 14.56;
        if ((fuel == "gas" && (cylinder > 1000 && cylinder <= 1300)) ||
            (fuel != "gas" && (cylinder > 1500 && cylinder <= 2000))) return 29.06;

        if ((fuel == "gas" && (cylinder > 1300 && cylinder <= 1750)) ||
            (fuel != "gas" && (cylinder > 2000 && cylinder <= 3000))) return 45.15;

        if ((fuel == "gas" && (cylinder > 1750 && cylinder <= 2600)) ||
            (fuel != "gas" && cylinder > 3000)) return 113.98;

        if (fuel == "gas" && (cylinder > 2600 && cylinder <= 3500)) return 181.17;
        if (fuel == "gas" && cylinder > 3500) return 320.89;
    }
}

Car::Car(string b, int m, int y, string f, int cyl): MotorVehicle(b,m,y,f,cyl){}

int Car::info() const {
    return 5;
}

int Car::info(ostream &o) const{
    o << "Brand: " << brand << "; Month/Year: " << month << "/" << year << endl;
    o << "Fuel: " << getFuel() << "; Cylinder: " << getCylinder() << endl << endl;

    return 5;
}

Truck::Truck(string b, int m, int y,string f, int cyl,int ml): MotorVehicle(b,m,y,f,cyl){
    maximumLoad = ml;
}

int Truck::info() const {
    return 6;
}


int Truck::info(ostream &o) const{
    o << "Brand: " << brand << "; Month/Year: " << month << "/" << year << endl;
    o << "Fuel: " << getFuel() << "; Cylinder: " << getCylinder() << endl << endl;;

    return 6;
}

Bicycle::Bicycle(string b, int m, int y, string t): Vehicle(b,m,y){
    type = t;
}

int Bicycle::info() const {
    return 4;
}


int Bicycle::info(ostream &o) const{
    o << "Brand: " << brand << "; Month/Year: " << month << "/" << year << endl;
    o << "Type: " << type << endl << endl;;

    return 4;
}

float Bicycle::calculateTax() const{
    return 0.0;
}