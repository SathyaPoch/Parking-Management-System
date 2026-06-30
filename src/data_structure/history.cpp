#include "history.h"
#include <iostream>
#include <fstream>
#include <sstream>

HistoryLinkedList::HistoryLinkedList() {
    head = nullptr;
    tail = nullptr;
}

bool HistoryLinkedList::isEmpty() const {
    return head == nullptr;
}

void HistoryLinkedList::insertAtTheEnd(const Vehicle& vehicle) {
    Node* node = new Node(vehicle);
    if (isEmpty()) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void HistoryLinkedList::appendToCSV(const Vehicle& vehicle) {
    std::ofstream csv("src/data/history.csv", std::ios::app);
    if (!csv.is_open()) return;

    csv << vehicle.plateNumber << ","
        << vehicle.ticketID << ","
        << vehicle.vehicleType << ","
        << vehicle.entryTimestamp << ","
        << vehicle.exitTimestamp << ","
        << vehicle.entryDateTime << ","
        << vehicle.status << "\n";
    csv.close();
}

void HistoryLinkedList::loadFromCSV() {
    std::ifstream file("src/data/history.csv");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string plate, id, type, entryTsStr, exitTsStr, entryTime, status;

        std::getline(ss, plate, ',');
        std::getline(ss, id, ',');
        std::getline(ss, type, ',');
        std::getline(ss, entryTsStr, ',');
        std::getline(ss, exitTsStr, ',');
        std::getline(ss, entryTime, ',');
        std::getline(ss, status, ',');

        if (plate.empty() || id.empty()) continue;

        Vehicle v(plate, type);
        v.ticketID = id;
        v.entryDateTime = entryTime;
        v.status = status;
        
        try {
            v.entryTimestamp = entryTsStr.empty() ? 0 : std::stol(entryTsStr);
            v.exitTimestamp = exitTsStr.empty() ? 0 : std::stol(exitTsStr);
        } catch (...) {
            v.entryTimestamp = 0;
            v.exitTimestamp = 0;
        }

        insertAtTheEnd(v);
    }
    file.close();
}


static const char* SORT_META_PATH = "src/data/sort_meta.csv";

void saveEntryMeta(const Vehicle& vehicle) {
    std::ofstream csv(SORT_META_PATH, std::ios::app);
    if (!csv.is_open()) return;
    csv << vehicle.ticketID << ","
        << vehicle.entryTimestamp << ","
        << vehicle.entryDateTime << "\n";
    csv.close();
}

void removeEntryMeta(const std::string& ticketID) {
    std::ifstream in(SORT_META_PATH);
    if (!in.is_open()) return; 

    std::string buffer, line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tid;
        std::getline(ss, tid, ',');
        if (tid != ticketID) {
            buffer += line + "\n";
        }
    }
    in.close();

    std::ofstream out(SORT_META_PATH);
    if (!out.is_open()) return;
    out << buffer;
    out.close();
}

void loadEntryMeta(DoubleLinkedList& list) {
    std::ifstream file(SORT_META_PATH);
    if (!file.is_open()) return; 

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string ticketID, tsStr, dateTime;

        std::getline(ss, ticketID, ',');
        std::getline(ss, tsStr, ',');
        std::getline(ss, dateTime, ',');

        if (ticketID.empty()) continue;

        long ts = 0;
        try {
            ts = tsStr.empty() ? 0 : std::stol(tsStr);
        } catch (...) {
            ts = 0;
        }

        Node* cur = list.head;
        while (cur != nullptr) {
            if (cur->data.ticketID == ticketID) {
                cur->data.entryTimestamp = ts;
                cur->data.entryDateTime = dateTime;
                break;
            }
            cur = cur->next;
        }
    }
    file.close();
}