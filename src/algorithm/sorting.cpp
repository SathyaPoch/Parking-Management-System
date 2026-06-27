#include "sorting.h"
#include <iostream>
#include <ctime>
using namespace std;

long getDuration(Vehicle v) {
    long end = v.exitTimestamp;
    if (end == 0) end = (long)time(0); 
    return (end - v.entryTimestamp) / 60;
}

void mergeByEntry(Vehicle arr[], int left, int middle, int right) {
    int s1 = middle - left + 1;
    int s2 = right - middle;
    Vehicle leftPart[300], rightPart[300];

    for (int i = 0; i < s1; i++) leftPart[i] = arr[left + i];
    for (int j = 0; j < s2; j++) rightPart[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < s1 && j < s2) {
        if (leftPart[i].entryTimestamp <= rightPart[j].entryTimestamp)
            arr[k++] = leftPart[i++];
        else
            arr[k++] = rightPart[j++];
    }
    while (i < s1) arr[k++] = leftPart[i++];
    while (j < s2) arr[k++] = rightPart[j++];
}

void mergeByDuration(Vehicle arr[], int left, int middle, int right) {
    int s1 = middle - left + 1;
    int s2 = right - middle;
    Vehicle leftPart[300], rightPart[300];

    for (int i = 0; i < s1; i++) leftPart[i] = arr[left + i];
    for (int j = 0; j < s2; j++) rightPart[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < s1 && j < s2) {
        if (getDuration(leftPart[i]) >= getDuration(rightPart[j]))
            arr[k++] = leftPart[i++];
        else
            arr[k++] = rightPart[j++];
    }
    while (i < s1) arr[k++] = leftPart[i++];
    while (j < s2) arr[k++] = rightPart[j++];
}

void mergeByStatus(Vehicle arr[], int left, int middle, int right) {
    int s1 = middle - left + 1;
    int s2 = right - middle;
    Vehicle leftPart[300], rightPart[300];

    for (int i = 0; i < s1; i++) leftPart[i] = arr[left + i];
    for (int j = 0; j < s2; j++) rightPart[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < s1 && j < s2) {
        if (leftPart[i].status <= rightPart[j].status)
            arr[k++] = leftPart[i++];
        else
            arr[k++] = rightPart[j++];
    }
    while (i < s1) arr[k++] = leftPart[i++];
    while (j < s2) arr[k++] = rightPart[j++];
}

void mergeSort(Vehicle arr[], int left, int right, string mode) {
    if (left >= right) return;
    int middle = (left + right) / 2;
    mergeSort(arr, left, middle, mode);
    mergeSort(arr, middle + 1, right, mode);

    if (mode == "entry") mergeByEntry(arr, left, middle, right);
    else if (mode == "duration") mergeByDuration(arr, left, middle, right);
    else if (mode == "status") mergeByStatus(arr, left, middle, right);
}

void displaySorted(Vehicle arr[], int size) {
    cout << "\n===== SORT RESULT =====" << endl;
    for (int i = 0; i < size; i++) {
        long dur = getDuration(arr[i]);
        cout << "[" << i+1 << "] " << arr[i].plateNumber << " (" << arr[i].vehicleType << ")" << endl;
        cout << "    Status   : " << arr[i].status << endl;
        if (dur < 60)
            cout << "    Duration : " << dur << " min" << endl;
        else
            cout << "    Duration : " << dur/60 << "h " << dur%60 << "min" << endl;
        cout << endl;
    }
}