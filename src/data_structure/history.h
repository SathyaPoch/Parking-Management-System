#ifndef HISTORY_H
#define HISTORY_H
#include "data_structure/linked_list.h" 
#include <string>

class HistoryLinkedList {
public:
    Node* head;
    Node* tail;

    HistoryLinkedList();
    bool isEmpty() const;
    void insertAtTheEnd(const Vehicle& vehicle);
    void appendToCSV(const Vehicle& vehicle);
    void loadFromCSV();
};

void saveEntryMeta(const Vehicle& vehicle);
void removeEntryMeta(const std::string& ticketID);
void loadEntryMeta(DoubleLinkedList& list);

#endif