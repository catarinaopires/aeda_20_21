/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
    BSTItrIn<Expertize> it(expertizes);
    Expertize e(expertizeAvailable, cost);
    while(!it.isAtEnd()){
        if(it.retrieve() == e){
            it.retrieve().addConsultant(student);
            return;
        }
        it.advance();
    }

    e.addConsultant(student);
    expertizes.insert(e);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;

    BSTItrIn<Expertize> it(expertizes);
    Expertize e(project->getExpertize(), project->getCost());
    while(!it.isAtEnd()){
        if(it.retrieve() == e){
            for(auto s: it.retrieve().getConsultants()){
                if(s->getCurrentProject() == "")
                    temp.push_back(s);
            }
        }
        it.advance();
    }

	return temp;
}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	if(project->getConsultant() != NULL || student->getCurrentProject() != "")
	    return false;

	Expertize e = expertizes.find(Expertize(project->getExpertize(), project->getCost()));
    if(e == Expertize("", 0)){
        return false;
    }

    for(auto s: e.getConsultants()){
        if(s->getName() == student->getName() && s->getEMail() == student->getEMail()){
            student->addProject(project->getTitle());
            project->setConsultant(student);
            return true;
        }
    }
    return false;
}

//
// Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
    students.insert(student);

}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	for(auto it = students.begin(); it != students.end(); it++){
	    if(it->getEMail() == student->getEMail()){
	        student->setEMail(newEMail);
	        students.erase(it);
	        students.insert(student);
	    }
	}

}


//
// Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for(auto c: candidates){
	    if(c.getPastProjects().size() >= min){
            activeStudents.push(c);
	    }
	}

}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    if(activeStudents.empty())
        return 0;

    int max  = activeStudents.top().getPastProjects().size();;
    priority_queue<Student> temp = activeStudents;
    temp.pop();

    if(temp.empty()){
        studentMaximus = activeStudents.top();
        return activeStudents.size();
    }

    // Because the priority_queue is sorted there's no need to see more than the 2 firsts students
    if(temp.top().getPastProjects().size() == max){
        return 0;
    }
    else{
        studentMaximus = activeStudents.top();
        return activeStudents.size();
    }
}





















