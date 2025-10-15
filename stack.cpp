#include "stack.h"
#include <string>
using namespace std;

Stack* create_stack(string name) {
    Stack* s = new Stack;
    s->name = name;
    s->top = nullptr;
    return s;
}

void stack_push(Stack* s, string value) {
    SNode* node = new SNode;
    node->value = value;
    node->next = s->top;
    s->top = node;
}

string stack_pop(Stack* s) {
    if (!s->top) return "";
    SNode* node = s->top;
    string value = node->value;
    s->top = node->next;
    delete node;
    return value;
}

string stack_peek(Stack* s) {
    if (!s->top) return "";
    return s->top->value;
}

string stack_read(Stack* s) {
    string out = "";
    SNode* cur = s->top;
    while (cur) {
        out += cur->value;
        if (cur->next) out += " ";
        cur = cur->next;
    }
    return out;
}

