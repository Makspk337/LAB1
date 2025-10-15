#include "doubly_list.h"
#include <string>
using namespace std;

Doubly_List* create_doubly_list(string name) {
    Doubly_List* list = new Doubly_List;
    list->name = name;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void dlist_push_head(Doubly_List* list, string value) {
    DNode* node = new DNode;
    node->value = value;
    node->prev = nullptr;
    node->next = list->head;
    if (list->head) list->head->prev = node;
    list->head = node;
    if (!list->tail) list->tail = node;
}

void dlist_push_tail(Doubly_List* list, string value) {
    DNode* node = new DNode;
    node->value = value;
    node->next = nullptr;
    node->prev = list->tail;
    if (list->tail) list->tail->next = node;
    list->tail = node;
    if (!list->head) list->head = node;
}

void dlist_push_before(Doubly_List* list, string before, string value) {
    DNode* cur = list->head;
    while (cur && cur->value != before) cur = cur->next;
    if (cur) {
        DNode* node = new DNode;
        node->value = value;
        node->next = cur;
        node->prev = cur->prev;
        if (cur->prev) cur->prev->next = node;
        else list->head = node;
        cur->prev = node;
    }
}

void dlist_push_after(Doubly_List* list, string after, string value) {
    DNode* cur = list->head;
    while (cur && cur->value != after) cur = cur->next;
    if (cur) {
        DNode* node = new DNode;
        node->value = value;
        node->prev = cur;
        node->next = cur->next;
        if (cur->next) cur->next->prev = node;
        else list->tail = node;
        cur->next = node;
    }
}

void dlist_delete_head(Doubly_List* list) {
    if (!list->head) return;
    DNode* tmp = list->head;
    list->head = list->head->next;
    if (list->head) list->head->prev = nullptr;
    else list->tail = nullptr;
    delete tmp;
}

void dlist_delete_tail(Doubly_List* list) {
    if (!list->tail) return;
    DNode* tmp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) list->tail->next = nullptr;
    else list->head = nullptr;
    delete tmp;
}

void dlist_delete_before(Doubly_List* list, string value) {
    DNode* cur = list->head;
    while (cur && cur->value != value) cur = cur->next;
    if (cur && cur->prev) {
        DNode* tmp = cur->prev;
        if (tmp->prev) tmp->prev->next = cur;
        else list->head = cur;
        cur->prev = tmp->prev;
        delete tmp;
    }
}

void dlist_delete_after(Doubly_List* list, string value) {
    DNode* cur = list->head;
    while (cur && cur->value != value) cur = cur->next;
    if (cur && cur->next) {
        DNode* tmp = cur->next;
        cur->next = tmp->next;
        if (tmp->next) tmp->next->prev = cur;
        else list->tail = cur;
        delete tmp;
    }
}

void dlist_delete_value(Doubly_List* list, string value) {
    DNode* cur = list->head;
    while (cur && cur->value != value) {
        cur = cur->next;
    }
    
    if (cur) {
        if (cur->prev) cur->prev->next = cur->next;
        else list->head = cur->next;
        
        if (cur->next) cur->next->prev = cur->prev;
        else list->tail = cur->prev;
        
        delete cur;
    }
}

bool dlist_find(Doubly_List* list, string value) {
    DNode* cur = list->head;
    while (cur) {
        if (cur->value == value) return true;
        cur = cur->next;
    }
    return false;
}

string dlist_read(Doubly_List* list) {
    string out = "";
    DNode* cur = list->head;
    while (cur) {
        out += cur->value;
        if (cur->next) out += " ";
        cur = cur->next;
    }
    return out;
}

string dlist_read_reverse(Doubly_List* list) {
    string out = "";
    DNode* cur = list->tail;
    while (cur) {
        out += cur->value;
        if (cur->prev) out += " ";
        cur = cur->prev;
    }
    return out;
}
