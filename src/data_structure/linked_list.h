#ifndef LINKEDLIST_H
#define LINKEDLIST_H
struct Node {
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr) {}
};
#endif