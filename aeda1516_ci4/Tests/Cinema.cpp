/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// To implement...

bool Cinema::operator<(const Cinema & cr) const
{
    if(distance == cr.distance){
        return numberOfRooms < cr.numberOfRooms;
    }
	return distance > cr.distance;
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	Film *res = NULL;
    unsigned newH;
	BSTItrIn<FilmTime> it(timetable);

	while(!it.isAtEnd()){
	    if(it.retrieve().getHour() < h1){
	        res = it.retrieve().getFilm();
	        newH = it.retrieve().getHour();
	    }
	    else if(it.retrieve().getHour() == h1){
	        return it.retrieve().getFilm();

	    }
	    it.advance();
	}

	if(res != NULL)
	    h1 = newH;

	return res;
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
    BSTItrIn<FilmTime> it(timetable);
    FilmTime temp = FilmTime(0,NULL, 0);


    while(!it.isAtEnd()){
        if(it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h1) {
            temp = it.retrieve();
        }
        if(it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h2){
            return false;
        }
        it.advance();
    }

    if(temp == FilmTime(0,NULL, 0)){
        return false;
    }
    else{
        timetable.remove(temp);
        timetable.insert(FilmTime(h2, temp.getFilm(), temp.getRoomID()));
        return true;
    }


}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 0;
    BSTItrIn<FilmTime> it(timetable);

    while(!it.isAtEnd()){
        if(it.retrieve().getHour() == h1) {
            roomToUse = it.retrieve().getRoomID();
        }
        it.advance();
    }

    if(roomToUse < numberOfRooms){
        roomToUse++;
        timetable.insert(FilmTime(h1, f1, roomToUse));
        return roomToUse;
    }
	return 0;
}






