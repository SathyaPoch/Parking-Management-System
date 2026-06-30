# Parking Management System

## Overview

Parking Management System is a console-based C++ project created for the Data Structure and Algorithms course. The system is designed to manage vehicle parking records digitally instead of using manual paper records.

The program can handle vehicle check-in, check-out, searching, undo operations, waiting queues, sorting, CSV file storage, and revenue tracking. It is mainly built to demonstrate how different data structures and algorithms can work together in a real project.

## Project Information

- Course: Data Structure and Algorithms
- Project: Parking Management System
- Institution: Institute of Technology of Cambodia
- Language: C++
- Application Type: Console Application

## Team Members

- Thai Monika - p20240055
- Chheng Kimter - p20240007
- Song Phengroth - p20240046
- Poch Sathya - p20240012

## Problem Statement

Many parking places still use manual systems to record vehicle information. This can be slow, hard to update, and easy to make mistakes. During crowded times such as holidays, festivals, schools, or cafes, manual parking records can cause confusion, lost tickets, and traffic jams.

This project provides a simple digital parking management system that stores vehicle information, generates tickets, searches records, checks availability, manages waiting lines, and tracks revenue.

## Features

The system includes the following main features:

1. Get your ticket
2. Checking out
3. Undo previous action
4. Search for vehicle information
5. Check vehicle zone availability
6. Sort menu
7. Check revenue
8. Clear page
9. Quit

## Main Menu

When the program starts, the user can choose from the following menu:

```cpp
WELCOME TO PARKING MANAGEMENT SYSTEM

1. Get your ticket
2. Checking out
3. Undo previous action
4. Search for Vehicles Information
5. Check Vehicle Zone Availability
6. Sort Menu
7. Check Revenue
8. Clear Page
9. Quit
```
## CSV Data Storage

All data is structurally persisted within the `src/data/` directory using standard flat CSV layouts:

| File | Purpose |
| :--- | :--- |
| `cars.csv` | Stores currently parked cars |
| `motorbike.csv` | Stores currently parked motorbikes |
| `history.csv` | Stores vehicles that already checked out |
| `revenue.csv` | Stores total checkout count for revenue |
| `sort_meta.csv` | Stores entry timestamp metadata used for sorting |

Directory structure:
└── sathyapoch-parking-management-system/
    ├── README.md
    ├── LICENSE
    ├── run.ps1
    ├── TODO.md
    └── src/
        ├── main.cpp
        ├── algorithm/
        │   ├── hashmap.cpp
        │   ├── hashmap.h
        │   ├── sorting.cpp
        │   └── sorting.h
        ├── data/
        │   ├── cars.csv
        │   ├── history.csv
        │   ├── motorbike.csv
        │   ├── revenue.csv
        │   └── sort_meta.csv
        └── data_structure/
            ├── history.cpp
            ├── history.h
            ├── linked_list.cpp
            ├── linked_list.h
            ├── queue.cpp
            ├── queue.h
            ├── stack.cpp
            └── Stack.h

## How to Compile and Run 
## Linux / macOS 
From the project root folder, run: 
g++ -std=c++17 -Isrc \
src/main.cpp \
src/data_structure/linked_list.cpp \
src/data_structure/queue.cpp \
src/data_structure/stack.cpp \
src/data_structure/history.cpp \
src/algorithm/hashmap.cpp \
src/algorithm/sorting.cpp \
-o parking_system
 ./parking_system

## Windows PowerShell 
This project also includes run.ps1. 
To compile and run once: 
.\run.ps1

To watch for changes and automatically rebuild: 
.\run.ps1 -Watch

