#include "array.h"
#include <string>
using namespace std;

Array* create_array(string name) {
    Array* arr = new Array;
    arr->name = name;
    arr->size = 0;
    arr->capacity = 4;
    arr->data = new string[arr->capacity];
    return arr;
}

void array_push_back(Array* arr, string value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        string* newData = new string[arr->capacity];
        for (int i = 0; i < arr->size; i++) newData[i] = arr->data[i];
        delete[] arr->data;
        arr->data = newData;
    }
    arr->data[arr->size++] = value;
}

void array_insert(Array* arr, int index, string value) {
    if (index < 0 || index > arr->size) return;
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        string* newData = new string[arr->capacity];
        for (int i = 0; i < arr->size; i++) newData[i] = arr->data[i];
        delete[] arr->data;
        arr->data = newData;
    }
    for (int i = arr->size; i > index; i--) arr->data[i] = arr->data[i - 1];
    arr->data[index] = value;
    arr->size++;
}

string array_get(Array* arr, int index) {
    if (index < 0 || index >= arr->size) return "";
    return arr->data[index];
}

void array_delete(Array* arr, int index) {
    if (index < 0 || index >= arr->size) return;
    for (int i = index; i < arr->size - 1; i++) arr->data[i] = arr->data[i + 1];
    arr->size--;
}

void array_replace(Array* arr, int index, string value) {
    if (index < 0 || index >= arr->size) return;
    arr->data[index] = value;
}

int array_length(Array* arr) {
    return arr->size;
}

string array_read(Array* arr) {
    string out = "";
    for (int i = 0; i < arr->size; i++) {
        out += arr->data[i];
        if (i != arr->size - 1) out += " ";
    }
    return out;
}

