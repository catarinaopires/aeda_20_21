
#include "Hospital.h"

#include <algorithm>
#include <stack>
#include <iostream>



Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
    doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
    return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
    letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
    return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{

    unsigned counter = 0;
    for(auto d: doctors ){
        if(d.getMedicalSpecialty() == medicalSpecialty){
            counter += d.getPatients().size();
        }
    }
    return counter;

}

bool compareDoctors(const Doctor &d1, const Doctor &d2) {
    if (d1.getPatients().size() == d2.getPatients().size()){
        if(d1.getMedicalSpecialty() == d2.getMedicalSpecialty()){
            return d1.getCode() < d2.getCode();
        }
        return d1.getMedicalSpecialty() < d2.getMedicalSpecialty();
    }
    return d1.getPatients().size() < d2.getPatients().size();

}

void Hospital::sortDoctors() {
    doctors.sort(compareDoctors);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
    int counter = 0;

    for(auto doc: doctors){
        if(doc.getMedicalSpecialty() == medicalSpecialty1)
            counter++;
    }
    if(counter < 3){
        Doctor d(codM1, medicalSpecialty1);
        doctors.push_back(d);
        return true;
    }
    else{
        return false;
    }


}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {

    for(auto doc: doctors){
        if(doc.getCode() == codM1){
            queue<Patient> p = doc.getPatients();
            doctors.remove(doc);
            return p;
        }
    }

    throw DoctorInexistent();

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
    bool exists = false;
    int minPacient = doctors.begin()->getPatients().size();
    unsigned code;

    for(auto doc:doctors){
        if(doc.getMedicalSpecialty() == medicalSpecialty1){
            exists = true;

            if(doc.getPatients().size() <= minPacient){
                code = doc.getCode();
                minPacient = doc.getPatients().size();
            }
        }
    }

    if(exists){
        for(auto it = doctors.begin(); it != doctors.end(); it++){
           if((*it).getCode() == code){
               Patient p(cod1, medicalSpecialty1);
               (*it).addPatient(p);
               return true;
            }
        }
    }
    return false;
}



void Hospital::processPatient(unsigned codM1) {

   for(auto it = doctors.begin(); it != doctors.end(); it++){
       if((*it).getCode() == codM1){
           if((*it).getPatients().empty())
               return;

           Patient p = (*it).getPatients().front();
           (*it).removeNextPatient();

           for(auto it2 = letterTray.begin(); it2 != letterTray.end(); it2++){
               if((*it2).size() < trayCapacity){
                   (*it2).push(p);
                   return;
               }
           }

           stack<Patient> t;
           t.push(p);
           letterTray.push_back(t);
           return;

       }
   }
}


unsigned Hospital::removePatients(unsigned codP1) {

    unsigned counter=0;

    for(auto it2 = letterTray.begin(); it2 != letterTray.end(); it2++){
        if((*it2).top().getCode() == codP1){
            (*it2).pop();
            counter++;
        }
        if((*it2).empty()){
            it2 = --letterTray.erase(it2);
        }
    }
    return counter;
}
