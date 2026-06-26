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
        writeIO(a3);
      
}
        


void DoubleLinkedList::displayList() {
    Node* node = head;
    while (node != NULL) {
        //std::cout << "TickeyID: "<< node->data.ticketID <<"\t ||| \t " << "Vehicle Type: "<< node->data.vehicleType <<"\t ||| \t " << "Plate Number: "<<node->data.plateNumber<<std::endl;
        std::cout << "Plate Number: " << node->data.plateNumber << std::endl;
        std::cout << "Ticket : " << node->data.ticketID << std::endl;
        std::cout << "Vehicle Type: " << node->data.vehicleType << std::endl;
     
        node = node->next;
    }
}

bool DoubleLinkedList::deleteByID(std::string leaveID){
    if(isEmpty()){
        std::cout<<"List is empty. Nothing to delete."<< std::endl;
        return false;
    }
    Node* current = head;
   while(current != NULL){
    if(current->data.ticketID == leaveID){
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

Vehicle* DoubleLinkedList::findByID(std::string ticketID) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.ticketID == ticketID) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

bool DoubleLinkedList::available(std::string type){
    if(type == "car"){
        if(current_car<max_car){
            return true;
        }else{
            return false;
        }
    }
    if(type == "motor"){
        if(current_motor < max_motor){
            return true;
        }else{
            return false;
        }
    }
    return false; 
}
bool DoubleLinkedList::writeIO(const Vehicle& vehicle) {
    std::ofstream csv;
    if (vehicle.vehicleType == "car")
        csv.open("src/data/cars.csv", std::ios::app);
    else if (vehicle.vehicleType == "motor")
        csv.open("src/data/motorbike.csv", std::ios::app);
    else
        return false;

    if (!csv.is_open()) return false;

    csv << vehicle.plateNumber << ','
        << vehicle.ticketID << ','
        << vehicle.vehicleType << '\n';
    return true;
    
}
