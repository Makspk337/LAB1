#include "tree.h"
#include <string>
#include <sstream>
using namespace std;

Tree* create_tree(string name) {
    Tree* t = new Tree;
    t->name = name;
    t->root = nullptr;
    return t;
}

void tree_insert(Tree* t, int value) {
    TNode** current = &t->root;
    while (*current) {
        if (value < (*current)->value) {
            current = &(*current)->left;
        } else if (value > (*current)->value) {
            current = &(*current)->right;
        } else {
            return;
        }
    }
    *current = new TNode{value, nullptr, nullptr};
}

bool tree_find(Tree* t, int value) {
    TNode* current = t->root;
    while (current) {
        if (value == current->value) {
            return true;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

string tree_read(Tree* t) {
    if (!t->root) return "";
    
    string out = "";
    TNode* queue[100];
    int front = 0, rear = 0;
    
    queue[rear++] = t->root;
    
    while (front < rear) {
        TNode* cur = queue[front++];
        out += to_string(cur->value);
        
        bool has_more_elements = (front < rear) || cur->left || cur->right;
        if (has_more_elements) {
            out += " ";
        }
        
        if (cur->left) queue[rear++] = cur->left;
        if (cur->right) queue[rear++] = cur->right;
    }
    
    return out;
}

bool tree_is_full(Tree* t) {
    if (!t->root) return true;
    
    TNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = t->root;
    
    while (front < rear) {
        TNode* cur = queue[front++];
        
        if ((cur->left && !cur->right) || (!cur->left && cur->right)) {
            return false;
        }
        
        if (cur->left) queue[rear++] = cur->left;
        if (cur->right) queue[rear++] = cur->right;
    }
    
    return true;
}
