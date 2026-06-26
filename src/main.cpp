#include <iostream>
#include "data_structure/linked_list.h"
#include "data_structure/Stack.h"
#include "data_structure/queue.h"
#include <string>
#include <ctime>
#include <time.h>
#include <cctype>
#include <cstdlib>
using namespace std;
bool available(string type);
bool checkPlateValidation(string plate, string type);
int Vehicle::carIdTracker = 0;
int Vehicle::bikeIdTracker = 0;
bool writeIO(string vehicleType);
class Ticket {
public:
    int ticketID;
    Vehicle vehicle;
    string entryTime;
    string exitTime;
    char parkingZone;
    double fee;
 
    Ticket(int id, Vehicle a1, string arrivalTime, string leaveTime, char zone, double feeCharge) {
       
        ticketID = id;
        vehicle = a1;
        entryTime = arrivalTime;
        exitTime = leaveTime;
        parkingZone = zone;
        fee = feeCharge;
    }  
    
  
};

// time_t rawtime;
//   struct tm * timeinfo;

//   time (&rawtime);
//   timeinfo = localtime (&rawtime);
//   printf ("Current local time and date: %s", asctime(timeinfo));
class ParkingZone {
public:
    int id;
    string zoneLocation;
    int spots;
    int full;
};
int main(){
 DoubleLinkedList list;
 Stack stack;
 Queue car_queue;   // NEW: Separate line for cars
 Queue bike_queue;
 int option = 0;
 char user_choice = 'n';
 int parking_zone = 0;

 do{
    cout<< "\nWELCOME TO PARKING MANAGEMENT SYSTEM\n";
    cout << "\n1. Get your ticket\n";
    cout << "2. Checking out\n";
    cout << "3. Undo previous action \n";
    cout << "4. Search for Vehicles Information\n";
    cout << "5. Check Vehicle Zone Availability\n";
    cout << "6. Sort by date and durations\n";
    cout << "7. Check Revenue\n";
    cout << "8. Clear Page\n"; 
    cout << "9. Quit\n";
    cout << "Enter your option : ";
    cin >> option;
    switch(option){
        case 1:{
            string plate, type;
            park:
            cout << "Enter The Vehicle Type: ";
            cin >> type;
            if(type == "car"){
                cout<<"Enter Car Plate Number(e.g. 2E-6806): ";
                cin>>plate;
            }else if(type == "motor"){
                cout<<"Enter Motor Plate Number(e.g. 1E-6806): ";
                cin>>plate;
            }
            if(checkPlateValidation(plate, type)){
                if(list.available(type)==true){
                Vehicle vehicle(plate, type);
                cout << "Vehicle ticket ID: " << vehicle.ticketID << endl;
                list.insertAtTheEnd(vehicle);
                list.displayList();
                cout << "\n--- TICKET PRINTED ---\n";
                cout<< "========================================\n";
                cout << " Ticket ID : " << vehicle.ticketID << "\n";
                cout << " Type      : " << vehicle.vehicleType << "\n";
                cout << " Plate     : " << vehicle.plateNumber << "\n";
                cout<< "========================================\n";
                cout << "----------------------\n" << endl;
                ActionRecord log;
                log.action_type = "Park";
                log.target_vehicle = vehicle;
                stack.push(log);
                }else{
                cout << "\n Reminder: The "<< type << "parking zone is full.\n";
                Vehicle waiting_vehicle(plate, type);
                if(type == "car"){
                    car_queue.enqueue(waiting_vehicle);
                }else if(type == "motor" || "motorbike"){
                    bike_queue.enqueue(waiting_vehicle);
                }
                ActionRecord log;
                cout<<type<<": "<<plate<<" has been added to the waiting line\n";
                log.action_type = "Wait";
                log.target_vehicle = waiting_vehicle;
                stack.push(log);
                }
            }else{
                cout<< "Invalid plate number. Please enter the checking information again\n";
                goto park;
            }
            break;
        }
        case 2: {
            cout << "Are you sure you want to check out? (y/n): ";
            cin >> user_choice;
            if (user_choice == 'y' || user_choice == 'Y') {
                string leave_plate, leave_type;
                cout << "Enter the type leaving vehicle: ";
                cin >> leave_type;
                cout << "Enter the plate number of the vehicle: ";
                cin >> leave_plate;

                bool found = list.deleteVehiclePlate(leave_plate);
                if(found == true){
                    cout << "\nVehicle " << leave_plate << " checked out successfully.\n";

                    ActionRecord checkout;
                    checkout.action_type = "Checkout";
                    Vehicle leaving(leave_plate, leave_type);
                    checkout.target_vehicle = leaving;
                    stack.push(checkout);
                }else{
                    cout << "The Vehicle is not found!!!" << endl;
                }
            } else {
                cout << "Cancelled Choice!";
            }
            break;
        }
        case 3:{    
            cout<<"-------- Undo Previous Action ---------\n";
            if(stack.is_empty()){
                cout<<"History is empty\n";
                cout<<"~~~~~~~~~~~~~~~~~~~~~~\n";
                break;
            }

            ActionRecord Undo = stack.pop();
            string action = Undo.action_type;
            Vehicle v = Undo.target_vehicle;

            if(action =="Park"){
                list.deleteVehiclePlate(v.plateNumber);
                cout << "Deleted:" << v.plateNumber<< "from the parking lot"<< endl;
            }
            else if(action =="Checkout"){
                list.insertAtTheEnd(v);
                cout << "Restored:" << v.plateNumber<< "to the parking lot"<< endl;
            }
            else if(action =="Wait"){
                if(v.vehicleType == "car"){
                    car_queue.enqueue(v);
                }else if(v.vehicleType == "motor"){
                    bike_queue.enqueue(v);
                }
                cout << "Restored:" << v.plateNumber<< "to the waiting line"<< endl;
            }
            cout<<"----------------------------\n";
            break;
        }
        case 4:{
            cout<<"--------------- Search for Vehicles Information ----------------\n";
            break;
        }
        case 5:{
            cout<<"---------------- Check Vehicle Zone Availability ----------------\n";
            break;
        }
        case 6: {
            cout<<"---------------- Sort by Date and Duration ----------------\n";
            break;
        }
        case 7:{
            cout << "Clearing current page...\n";
            std::system("cls");
            std::system("clear");
            break;
        }
        case 8:{
            cout<<"--------------------------------------------------\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Successfully cleared page"<<endl;
            cout<<"--------------------------------------------------\n";
            break;
        }
        case 9:{
            cout<<"Quitting...";
            break;
        }
        default:{
            cout << "Invalid Option";
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    }
}while(option !=9);
    return 0;
}

void displayTicketInfo() {
    cout << "";
}
bool checkPlateValidation(string plate, string type) { 
    if (plate.length() != 7) {
        return false;
    }
    
    if (plate[2] != '-') {
        return false;
    }
    
    if (!isalpha(static_cast<unsigned char>(plate[1]))) {
        return false; 
    }
    
    if (!isdigit(static_cast<unsigned char>(plate[0]))) {
        return false;
    }

    if (type == "car" && plate[0] != '2') {
        return false;
    }

    if (type == "motor" && plate[0] != '1') {
        return false;
    }

    for (int i = 3; i <= 6; i++) {
        if (!isdigit(static_cast<unsigned char>(plate[i]))) {
            return false;
        }
    }

    return true; 
}
