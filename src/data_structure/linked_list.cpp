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
        vehicleCount++;
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

void DoubleLinkedList::deleteEnd(){
    if(isEmpty()){
        std::cout<<"List is empty. Nothing to delete."<< std::endl;
        return;
    }
    Node* nodeToDelete = tail;
    if(head == tail){
        head = nullptr;
        tail = nullptr;
    }
    else{
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete nodeToDelete;
    vehicleCount--;
}
 
 bool DoubleLinkedList::isFull() {
    if (vehicleCount >= maxCapacity) {
        return true;
    } else {
        return false;
    }
}  
