#include "sorting.h"
#include <iostream>
#include <ctime>

using namespace std;

long getDuration(const Vehicle& v) {
    if (v.entryTimestamp <= 0) {
        return 0;
    }

    long end = v.exitTimestamp;
    if (end <= 0) {
        end = (long)time(0);
    }

    return (end - v.entryTimestamp) / 60;
}

string formatDuration(long minutes) {
    if (minutes < 0) minutes = 0;

    long days = minutes / (60 * 24);
    long hours = (minutes % (60 * 24)) / 60;
    long mins = minutes % 60;

    string result = "";
    if (days > 0) {
        result += to_string(days) + "d " + to_string(hours) + "h " + to_string(mins) + "min";
    } else if (hours > 0) {
        result += to_string(hours) + "h " + to_string(mins) + "min";
    } else {
        result += to_string(mins) + "min";
    }
    return result;
}

bool comesBefore(Node* a, Node* b, const string& mode) {
    if (mode == "entry") {
        // latest entry time appears first
        return a->data.entryTimestamp >= b->data.entryTimestamp; 
    } else if (mode == "duration") {
        // longest duration appears first
        return getDuration(a->data) >= getDuration(b->data); 
    } else if (mode == "status") {
        // "parking" vehicles appear before "left" vehicles
        if (a->data.status == b->data.status) return true;
        return (a->data.status == "parking");
    }
    return false;
}

void splitList(Node* source, Node** front, Node** back) {
    if (source == nullptr || source->next == nullptr) {
        *front = source;
        *back = nullptr;
        return;
    }
    Node* slow = source;
    Node* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = nullptr;   
}

Node* merge(Node* a, Node* b, const string& mode) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Node* result = nullptr;
    if (comesBefore(a, b, mode)) {
        result = a;
        result->next = merge(a->next, b, mode);
        if (result->next) result->next->prev = result;
    } else {
        result = b;
        result->next = merge(a, b->next, mode);
        if (result->next) result->next->prev = result;
    }
    result->prev = nullptr;   
    return result;
}

Node* mergeSortList(Node* head, const string& mode) {
    if (head == nullptr || head->next == nullptr) return head;

    Node* front = nullptr;
    Node* back = nullptr;
    splitList(head, &front, &back);

    front = mergeSortList(front, mode);
    back = mergeSortList(back, mode);

    Node* sorted = merge(front, back, mode);

    Node* cur = sorted;
    Node* prevNode = nullptr;
    while (cur != nullptr) {
        cur->prev = prevNode;
        prevNode = cur;
        cur = cur->next;
    }
    return sorted;
}

void displaySorted(Node* head, const string& vehicleType, const string& mode) {
    cout << "\n===== SORT RESULT";
    if (vehicleType != "all") cout << " [" << vehicleType << "]";
    cout << " =====" << endl;

    int idx = 1;
    Node* cur = head;
    while (cur != nullptr) {
        bool typeMatch = (vehicleType == "all" || cur->data.vehicleType == vehicleType);
        // entry/duration modes only make sense for vehicles still parking
        bool statusMatch = (mode == "status") || (cur->data.status == "parking");

        if (typeMatch && statusMatch) {
            cout << "[" << idx++ << "] " << cur->data.plateNumber 
                 << " (" << cur->data.vehicleType << ")" << endl;

            if (mode == "status") {
                cout << " Status : " << cur->data.status << endl;
            }

            long dur = getDuration(cur->data);
            cout << " Duration : " << formatDuration(dur) << endl;
            cout << endl;
        }
        cur = cur->next;
    }
    if (idx == 1) {
        cout << " (No records found matching this type)" << endl;
    }
}