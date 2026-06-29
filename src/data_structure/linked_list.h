#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

class Vehicle {
public:
    
    std::string plateNumber;
    std::string vehicleType;
    std::string ticketID;
    std::string ticketDate;
    std::string status;
    std::string entryDateTime;
    long entryTimestamp;
    long exitTimestamp;


    Vehicle() = default;

    Vehicle(std::string num, std::string type) {
        plateNumber = num;
        vehicleType = type;
        status = "parked";
        entryTimestamp = 0;
        exitTimestamp = 0;
        entryDateTime = "";
     
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

    int max_car;
    int max_motor;
    int current_car;
    int current_motor;

public:
    DoubleLinkedList(){
        head = nullptr;
        tail = nullptr;
        max_car = 10;
        max_motor = 200;
        current_car = 0;
        current_motor = 0;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    bool deleteByID(std::string ticketID);
    bool insertAtTheEnd(const Vehicle& vehicle);
    void displayList();
    bool available(std::string type);
    bool writeIO(const Vehicle& vehicle);
    void LoadOldDataFromCSV();
    
};
#endif