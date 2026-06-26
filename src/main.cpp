#include <iostream>
#include "data_structure/linked_list.h"
#include "data_structure/Stack.h"
#include "data_structure/queue.h"
#include "algorithm/sorting.h"
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
Vehicle history[600];
int historyCount = 0;
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
    cout<< "WELCOME TO PARKING MANAGEMENT SYSTEM\n";
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
            cout << "Enter The Vehicle Type: ";
            cin >> type;
            cout << "Enter " << type << " Plate Number(e.g. car:2E-6806, motor:1E-6806 ): ";
            cin >> plate;
            if(checkPlateValidation(plate, type)){
                if(list.available(type)==true){
                Vehicle vehicle(plate, type);
                vehicle.entryTimestamp = (long)time(0);
                vehicle.status = "parked";
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
                cout<< "Invalid plate number.";
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

                Node* curr = list.head;
                while (curr != NULL)
                {
                    if (curr->data.plateNumber == leave_plate)
                    {
                        curr->data.exitTimestamp = (long)time(0);
                        curr->data.status = "left";
                        history[historyCount] = curr->data;
                        historyCount++;
                        break;
                    }
                    curr = curr->next;
                }

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
            ActionRecord last_action = stack.peek();
            if(last_action.action_type == "Park"){
                list.deleteVehiclePlate(last_action.target_vehicle.plateNumber);
            }else if(last_action.action_type == "Checkout"){
                list.deleteVehiclePlate(last_action.target_vehicle.plateNumber);
            }else if(last_action.action_type == "Wait"){
                list.deleteVehiclePlate(last_action.target_vehicle.plateNumber);
            }else{
                cout<< " No Action To Undo\n";
            }
            stack.pop();
            list.displayList();
            cout << "Undo Action Success\n";
            cout << "----------------------\n" << endl;
            break;
        }
        case 4:{
            break;
        }
        case 5:{
            Vehicle temp[600];
            int total = 0;

            // copy checked out vehicles from history
            for (int i = 0; i < historyCount; i++)
            {
                temp[total] = history[i];
                total++;
            }

            // copy currently parked vehicles from linked list
            Node *curr = list.head;
            while (curr != NULL)
            {
                temp[total] = curr->data;
                total++;
                curr = curr->next;
            }

            if (total == 0)
            {
                cout << "No records yet." << endl;
                break;
            }

            cout << "\nSort by:\n";
            cout << "1. Entry time (earliest first)\n";
            cout << "2. Duration (longest first)\n";
            cout << "3. Status (parked or left)\n";
            cout << "Choose: ";
            int sortChoice;
            cin >> sortChoice;

            if (sortChoice == 1)
                mergeSort(temp, 0, total - 1, "entry");
            else if (sortChoice == 2)
                mergeSort(temp, 0, total - 1, "duration");
            else if (sortChoice == 3)
                mergeSort(temp, 0, total - 1, "status");
            else
            {
                cout << "Invalid choice." << endl;
                break;
            }

            displaySorted(temp, total);
            break;
        }
        case 6: {
            break;
        }
        case 7:{
            cout << "Clearing current page...\n";
            std::system("cls");
            std::system("clear");
            break;
        }
        case 8:{
            cout << "Quitting...";
            break;
        }
        case 9:{
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
