#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------


template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if(chambers.size() == maxCapacity)
        return false;

    for(int i = 0; i < chambers.size(); i++){
        if(*chambers[i] == *chamber)
            return false;
    }
    chambers.push_back(chamber);
    return true;
}

bool sortC(const Room* r1, const Room* r2){
    if ( r1->getCode() == r2->getCode())
        return r1->getFloor() > r2->getFloor();
    else
        return r1->getCode() < r2->getCode();
}

template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    sort(chambers.begin(), chambers.end(), sortC);
}

template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {

    for(int i = 0; i < chambers.size(); i++){
        if(chambers[i]->getCode() == code && chambers[i]->getFloor() == floor){
            Chamber * c = chambers[i];
            chambers.erase(chambers.begin()+i);
            return c;
        }
    }
    throw NoSuchChamberException();
}

class NoSuchFloorException {
    int f;
public:
    NoSuchFloorException(int f){ this->f = f; }
    int getFloor() const { return f;}
};

template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    int counter = 0;
    float totalarea = 0.0;

    for(int i = 0; i < chambers.size(); i++){
        if(chambers[i]->getFloor() == floor){
            counter++;
            totalarea += chambers[i]->getArea();
        }
    }

    if(counter == 0)
        throw NoSuchFloorException(floor);

    return totalarea/(float)counter;
}

template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    typename std::list<Chamber>:: iterator it;

    for(it = reservationsDone.begin(); it != reservationsDone.end(); it++ ){
        if(it->getCode() == code && it->getFloor() == floor){
            it->setReservation(true);
            return false;
        }
    }

    for(int i = 0; i < chambers.size(); i++){
        if(chambers[i]->getCode() == code && chambers[i]->getFloor() == floor){
            chambers[i]->setReservation(true);
            reservationsDone.push_back(*chambers[i]);
            return true;
        }
    }

    return false;
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    bool found = false;
    std::list<Chamber> res;
    typename std::list<Chamber>:: const_iterator it;

    for(int i = 0 ; i < chambers.size(); i++){
        for(it = reservationsDone.begin(); it != reservationsDone.end(); it++) {
            if (*it == *chambers[i]) {
                found = true;
                break;
            }
        }
        if(!found){
            res.push_back(*chambers[i]);
        }
        found = false;
    }

    return res;
}


#endif /* SRC_HOTEL_H_ */
