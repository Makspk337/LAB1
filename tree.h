#ifndef TREE_H
#define TREE_H
#include <string>
using namespace std;

struct TNode {
    int value;
    TNode* left;
    TNode* right;
};

struct Tree {
    string name;
    TNode* root;
};

Tree* create_tree(string name);
void tree_insert(Tree* t, int value);
bool tree_find(Tree* t, int value);
string tree_read(Tree* t);
bool tree_is_full(Tree* t);

#endif
