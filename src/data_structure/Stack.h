#pragma once 
#include <string>

struct ActionRecord {
    std::string action_type;
    std::string vehicle_type;
    std::string plate_num;
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