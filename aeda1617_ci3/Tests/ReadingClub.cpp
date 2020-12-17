/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// Part I   - BST
//

void ReadingClub::generateCatalog() {
    bool done = false;

	for(int i = 0; i < books.size(); i++){
        BookCatalogItem b(books[i]->getTitle(), books[i]->getAuthor(), books[i]->getYear());

        BSTItrIn<BookCatalogItem> it(catalogItems);

        while(!it.isAtEnd()){
            if(it.retrieve() == b){
                it.retrieve().addItems(books[i]);
                done = true;
                break;
            }
            it.advance();
        }

        if(!done){
            b.addItems(books[i]);
            catalogItems.insert(b);
        }
        done = false;
	}

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
    BookCatalogItem c(book->getTitle(), book->getAuthor(), book->getYear());
    BSTItrIn<BookCatalogItem> it(catalogItems);

    while(!it.isAtEnd()){
        if(it.retrieve() == c){
            for (auto b: it.retrieve().getItems()){
                if(b->getReader() == NULL){
                    temp.push_back(b);
                }
            }
        }
        it.advance();
    }

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
    BookCatalogItem c(book->getTitle(), book->getAuthor(), book->getYear());
    BSTItrIn<BookCatalogItem> it(catalogItems);

    while(!it.isAtEnd()){
        if(it.retrieve() == c){
            for (auto b: it.retrieve().getItems()){
                if(b->getReader() == NULL){
                    b->setReader(reader);
                    reader->addReading(book->getTitle(), book->getAuthor());
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

void ReadingClub::addUserRecord(User* user) {
    userRecords.insert(UserRecord(user));
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	for(auto u: userRecords){
	    if(u.getEMail() == user->getEMail()){
	        u.setEMail(newEMail);
            return;
	    }
	}

}


//
// Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for(int i = 0; i < candidates.size(); i++){
	    int nr = candidates[i].getReadings().size();
        if(candidates[i].getReading().first != "" && candidates[i].getReading().second != ""){
            nr++;
        }
	    if(nr >= min){
            readerCandidates.push(candidates[i]);
	    }
	}

}

int ReadingClub::awardReaderChampion(User& champion) {
    priority_queue<User> temp = readerCandidates;

    if(!temp.empty()){
        User champ = temp.top();
        int nr = champ.getReadings().size();
        if(champ.getReading().first != "" && champ.getReading().second != ""){
            nr++;
        }
        temp.pop();

        if(!temp.empty()){
            int nrNext = temp.top().getReadings().size();
            if(temp.top().getReading().first != "" && temp.top().getReading().second != ""){
              nrNext++;
            }
            if(nr > nrNext){
               champion = champ;
               return readerCandidates.size();
            }
            else{
                return 0;
            }
        }
        champion = champ;
        return readerCandidates.size();
    }
    else
        return 0;

}
























