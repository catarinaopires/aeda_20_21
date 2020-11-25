/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"


BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------


BankOfficer::BankOfficer(string name) {
    static unsigned int id_name = 1;
    this->id = id_name;
    id_name++;
    this->name = name;
}

bool operator>(const BankOfficer& b1, const BankOfficer& b2){
    if(b1.getAccounts().size() == b2.getAccounts().size()){
        return b1.getName() > b2.getName();
    }
    return b1.getAccounts().size() > b2.getAccounts().size();
}



