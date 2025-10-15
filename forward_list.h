#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <string>
using namespace std;

struct FNode {
    string value;
    FNode* next;
};

struct Forward_List {
    string name;
    FNode* head;
};

Forward_List* create_forward_list(string name);
void flist_push_head(Forward_List* list, string value);
void flist_push_tail(Forward_List* list, string value);
void flist_push_before(Forward_List* list, string before, string value);
void flist_push_after(Forward_List* list, string after, string value);
void flist_delete_head(Forward_List* list);
void flist_delete_tail(Forward_List* list);
void flist_delete_before(Forward_List* list, string value);
void flist_delete_after(Forward_List* list, string value);
void flist_delete_value(Forward_List* list, string value);
bool flist_find(Forward_List* list, string value);
string flist_read(Forward_List* list);
string flist_read_reverse(Forward_List* list);

#endif
