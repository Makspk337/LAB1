#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

struct QNode {
    string data;
    QNode* next;
};

struct Queue {
    string name;
    QNode* head;
    QNode* tail;
    int size;
};

Queue* create_queue(string name);
void queue_push(Queue* q, string data);
string queue_pop(Queue* q);
string queue_peek(Queue* q);
bool queue_is_empty(Queue* q);
string queue_read(Queue* q);

#endif
