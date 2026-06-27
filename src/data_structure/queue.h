#pragma once
#include <string>
#include "linked_list.h"

 static const int SIZE = 100; 

class Queue{
private:
   Vehicle Q[SIZE];
    int front;
    int rear;

public: 
    Queue(); //constructor 
    void enqueue(Vehicle vchicle);
    Vehicle dequeue();
    Vehicle peek_front();

    bool isEmpty();
    bool isFull();
    void remove_last_veh(std::string plate);
    void displayQueue();

};