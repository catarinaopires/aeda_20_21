#include "packagingMachine.h"
#include <sstream>
#include <string>
#include <algorithm>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    int counter = 0;
	for(int i = 0; i < objs.size(); i++){
	    if(objs[i].getWeight() <= boxCapacity){
            counter++;
            objects.push(objs[i]);
            objs.erase(objs.begin() + i);
            i--;
	    }
	}
	return counter;
}

// TODO: CORRIGIR -> NÃO SE PODE CRIAR BOX INICIAL (BOX(0))
Box PackagingMachine::searchBox(Object& obj) {
	HeapBox temp;

	while(!boxes.empty()){
	    if(boxes.top().getFree() >= obj.getWeight()){
	        Box b = boxes.top();
	        boxes.pop();

	        while(!boxes.empty()){
                temp.push(boxes.top());
                boxes.pop();
	        }

            while(!temp.empty()){
                boxes.push(temp.top());
                temp.pop();
            }

	        return b;
	    }
	    else{
	        temp.push(boxes.top());
	    }
        boxes.pop();
	}

	while(!temp.empty()){
	    boxes.push(temp.top());
	    temp.pop();
	}

	return Box(boxCapacity);
}

unsigned PackagingMachine::packObjects() {
	while(!objects.empty()){
	    Object obj = objects.top();
        objects.pop();
        Box b = searchBox(obj);
        b.addObject(obj);
        boxes.push(b);
	}
	return boxes.size();
}

string PackagingMachine::printObjectsNotPacked() const {
    string str;
    if(!objects.size())
        str = "No objects!\n";
    else{
        HeapObj temp = objects;
        while(!temp.empty()){
            stringstream ss;
            ss << temp.top() << endl;
            str += ss.str();
            temp.pop();
        }
    }
	return str;
}

// Correct code
Box PackagingMachine::boxWithMoreObjects() const {
	if(boxes.empty())
	    throw MachineWithoutBoxes();
	else{
        HeapBox temp = boxes;
        Box b = temp.top();
        temp.pop();

        while(!temp.empty()){
            if(temp.top().getSize() > b.getSize()){
                b = temp.top();
            }
            temp.pop();
        }
        return b;
	}
}