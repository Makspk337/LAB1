#ifndef ARRAY_H
#define ARRAY_H
#include <string>
using namespace std;

struct Array {
    string name;
    string* data;
    int size;
    int capacity;
};

Array* create_array(string name);
void array_push_back(Array* arr, string value);
void array_insert(Array* arr, int index, string value);
string array_get(Array* arr, int index);
void array_delete(Array* arr, int index);
void array_replace(Array* arr, int index, string value);
int array_length(Array* arr);
string array_read(Array* arr);

#endif

