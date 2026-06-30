#ifndef SORTING_H
#define SORTING_H
#include "data_structure/linked_list.h"
#include <string>

long getDuration(const Vehicle& v);
std::string formatDuration(long minutes);
Node* mergeSortList(Node* head, const std::string& mode);
void displaySorted(Node* head, const std::string& vehicleType, const std::string& mode);

#endif