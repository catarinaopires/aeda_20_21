#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    int counter = 0;
    sort(obj.begin(), obj.end());

    for(int i = 0; i < obj.size(); i++){

        if(!objects.empty()){
            if(objects.back() < obj[i]){
                objects.push(obj[i]);
                counter++;
            }
        }
        else{
            objects.push(obj[i]);
            counter++;
        }

    }
    return counter;
}

Object Warehouse::RemoveObjectQueue(int maxSize){
    Object obj("dummy", maxSize);
    bool found = false;
    vector<Object> o;

    while(!objects.empty()){
        Object temp = objects.front();

        if(!found){
            if(temp.getSize() <= maxSize){
                found = true;
                obj = temp;
                objects.pop();
                continue;
            }
        }

        o.push_back(temp);
        objects.pop();
    }

    for(int i = 0; i < o.size(); i++){
        objects.push(o[i]);
    }

     return obj;
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {

    for(int i = 0; i < boV.size(); i++){
        boxes.push(boV[i]);
    }

    return boxes.size();
}

void Warehouse::processBox(ThinTallBox& box){
    queue<Object> newObj;
    std::size_t sizeQueue = objects.size();

    while(!objects.empty()){
        if(objects.front().getSize() <= box.getCapacity() - box.getContentSize()){
            box.insert(objects.front());
            objects.pop();
            break;
        }

        newObj.push(objects.front());
        objects.pop();
    }

    while(!objects.empty()){
        newObj.push(objects.front());
        objects.pop();
    }
    objects = newObj;

    if(sizeQueue == newObj.size()){
        Object d("dummy",0);
        box.insert(d);
    }

}

vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    queue<ThinTallBox> newQueue;
   while(!boxes.empty()){
       if(boxes.front().full()){
           res.push_back(boxes.front());
           boxes.pop();
       }
       else if(boxes.front().getDays() <= 0){
           processBox(boxes.front());
           res.push_back(boxes.front());
           boxes.pop();
       }
       else{
           processBox(boxes.front());
           boxes.front().setDaysToSend(boxes.front().getDays() - 1);
           newQueue.push(boxes.front());
           boxes.pop();
       }
   }
   return res;
}

