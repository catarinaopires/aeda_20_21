/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

double Bank::getWithdraw(string cod1) const{
    double res = 0.0;
	for(size_t i = 0; i < accounts.size(); i++){
	    if(accounts[i]->getCodH() == cod1)
	        res += accounts[i]->getWithdraw();
	}
	return res;
}


vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;

    for(size_t i = 0; i < bankOfficers.size(); i++){
        if(bankOfficers[i].getName() == name){
            res = bankOfficers[i].getAccounts();
            bankOfficers.erase(bankOfficers.begin() + i);
            break;
        }
    }
    // Empty vector
    return res;
}


const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *b = new BankOfficer();
    for(size_t i = 0; i < bankOfficers.size(); i++){
        if(bankOfficers[i].getName() == name){
            bankOfficers[i].addAccount(ac);
            accounts.push_back(ac);

            *b = bankOfficers[i];
            return *b;
        }
    }
    throw NoBankOfficerException(name);
}

bool sortAccountsComp(const Account *ac1, const Account *ac2){
    if(ac1->getBalance() == ac2->getBalance()){
        return ac1->getCodIBAN() < ac2->getCodIBAN();
    }
    return ac1->getBalance() < ac2->getBalance();
}

void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), sortAccountsComp);
}

