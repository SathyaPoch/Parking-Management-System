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
    

    static int carIdTracker;
    static int bikeIdTracker;

    Vehicle() = default;

    Vehicle(std::string num, std::string type) {
        plateNumber = num;
        vehicleType = type;
        if (type == "car") {
            carIdTracker++;
            ticketID = "TC" + std::to_string(carIdTracker);
        } else if (type == "motorbike") {
            bikeIdTracker++;
            ticketID = "TB" + std::to_string(bikeIdTracker); 
        } else {
            std::cout << "Invalid! Only accept car and motorbike" << std::endl;
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

    int max_car;
    int max_motor;
    int current_car;
    int current_motor;

public:
    DoubleLinkedList(){
        head = nullptr;
        tail = nullptr;
        max_car = 100;
        max_motor = 200;
        current_car = 0;
        current_motor = 0;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    bool deleteVehiclePlate(std::string leave_plate);
    void insertAtTheEnd(const Vehicle& a3);
    void displayList();
    bool available(std::string type);
    bool writeIO(std::string vehicleType);
    
};
#endif