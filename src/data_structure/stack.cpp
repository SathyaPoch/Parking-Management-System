#include <Stack.h>
#include <iostream>
#include <linked_list.h>

Stack::Stack(){
    top == -1;
}

bool Stack::is_empty(){
    if(top==-1){
        return true;
    }else{
        return false;
    }
}

void Stack::push(ActionRecord action){
    if(top > 99){
        std::cout<<"Stack Overflow. Cannot save to history!\n " << std::endl;
        return;
    }
    top+=1;
    history_arr[top] = action;
    std::cout<< "History is updated" << std::endl;
}

ActionRecord Stack::pop(){
    if(is_empty){
        std::cout<<"Stack underflow\n"<<std::endl;
        return{"none"};
    }
    ActionRecord last_action = history_arr[top];
    top--;
    return last_action;
}

ActionRecord Stack::peek(){
    if(is_empty()){
        std::cout<<"Stack is empty\n"<<std::endl;
        return;
    }
    return history_arr[top];
}

