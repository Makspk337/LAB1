#include "forward_list.h"
#include <string>
using namespace std;

Forward_List* create_forward_list(string name) {
    Forward_List* list = new Forward_List;
    list->name = name;
    list->head = nullptr;
    return list;
}

void flist_push_head(Forward_List* list, string value) {
    FNode* node = new FNode;
    node->value = value;
    node->next = list->head;
    list->head = node;
}

void flist_push_tail(Forward_List* list, string value) {
    FNode* node = new FNode;
    node->value = value;
    node->next = nullptr;
    if (!list->head) {
        list->head = node;
        return;
    }
    FNode* cur = list->head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

void flist_push_before(Forward_List* list, string before, string value) {
    if (!list->head) return;
    if (list->head->value == before) {
        flist_push_head(list, value);
        return;
    }
    FNode* cur = list->head;
    while (cur->next && cur->next->value != before) cur = cur->next;
    if (cur->next) {
        FNode* node = new FNode;
        node->value = value;
        node->next = cur->next;
        cur->next = node;
    }
}

void flist_push_after(Forward_List* list, string after, string value) {
    FNode* cur = list->head;
    while (cur && cur->value != after) cur = cur->next;
    if (cur) {
        FNode* node = new FNode;
        node->value = value;
        node->next = cur->next;
        cur->next = node;
    }
}

void flist_delete_head(Forward_List* list) {
    if (!list->head) return;
    FNode* tmp = list->head;
    list->head = list->head->next;
    delete tmp;
}

void flist_delete_tail(Forward_List* list) {
    if (!list->head) return;
    if (!list->head->next) {
        delete list->head;
        list->head = nullptr;
        return;
    }
    FNode* cur = list->head;
    while (cur->next->next) cur = cur->next;
    delete cur->next;
    cur->next = nullptr;
}

void flist_delete_before(Forward_List* list, string value) {
    if (!list->head || list->head->value == value) return;
    if (list->head->next && list->head->next->value == value) {
        flist_delete_head(list);
        return;
    }
    FNode* prev = list->head;
    FNode* cur = list->head->next;
    while (cur->next && cur->next->value != value) {
        prev = cur;
        cur = cur->next;
    }
    if (cur->next) {
        prev->next = cur->next;
        delete cur;
    }
}

void flist_delete_after(Forward_List* list, string value) {
    FNode* cur = list->head;
    while (cur && cur->value != value) cur = cur->next;
    if (cur && cur->next) {
        FNode* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
    }
}

void flist_delete_value(Forward_List* list, string value) {
    if (!list->head) return;
    
    if (list->head->value == value) {
        flist_delete_head(list);
        return;
    }
    
    FNode* prev = list->head;
    FNode* cur = list->head->next;
    
    while (cur && cur->value != value) {
        prev = cur;
        cur = cur->next;
    }
    
    if (cur) {
        prev->next = cur->next;
        delete cur;
    }
}

bool flist_find(Forward_List* list, string value) {
    FNode* cur = list->head;
    while (cur) {
        if (cur->value == value) return true;
        cur = cur->next;
    }
    return false;
}

string flist_read(Forward_List* list) {
    string out = "";
    FNode* cur = list->head;
    while (cur) {
        out += cur->value;
        if (cur->next) out += " ";
        cur = cur->next;
    }
    return out;
}

string flist_read_reverse(Forward_List* list) {
    if (!list->head) return "";
    int len = 0;
    FNode* cur = list->head;
    while (cur) {
        len++;
        cur = cur->next;
    }

    string* arr = new string[len];
    cur = list->head;
    int i = 0;
    while (cur) {
        arr[i++] = cur->value;
        cur = cur->next;
    }

    string out = "";
    for (int j = len - 1; j >= 0; j--) {
        out += arr[j];
        if (j > 0) out += " ";
    }

    delete[] arr;
    return out;
}
