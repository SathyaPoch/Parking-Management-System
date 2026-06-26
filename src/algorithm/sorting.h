#ifndef SORTING_H
#define SORTING_H

#include "../data_structure/linked_list.h"
#include <string>
#include <ctime>
using namespace std;

long getDuration(Vehicle v);
void mergeSort(Vehicle arr[], int left, int right, string mode);
void displaySorted(Vehicle arr[], int size);

#endif