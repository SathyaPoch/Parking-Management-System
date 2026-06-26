#include <iostream>
#include "linked_list.h"
#include <fstream>
#include <iostream>
// TODO: add insert function (insert at the end) using double linked list
 void DoubleLinkedList::insertAtTheEnd(const Vehicle& a3){
        Node* node = new Node(a3); 

        if (isEmpty()) {
            
            head = node;
            tail = node;
        } else {
          
            tail->next = node;
            node->prev = tail;
            tail = node; 
        }
        //add the capacity
        if (a3.vehicleType == "car") {
            current_car++;
        } else if (a3.vehicleType == "motor") {
            current_motor++;
        }
        writeIO(a3.vehicleType);
}

void DoubleLinkedList::displayList() {
    Node* node = head;
    while (node != NULL) {
        std::cout << "Plate Number: " << node->data.plateNumber << std::endl;
        std::cout << "Ticket : " << node->data.ticketID << std::endl;
        std::cout << "Vehicle Type: " << node->data.vehicleType << std::endl;
     
        node = node->next;
    }
}

bool DoubleLinkedList::deleteVehiclePlate( std:: string leave_plate){
    if(isEmpty()){
        std::cout<<"List is empty. Nothing to delete."<< std::endl;
        return false;
    }
    //TODO : traverse the list to look for the liscense plate to delete
    Node* current = head;
   while(current != NULL){
    if(current->data.plateNumber == leave_plate){
        if(current == head && current == tail){
            head = NULL;
            tail = NULL;
        }else if (current == head){
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
        }else if (current == tail){
            tail = tail->prev;
            tail->next = NULL;
        }else{
            //if it's in the middle of the list
             current->prev->next = current->next;
             current->next->prev = current->prev;
        }
        //remove the capacity 
        if (current->data.vehicleType == "car") {
                current_car--;
            } else if (current->data.vehicleType == "motor") {
                current_motor--;
            }

        delete current;
        return true; 
    }
        current = current->next;
   }
   return false;
}

bool DoubleLinkedList::available(std::string type){
    if(type == "car"){
        if(current_car<max_car){
            return true;
        }else{
            return false;
        }
    }
    if(type == "motor" || "motorbike" || "moto"){
        if(current_motor < max_motor){
            return true;
        }else{
            return false;
        }
    }
    return false; 
}
bool DoubleLinkedList::writeIO(std::string vehicleType) {
    std::ofstream csv;
    if(vehicleType == "car"){
        csv.open("src/data/cars.csv")std::endl;
    } else if (vehicleType == "motor"){
        csv.open("src/data/motorbike.csv")std::endl;
    } else {
        std::cout << "Invalid";
        return false;
    }

    csv << "plateNumber,ticketID,vehicleType\n";
    Node* current = head;
    while(current != NULL) {
        if(current->data.vehicleType == vehicleType) {
            csv << current->data.plateNumber << ','
                << current->data.ticketID << ','
                << current->data.vehicleType << '\n';
            csv.close();
        }
        current = current->next;
    }
    
    return true;
}
