#include "queue.h"
#include "iostream"

Queue::Queue(){
    front = -1;
    rear = -1;
}

bool Queue::isEmpty(){
    if(front == -1){
        return true;
    }else{
        return false;
    }
}

bool Queue::isFull(){
    if((rear + 1) % SIZE == front){
        return true;
    }else{
        return false;
    }
}

void Queue::enqueue(Vehicle vehicle){
    if(isFull()){
        std::cout<<"Warning: The waiting line is full" <<std::endl;
        return;
    }
    if(isEmpty()){
        front = 0;
        rear = 0;
    }else{
        rear = (rear + 1) % SIZE;
    }
    Q[rear] = vehicle;
    std::cout << "Vehicle" << vehicle.plateNumber << "joinded the waiting line." <<std::endl;
}

Vehicle Queue::dequeue(){
    if(isEmpty()){ //check queue
        std::cout<<"The Waiting line is empty"<< std::endl;
        Vehicle empty_vehcile("none","none");
        return empty_vehcile;
    }
    Vehicle leave = Q[front]; // //store value

    if(front == rear){
        front = rear = -1;
    }else{
        front = (front + 1) % SIZE;
    }
    return leave;
}

Vehicle Queue::peek_front(){
 if(!isEmpty()){
     return Q[front];
 }
 return Vehicle("none","none");
}

void Queue::displayQueue(){
    if(isEmpty()){
        std::cout<<"The Waiting line is empty for  "<<Q[front].vehicleType<<" \n";
        return;    
    }
    std::cout<<"The Waiting Line for "<< Q[front].vehicleType <<": \n";
    for(int i = front; i <= rear; i = (i + 1) % SIZE){
        std::cout<<i+1<<". "<<"Plate Number: "<<Q[i].plateNumber<<std::endl;
    }
    std::cout<<"=======================================\n";
}