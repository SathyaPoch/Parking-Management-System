#include <iostream>
#include <string>
#include <cctype>
using namespace std;
#include "data_structure/Stack.h"
#include "hashmap.h"

//logic:
//hash function: (ascii sum + num sum) * 31 % TABLE_SIZE
//table size: 101
//collision: chaining
//insert when check in
//remove when check out
//search when check out and search for vehicle

HashMap::HashMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

int HashMap::hashFunction(string key) {
    int num_sum = 0;
    int ascii_sum = 0;

    for (char c : key) {
        ascii_sum += static_cast<int>(c);
    }

    for (int j = 0; j < key.length(); j++) {
        if (isdigit(key[j])) {
            num_sum = (num_sum*10 + (key[j] - '0')) % TABLE_SIZE; //make sure 001 and 010 won't end up in the same bucket and module for shorter string
        }
    }

    return ((ascii_sum + num_sum) * 31) % TABLE_SIZE; 
}

void HashMap::insert(string key, string value) {
    int index = hashFunction(key);
    HashEntry* newNode = new HashEntry();
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
}

string HashMap::search(string key) {
    int index = hashFunction(key);
    HashEntry* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return "";
}

void HashMap::remove(string key) {
    int index = hashFunction(key);
    HashEntry* current = table[index];
    HashEntry* prev = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

HashMap::~HashMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashEntry* current = table[i];
        while (current != nullptr) {
            HashEntry* temp = current;
            current = current->next;
            delete temp;
        }
    }
}