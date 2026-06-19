#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

class Vehicle {
public:
    string plateNumber;
    string vehicleType;
    string ticketID;
    string ticketDate;

    static int carIdTracker;
    static int bikeIdTracker;

    Vehicle() = default;

    Vehicle(string num, string type) {
        plateNumber = num;
        vehicleType = type;
        if (type == "car") {
            carIdTracker++;
            ticketID = "TC" + to_string(carIdTracker);
        } else if (type == "motorbike") {
            bikeIdTracker++;
            ticketID = "TB" + to_string(bikeIdTracker); 
        } else {
            cout << "Invalid! Only accept car and motorbike" << endl;
        }
    }
};

struct Node {
    Vehicle data;
    Node* next;
    Node* prev;

    Node(const Vehicle& val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoubleLinkedList {
public:
    Node* head;
    Node* tail;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    bool isEmpty() const {
        return head == nullptr;
    }

    void insertAtTheEnd(const Vehicle& a3);
    void displayList();
};
#endif