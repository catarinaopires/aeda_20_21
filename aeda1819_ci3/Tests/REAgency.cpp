#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// Part I   - BST
//
void REAgency::generateCatalog() {
    bool done = false;
	for(int i = 0; i < properties.size(); i++){
	    PropertyTypeItem p(properties[i]->getAddress(), properties[i]->getPostalCode(), properties[i]->getTypology(), properties[i]->getPrice());
	    p.addItems(properties[i]);
	    BSTItrIn<PropertyTypeItem> it(catalogItems);

	    while(!it.isAtEnd()){
	        if(it.retrieve() == p){

	            PropertyTypeItem temp = it.retrieve();
	            catalogItems.remove(it.retrieve());
	            temp.addItems(properties[i]);
	            catalogItems.insert(temp);
	            done = true;
	            break;

	        }
	        it.advance();
	    }
	    if(!done){
            catalogItems.insert(p);
	    }
        done = false;
	}
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	PropertyTypeItem p(property->getAddress(), property->getPostalCode(), property->getTypology(), property->getPrice());
	while(!it.isAtEnd()){
	    if(it.retrieve() == p){
	        vector<Property*> items = it.retrieve().getItems();
	        for(int i = 0; i < items.size(); i++){
	            if(get<0>(items[i]->getReservation()) == NULL){
	                temp.push_back(items[i]);
	            }
	        }
	    }
	    it.advance();
	}

	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    BSTItrIn<PropertyTypeItem> it(catalogItems);
    PropertyTypeItem p(property->getAddress(), property->getPostalCode(), property->getTypology(), property->getPrice());
    while(!it.isAtEnd()){
        if(it.retrieve() == p){
            vector<Property*> items = it.retrieve().getItems();
            for(int i = 0; i < items.size(); i++){
                if(get<0>(items[i]->getReservation()) == NULL){
                    items[i]->setReservation(make_tuple(client, items[i]->getPrice() - (percentage* items[i]->getPrice())/100));
                    client->addVisiting(property->getAddress(), property->getPostalCode(), property->getTypology(), to_string(property->getPrice()));
                    return true;
                }
            }
        }
        it.advance();
    }

	return false;
}

//
// Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
    listingRecords.insert(ClientRecord(client));

}

void REAgency::deleteClients() {
	auto it = listingRecords.begin();

	while(it != listingRecords.end()){
	    if(it->getClientPointer()->getVisitedProperties().size() == 0){
	        it = listingRecords.erase(it);
	    }
	    else
	        it++;
	}
}

//
// Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    for(int i = 0; i < candidates.size(); i++){
        float ratio = 0;

        for(int j = 0; j < properties.size(); j++){
            if(get<0>(properties[j]->getReservation())->getEMail() == candidates[i].getEMail()){
                ratio++;
            }
        }
        ratio /= candidates[i].getVisitedProperties().size();

        if(ratio > min){
            clientProfiles.push(candidates[i]);
        }
    }

}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
    priority_queue<Client> temp = clientProfiles;

    while(!temp.empty()){
        if(temp.top().getVisiting() == tuple<string, string, string, string>()) continue;
        else {
            int cod = stoi(get<1>(temp.top().getVisiting()));
            Property* toAdd;
            int min = 9999999;
            for(auto p: properties){
                int diff = abs(stoi(p->getPostalCode())-cod);
                if(diff != 0 && diff < min && get<0>(p->getReservation()) == NULL){
                    min = diff;
                    toAdd = p;
                }
            }
            tempProperties.push_back(toAdd);
        }
        temp.pop();
    }
	return tempProperties;
}
