#ifndef STACK_H
#define STACK_H
#include <string>
using namespace std;

struct SNode {
    string value;
    SNode* next;
};

struct Stack {
    string name;
    SNode* top;
};

Stack* create_stack(string name);
void stack_push(Stack* s, string value);
string stack_pop(Stack* s);
string stack_peek(Stack* s);
string stack_read(Stack* s);

#endif

