#include <iostream>
#include "data_structure/linked_list.h"
#include <fstream>
using namespace std;

// TODO: add insert function (insert at the end) using double linked list
 void DoubleLinkedList::insertAtTheEnd(const Vehicle& a3){
        Node* newNode = new Node(a3); 

        if (isEmpty()) {
            
            head = newNode;
            tail = newNode;
        } else {
          
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode; 
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
 
   
