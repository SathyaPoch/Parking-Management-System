#include "sorting.h"
#include <iostream>
#include <ctime>
using namespace std;

long getDuration(Vehicle v) {
    long end = v.exitTimestamp;
    if (end == 0) end = (long)time(0); 
    return (end - v.entryTimestamp) / 60;
}

void mergeByEntry(Vehicle arr[], int l, int m, int r) {
    int s1 = m - l + 1;
    int s2 = r - m;
    Vehicle left[300], right[300];

    for (int i = 0; i < s1; i++) left[i] = arr[l + i];
    for (int j = 0; j < s2; j++) right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < s1 && j < s2) {
        if (left[i].entryTimestamp <= right[j].entryTimestamp)
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < s1) arr[k++] = left[i++];
    while (j < s2) arr[k++] = right[j++];
}

void mergeByDuration(Vehicle arr[], int l, int m, int r) {
    int s1 = m - l + 1;
    int s2 = r - m;
    Vehicle left[300], right[300];

    for (int i = 0; i < s1; i++) left[i] = arr[l + i];
    for (int j = 0; j < s2; j++) right[j] = arr[m + 1 + j];

   
    int i = 0, j = 0, k = l;
    while (i < s1 && j < s2) {
        if (getDuration(left[i]) >= getDuration(right[j]))
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < s1) arr[k++] = left[i++];
    while (j < s2) arr[k++] = right[j++];
}

void mergeByStatus(Vehicle arr[], int l, int m, int r) {
    int s1 = m - l + 1;
    int s2 = r - m;
    Vehicle left[300], right[300];

    for (int i = 0; i < s1; i++) left[i] = arr[l + i];
    for (int j = 0; j < s2; j++) right[j] = arr[m + 1 + j];

    
    int i = 0, j = 0, k = l;
    while (i < s1 && j < s2) {
        if (left[i].status <= right[j].status)
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < s1) arr[k++] = left[i++];
    while (j < s2) arr[k++] = right[j++];
}

void mergeSort(Vehicle arr[], int l, int r, string mode) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m, mode);
    mergeSort(arr, m + 1, r, mode);

    if (mode == "entry") mergeByEntry(arr, l, m, r);
    else if (mode == "duration") mergeByDuration(arr, l, m, r);
    else if (mode == "status") mergeByStatus(arr, l, m, r);
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