#include <iostream>
using namespace std;
int main(){
 cout<< "WELCOME TO PARKING MANAGEMENT SYSTEM";
 int option = 0;
 int user_choice = 0;
 do{
    cout << "1. Get your ticket";
    cout << "2. Checking out";
    cout << "3. Search for Vehicles Information";
    cout << "4. Check Vehicle Zone Availability";
    cout << "5. Sort by date and durations ";
    cout << "6. Check Revenue";
    cout << "7. Clear Page "; 
    cout << "8. Quit";
    cin >> option;
    switch(option){
        case 1:
            break;
        case 2:
        cout << "Are you sure you want to check out?(y/n) ";
            switch(user_choice){
                case 'y|| Y':
                
                case 'n || N':
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
   }
}while(option !=8);
    return 0;
}

