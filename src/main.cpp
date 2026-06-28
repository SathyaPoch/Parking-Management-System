#include <iostream>
#include "data_structure/linked_list.h"
#include "data_structure/Stack.h"
#include "data_structure/queue.h"
#include "algorithm/hashmap.h"
#include "algorithm/sorting.h"
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <time.h>
#include <cctype>
#include <cstdlib>
using namespace std;
bool available(string type);
bool checkPlateValidation(string plate, string type);
bool writeIO(string vehicleType);
bool deleteAfterUndo(string vehicleType, string ticketID);
int ReadOldDataFromCSV(string csv, string oldId, int& vehicleCount);
string TicketID(string type, int& carIdTracker, int& bikeIdTracker);
string getCurrentDateTime();
int carIdTracker = 0;
int bikeIdTracker = 0;
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
 carIdTracker = ReadOldDataFromCSV("src/data/cars.csv", "TC", list.current_car);
 bikeIdTracker = ReadOldDataFromCSV("src/data/motorbike.csv", "TB", list.current_motor);
 Stack stack;
 Queue car_queue;   // NEW: Separate line for cars
 Queue bike_queue;
 HashMap plateMap;
 HashMap ticketMap;
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
                vehicle.ticketID = TicketID(type,carIdTracker, bikeIdTracker);
                vehicle.entryTimestamp = time(0);
                vehicle.entryDateTime = getCurrentDateTime();
                vehicle.exitTimestamp = 0;
                cout << "Vehicle ticket ID: " << vehicle.ticketID << endl;
                if (list.insertAtTheEnd(vehicle)) {
                    list.writeIO(vehicle);
                }
                plateMap.insert(vehicle.plateNumber, vehicle.ticketID);
                ticketMap.insert(vehicle.ticketID, vehicle.plateNumber);
                // list.writeIO(a3.vehicleType);
                list.displayList();
                cout << "\n--- TICKET PRINTED ---\n";
                cout<< "========================================\n";
                cout << " Ticket ID : " << vehicle.ticketID << "\n";
                cout << " Type      : " << vehicle.vehicleType << "\n";
                cout << " Plate     : " << vehicle.plateNumber << "\n";
                cout << " Entry Time: " << vehicle.entryDateTime << "\n";
                cout<< "========================================\n";
                cout << "----------------------\n" << endl;
                ActionRecord log;
                log.action_type = "Park";
                log.target_vehicle = vehicle;
                stack.push(log);
                }else{
                cout << "\n Reminder: The "<< type << " parking zone is full.\n";
                Vehicle waiting_vehicle(plate, type);
                if(type == "car"){
                    car_queue.enqueue(waiting_vehicle);
                }else if(type == "motor"){
                    bike_queue.enqueue(waiting_vehicle);
                }
                cout<<type<<": "<<plate<<" has been added to the waiting line\n";
                
                ActionRecord log;
                log.action_type = "Wait";
                log.target_vehicle = waiting_vehicle;
                stack.push(log);
                cout<<"Do you want to view the Waitline? (y/n): ";
                cin>>user_choice;
                if(user_choice == 'y' || user_choice == 'Y'){
                    car_queue.displayQueue();
                    bike_queue.displayQueue();
                }
                else{
                    break;
                }
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
                string ticketID;
                string plateNumber; 
                cout << "Enter the TicketID of the vehicle (e.g. TC1, TB2): ";
                cin >> ticketID;
                cout << "Enter the plate number of the vehicle: ";
                cin >> plateNumber;

                string plateStored = ticketMap.search(ticketID);
                string ticketIDStored = plateMap.search(plateNumber);

                if (ticketID == ticketIDStored && plateNumber == plateStored) {
                    cout << "Checked out successfully" << endl;
                    plateMap.remove(plateNumber);
                    ticketMap.remove(ticketID);
                    list.deleteByID(ticketID);

                    ActionRecord log;
                    log.action_type = "Checkout";
                    log.target_vehicle.ticketID = ticketID;
                    log.target_vehicle.plateNumber = plateNumber;
                    stack.push(log);
                } else if (ticketID != ticketIDStored || plateNumber != plateStored) {
                    cout << "Invalid ticket ID or plate number" << endl;
                } else {
                    cout << "Something went wrong." << endl;
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
            if(action == "Park"){
                list.deleteByID(v.ticketID);
                plateMap.remove(v.plateNumber);
                ticketMap.remove(v.ticketID);
                deleteAfterUndo(v.vehicleType, v.ticketID);
                cout << "Deleted: " << v.plateNumber << " from the parking lot" << endl;
            }
            else if(action =="Checkout"){
                list.insertAtTheEnd(v);
                list.writeIO(v);
                plateMap.insert(v.plateNumber, v.ticketID);
                ticketMap.insert(v.ticketID, v.plateNumber);
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
            do {
                cout << "Would you like to search by plate number or ticket ID? (p/t): ";
                cin >> user_choice;
                if (user_choice == 'p' || user_choice == 'P') {
                    string plate;
                    cout << "Enter the plate number of the vehicle: ";
                    cin >> plate;
                    cout << endl;
                    if (plateMap.search(plate) == "") {
                        cout << "Plate Number: " << plate << " not found." << endl;
                        break;
                    } else if (plateMap.search(plate) != "") {
                        cout << "Plate Number: " << plate << " belong to Ticket ID: " << plateMap.search(plate) << "" << endl;
                    }
                } else if (user_choice == 't' || user_choice == 'T'){
                    string ticketID;
                    cout << "Enter the TicketID of the vehicle (e.g. TC1, TB2): ";
                    cin >> ticketID;
                    cout << endl;
                    if (ticketMap.search(ticketID) == "") {
                        cout << "Ticket ID: " << ticketID << " not found." << endl;
                        break;
                    } else if (ticketMap.search(ticketID) != "") {
                        cout << "Ticket ID: " << ticketID << " belong to Plate Number: " << ticketMap.search(ticketID) << "" << endl;
                    }
                } else {
                    cout << "Invalid choice, please enter 'p' or 't'." << endl;
                }
            } while (user_choice != 'p' && user_choice != 'P' && user_choice != 't' && user_choice != 'T');
            break;
        }
        case 5:{
             cout<<"---------------- Check Vehicle Zone Availability ----------------\n";
            cout<<"~~~~~~~~ CAR ZONE ~~~~~~~~~\n";
            cout<<"Current Car: "<<list.current_car<< " ||| The Maximum Car: " <<list.max_car<<endl;
            //display the car.csv
            cout<<endl;
            cout<<"~~~~~~~~ MOTOR ZONE ~~~~~~~~~\n";
            cout<<"Current Motor: "<<list.current_motor<< " ||| The Maximum Motor: " <<list.max_motor<<endl;
            //display the motorbike.csv
            cout<<endl;

            break;
        }
        case 6: {
            cout<<"---------------- Sort by Date and Duration ----------------\n";
            Vehicle temp[600];
            int total = 0;

            
            // for (int i = 0; i < historyCount; i++)
            // {
            //     temp[total] = history[i];
            //     total++;
            // }

            
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
        case 7:{
            break;
        }
        case 8:{
            cout<<"--------------------------------------------------\n";
            cout << "Clearing current page...\n";
            std::system("cls");
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


string TicketID(string type, int& carIdTracker, int& bikeIdTracker) {
    if (type == "car") {
        carIdTracker = carIdTracker + 1;
        return "TC" + to_string(carIdTracker);
    } 
    else if (type == "motor") {
        bikeIdTracker = bikeIdTracker + 1;
        return "TB" + to_string(bikeIdTracker);
    }

    return 0;
}
int ReadOldDataFromCSV(string csv, string oldId, int& vehicleCount) {
    ifstream file(csv);
    string header;
    int countOldId = 0;
    vehicleCount = 0;

    getline(file, header);

    while (getline(file, header)) {
        if (header.empty()) continue;
        stringstream ss(header);

        string plateNumber;
        string ticketID;
        string vehicleType;

        getline(ss, plateNumber, ',');
        getline(ss, ticketID, ',');
        getline(ss, vehicleType, ',');

        if (plateNumber.empty() || ticketID.empty()) continue;
        vehicleCount++; // count every valid vehicle row 
        
        if (ticketID.length() > oldId.length()) {
            if (ticketID.find(oldId) == 0) {
                
                string checkId = ticketID.substr(oldId.length());
                int num = stoi(checkId);
                if (num > countOldId) {
                    countOldId = num;
                }
            }
        }
    }

    return countOldId;
}
//delete from csv after stack undo
bool deleteAfterUndo(string vehicleType, string ticketID) {
    string csv;

    if (vehicleType == "car") {
        csv = "src/data/cars.csv";
    } 
    else if (vehicleType == "motor") {
        csv = "src/data/motorbike.csv";
    } 
    else {
        cout << " Invalid!";
        return false;
    }

    ifstream file(csv);
    if (!file.is_open()) {
        return false;
    }

    string fileBuffer = ""; 
    string header;
    bool deleted = false;

    if (getline(file, header)) {
        fileBuffer += header + '\n';
    }

  
    while (getline(file, header)) {
        stringstream ss(header);

        string plateNumber;
        string currentTicketID;
        string type;

        getline(ss, plateNumber, ',');
        getline(ss, currentTicketID, ',');
        getline(ss, type, ',');

        if (currentTicketID == ticketID) {
            deleted = true;
            continue;
        }

        fileBuffer += header + '\n';
    }

    file.close();

    ofstream outFile(csv); 
    if (!outFile.is_open()) {
        return false;
    }

    outFile << fileBuffer;
    
    outFile.close();

    return true;
}
string getCurrentDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char buffer[30];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return string(buffer);
}