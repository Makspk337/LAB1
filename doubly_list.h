#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <string>
using namespace std;

struct DNode {
    string value;
    DNode* next;
    DNode* prev;
};

struct Doubly_List {
    string name;
    DNode* head;
    DNode* tail;
};

Doubly_List* create_doubly_list(string name);
void dlist_push_head(Doubly_List* list, string value);
void dlist_push_tail(Doubly_List* list, string value);
void dlist_push_before(Doubly_List* list, string before, string value);
void dlist_push_after(Doubly_List* list, string after, string value);
void dlist_delete_head(Doubly_List* list);
void dlist_delete_tail(Doubly_List* list);
void dlist_delete_before(Doubly_List* list, string value);
void dlist_delete_after(Doubly_List* list, string value);
void dlist_delete_value(Doubly_List* list, string value);
bool dlist_find(Doubly_List* list, string value);
string dlist_read(Doubly_List* list);
string dlist_read_reverse(Doubly_List* list);

#endif
