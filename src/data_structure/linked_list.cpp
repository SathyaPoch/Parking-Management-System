#include <iostream>
#include "linked_list.h"
#include <fstream>

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

        if (a3.vehicleType == "car") 
        current_car++;
        else if (a3.vehicleType == "motorbike") 
        current_motor++;
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
        if(current == head && tail){
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
        if (current->data.vehicleType == "car") 
        current_car--;
        else if (current->data.vehicleType == "motorbike") 
        current_motor--;
        delete current;
        return true; 
    }
        current = current->next;
   }
   return false;
}
 
bool DoubleLinkedList::avaiable(std::string type) {
    if (type == "car") {
        return current_car < max_car;
    } else {
        return current_motor < max_motor;
    }
}   
