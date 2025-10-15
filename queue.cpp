#include "queue.h"
#include <string>
using namespace std;

Queue* create_queue(string name) {
    Queue* q = new Queue;
    q->name = name;
    q->head = nullptr;
    q->tail = nullptr;
    q->size = 0;
    return q;
}

void queue_push(Queue* q, string data) {
    QNode* node = new QNode;
    node->data = data;
    node->next = nullptr;
    if (!q->head) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
    q->size++;
}

string queue_pop(Queue* q) {
    if (!q->head) return "";
    QNode* tmp = q->head;
    string data = tmp->data;
    q->head = q->head->next;
    if (!q->head) q->tail = nullptr;
    delete tmp;
    q->size--;
    return data;
}

string queue_peek(Queue* q) {
    if (!q->head) return "";
    return q->head->data;
}

bool queue_is_empty(Queue* q) {
    return q->size == 0;
}

string queue_read(Queue* q) {
    string out = "";
    QNode* cur = q->head;
    while (cur) {
        out += cur->data;
        if (cur->next) out += " ";
        cur = cur->next;
    }
    return out;
}
