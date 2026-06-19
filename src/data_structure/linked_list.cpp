#include <iostream>
#include "data_structure/linked_list.h"
#include <fstream>
using namespace std;

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
}

void DoubleLinkedList::displayList() {
    Node* node = head;
    while (node != NULL) {
        cout << "Plate Number: " << node->data.plateNumber << std::endl;
        cout << "Ticket : " << node->data.ticketID << endl;
        cout << "Vehicle Type: " << node->data.vehicleType << endl;
     
        node = node->next;
    }
}
 
   
