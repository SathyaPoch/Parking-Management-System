#pragma once 
#include <string>
#include "linked_list.h"

struct ActionRecord {
    std::string action_type;
    Vehicle target_vehicle;
};

class Stack{
    private: 
    ActionRecord history_arr[100];
    int top;

    public: 
    Stack(); //Constructor
    void push(ActionRecord action); // push everything inside the struct 
    ActionRecord pop(); //remove 3 varibles 
    ActionRecord peek(); //show 3 varibles
    bool is_empty();
    bool is_full();
};