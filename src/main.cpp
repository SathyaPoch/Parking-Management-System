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
 cout<< "WELCOME TO PARKING MANAGEMENT SYSTEM\n";
 DoubleLinkedList list;
 Stack stack;
 Queue car_queue;   // NEW: Separate line for cars
 Queue bike_queue;
 int option = 0;
 int user_choice = 0;
 int parking_zone = 0;

 do{
    cout << "1. Get your ticket\n";
    cout << "2. Checking out\n";
    cout << "3. Search for Vehicles Information\n";
    cout << "4. Check Vehicle Zone Availability\n";
    cout << "5. Sort by date and durations\n";
    cout << "6. Check Revenue\n";
    cout << "7. Clear Page\n"; 
    cout << "8. Quit\n";
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
                cout << "Vehicle ticket ID: " << vehicle.ticketID << endl;
                list.insertAtTheEnd(vehicle);
                 if( type == "car" || "Car" ){
                        list.writeIO("cars.csv");
                    }else if (type == "motorbike" || "Motorbike"){
                        list.writeIO("cars.csv");
                    }else{
                        std::cout<< "Invalid!";
                    }
                list.displayList();
                cout << "\n--- TICKET PRINTED ---\n";
                cout<< "==============================)==========\n";
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
                }else if(type == "motor"){
                    bike_queue.enqueue(waiting_vehicle);
                }
                ActionRecord log;
                cout<<type<<": "<<plate<<" has been added to the waiting line\n";
                log.action_type = "Wait";
                log.target_vehicle = waiting_vehicle;
                stack.push(log);
                break;
                }
            }else{
                cout<< "Invalid plate number.";
            }
        }
        case 2:
        cout << "Are you sure you want to check out?(y/n) ";
            switch(user_choice){
                case 'y':{
                string leave_plate, leave_type;
                cout<<"Enter the type leaving vehicle:";
                cin>>leave_type;
                cout<<"Enter the plate number of the vehicle:";
                cin>>leave_plate;

                bool found = list.deleteVehiclePlate(leave_plate);
                if(found == true){
                    cout << "\nVehicle " << leave_plate << " checked out successfully.\n";

                    //record the action
                    ActionRecord checkout;
                    checkout.action_type="Checkout";
                    Vehicle leaving(leave_plate, leave_type);
                    checkout.target_vehicle= leaving;
                    stack.push(checkout);

                    // 
                    
                }else{
                    cout<<"The Vehcile is not found!!!"<<endl;
                }
                }
                case 'n':
                cout<<"Cancelled Choice!";
                break;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;   
        case 7:
        cout << "Clearing current page...";
         std::system("cls");
            break;
        case 8:
            cout << "Quitting...";
            break;    
        default :
            cout << "Invalid Option";
            break;    
   }
}while(option !=8);
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

    if ((type == "motor" || type == "motorbike") && plate[0] != '1') {
        return false;
    }

    for (int i = 3; i <= 6; i++) {
        if (!isdigit(static_cast<unsigned char>(plate[i]))) {
            return false;
        }
    }

    return true; 
}
