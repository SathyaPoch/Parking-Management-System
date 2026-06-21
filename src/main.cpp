#include <iostream>
#include "data_structure/linked_list.h"
#include "data_structure/Stack.h"
#include "data_structure/queue.h"
#include <string>
#include <ctime>
#include <time.h>
#include <cctype>
using namespace std;

int Vehicle::carIdTracker = 0;
int Vehicle::bikeIdTracker = 0;

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
 int option = 0;
 int user_choice = 0;
 int parking_zone = 0;
 DoubleLinkedList list;
 Stack stack;
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
            cout << "Enter " << type << " Plate Number: ";
            cin >> plate;
           // if( ){ //if the spot avaiable 
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
            //}else{}
            cout << "\n Reminder: The "<< type << "parking zone is full.\n";
            Vehicle waiting_vehicle(plate, type);
            cout<<"Vechile"<<plate<<" has been added to the waiting line\n";
            log.action_type = "Wait";
            log.target_vehicle = waiting_vehicle;
            stack.push(log);
            break;
        }
        case 2:
        cout << "Are you sure you want to check out?(y/n) ";
            switch(user_choice){
                case 'y':
                cout<< "Not implemented yet.";
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
