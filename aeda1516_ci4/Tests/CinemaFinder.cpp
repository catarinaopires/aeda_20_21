/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// To implement...


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

	for(auto f: films){
	    for(auto a: f.film->getActors()){
	        if(a == actorName){
	            res.push_back(f.film->getTitle());
	            break;
	        }
	    }
	}

	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

    for(auto f: films){
        if(f.film->getTitle() == filmTitle){
            f.film->addActor(actorName);
            return;
        }
    }

    Film* temp = new Film(filmTitle);
    temp->addActor(actorName);
    FilmPtr tmp; tmp.film = temp;
    films.insert(tmp);
}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName="";

    priority_queue<Cinema> temp = cinemas;
    while(!temp.empty()){
        for(auto s: temp.top().getServices()){
            if(s == service1){
                return temp.top().getName();
            }
        }
        temp.pop();
    }

	return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {
    bool done = false;
    priority_queue<Cinema> temp;
    while(!cinemas.empty()){
        if(cinemas.top().getDistance() < maxDistance){
            done = true;
            Cinema c = cinemas.top();
            c.addService(service1);
            temp.push(c);
        }
        else{
            temp.push(cinemas.top());
        }
        cinemas.pop();
    }
    cinemas = temp;

    if(!done){
        throw(CinemaNotFound());
    }
}
