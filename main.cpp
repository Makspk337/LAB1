#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array.h"
#include "forward_list.h"
#include "doubly_list.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
using namespace std;

struct Entry {
    string type;
    void* ptr;
    string name;
};

Entry entries[100];
int entryCount = 0;

Entry* find_entry(string name) {
    for (int i = 0; i < entryCount; i++) {
        if (entries[i].name == name) return &entries[i];
    }
    return nullptr;
}

void save_to_file(string filename) {
    ofstream f(filename);
    for (int i = 0; i < entryCount; i++) {
        Entry e = entries[i];
        if (e.type == "ARRAY") f << "ARRAY " << ((Array*)e.ptr)->name << " " << array_read((Array*)e.ptr) << endl;
        else if (e.type == "FLIST") f << "FLIST " << ((Forward_List*)e.ptr)->name << " " << flist_read((Forward_List*)e.ptr) << endl;
        else if (e.type == "DLIST") f << "DLIST " << ((Doubly_List*)e.ptr)->name << " " << dlist_read((Doubly_List*)e.ptr) << endl;
        else if (e.type == "STACK") f << "STACK " << ((Stack*)e.ptr)->name << " " << stack_read((Stack*)e.ptr) << endl;
        else if (e.type == "QUEUE") f << "QUEUE " << ((Queue*)e.ptr)->name << " " << queue_read((Queue*)e.ptr) << endl;
        else if (e.type == "TREE") f << "TREE " << ((Tree*)e.ptr)->name << " " << tree_read((Tree*)e.ptr) << endl;
    }
    f.close();
}

void load_from_file(string filename) {
    ifstream f(filename);
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        stringstream ss(line);
        string type, name, val;
        ss >> type >> name;
        if (type == "ARRAY") {
            Array* a = create_array(name);
            while (ss >> val) array_push_back(a, val);
            entries[entryCount++] = {"ARRAY", a, name};
        } else if (type == "FLIST") {
            Forward_List* l = create_forward_list(name);
            while (ss >> val) flist_push_tail(l, val);
            entries[entryCount++] = {"FLIST", l, name};
        } else if (type == "DLIST") {
            Doubly_List* l = create_doubly_list(name);
            while (ss >> val) dlist_push_tail(l, val);
            entries[entryCount++] = {"DLIST", l, name};
        } else if (type == "STACK") {
            Stack* s = create_stack(name);
            while (ss >> val) stack_push(s, val);
            entries[entryCount++] = {"STACK", s, name};
        } else if (type == "QUEUE") {
            Queue* q = create_queue(name);
            while (ss >> val) queue_push(q, val);
            entries[entryCount++] = {"QUEUE", q, name};
        } else if (type == "TREE") {
            Tree* t = create_tree(name);
            while (ss >> val) {
                int int_val = stoi(val);
                tree_insert(t, int_val);
            }
            entries[entryCount++] = {"TREE", t, name};
        }
    }
    f.close();
}

int main(int argc, char* argv[]) {
    string filename, query;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }
    if (filename.empty() || query.empty()) return 0;

    load_from_file(filename);

    stringstream ss(query);
    string cmd, name, val, target;
    int index;

    ss >> cmd;

    if (cmd == "MPUSH") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (!e) {
            Array* a = create_array(name);
            array_push_back(a, val);
            entries[entryCount++] = {"ARRAY", a, name};
        } else array_push_back((Array*)e->ptr, val);
    } else if (cmd == "MSET") {
        ss >> name >> index >> val;
        Entry* e = find_entry(name);
        if (e) array_insert((Array*)e->ptr, index, val);
    } else if (cmd == "MREPLACE") {
        ss >> name >> index >> val;
        Entry* e = find_entry(name);
        if (e) array_replace((Array*)e->ptr, index, val);
    } else if (cmd == "MGET") {
        ss >> name >> index;
        Entry* e = find_entry(name);
        if (e) cout << array_get((Array*)e->ptr, index) << endl;
    } else if (cmd == "MDEL") {
        ss >> name >> index;
        Entry* e = find_entry(name);
        if (e) array_delete((Array*)e->ptr, index);
    } else if (cmd == "MLEN") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << array_length((Array*)e->ptr) << endl;
    } else if (cmd.substr(0, 5) == "FPUSH") {
        ss >> name;
        Entry* e = find_entry(name);
        if (!e) {
            Forward_List* l = create_forward_list(name);
            entries[entryCount++] = {"FLIST", l, name};
            e = find_entry(name);
        }
        if (cmd == "FPUSH_HEAD") ss >> val, flist_push_head((Forward_List*)e->ptr, val);
        else if (cmd == "FPUSH_TAIL") ss >> val, flist_push_tail((Forward_List*)e->ptr, val);
        else if (cmd == "FPUSH_BEFORE") ss >> target >> val, flist_push_before((Forward_List*)e->ptr, target, val);
        else if (cmd == "FPUSH_AFTER") ss >> target >> val, flist_push_after((Forward_List*)e->ptr, target, val);
    } else if (cmd.substr(0, 4) == "FDEL") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) {
            if (cmd == "FDEL_HEAD") flist_delete_head((Forward_List*)e->ptr);
            else if (cmd == "FDEL_TAIL") flist_delete_tail((Forward_List*)e->ptr);
            else if (cmd == "FDEL_BEFORE") ss >> target, flist_delete_before((Forward_List*)e->ptr, target);
            else if (cmd == "FDEL_AFTER") ss >> target, flist_delete_after((Forward_List*)e->ptr, target);
            else if (cmd == "FDEL_VALUE") ss >> target, flist_delete_value((Forward_List*)e->ptr, target);
        }
    } else if (cmd == "FFIND") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (e && flist_find((Forward_List*)e->ptr, val)) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    } else if (cmd == "FGET") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << flist_read((Forward_List*)e->ptr) << endl;
    } else if (cmd == "FGETR") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << flist_read_reverse((Forward_List*)e->ptr) << endl;
    } else if (cmd.substr(0, 5) == "LPUSH") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (!e) {
            Doubly_List* l = create_doubly_list(name);
            entries[entryCount++] = {"DLIST", l, name};
            e = find_entry(name);
        }
        if (cmd == "LPUSH_HEAD") dlist_push_head((Doubly_List*)e->ptr, val);
        else if (cmd == "LPUSH_TAIL") dlist_push_tail((Doubly_List*)e->ptr, val);
    } else if (cmd.substr(0, 4) == "LDEL") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) {
            if (cmd == "LDEL_HEAD") dlist_delete_head((Doubly_List*)e->ptr);
            else if (cmd == "LDEL_TAIL") dlist_delete_tail((Doubly_List*)e->ptr);
            else if (cmd == "LDEL_VALUE") ss >> target, dlist_delete_value((Doubly_List*)e->ptr, target);
        }
    } else if (cmd == "LFIND") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (e && dlist_find((Doubly_List*)e->ptr, val)) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    } else if (cmd == "LGET") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << dlist_read((Doubly_List*)e->ptr) << endl;
    } else if (cmd == "LGETR") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << dlist_read_reverse((Doubly_List*)e->ptr) << endl;
    } else if (cmd == "SPUSH") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (!e) {
            Stack* s = create_stack(name);
            stack_push(s, val);
            entries[entryCount++] = {"STACK", s, name};
        } else stack_push((Stack*)e->ptr, val);
    } else if (cmd == "SPOP") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << stack_pop((Stack*)e->ptr) << endl;
    } else if (cmd == "SPEEK") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << stack_peek((Stack*)e->ptr) << endl;
    } else if (cmd == "QPUSH") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (!e) {
            Queue* q = create_queue(name);
            queue_push(q, val);
            entries[entryCount++] = {"QUEUE", q, name};
        } else queue_push((Queue*)e->ptr, val);
    } else if (cmd == "QPOP") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << queue_pop((Queue*)e->ptr) << endl;
    } else if (cmd == "QPEEK") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << queue_peek((Queue*)e->ptr) << endl;
    } else if (cmd == "TINSERT") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (!e) {
            Tree* t = create_tree(name);
            int int_val = stoi(val);
            tree_insert(t, int_val);
            entries[entryCount++] = {"TREE", t, name};
        } else {
            int int_val = stoi(val);
            tree_insert((Tree*)e->ptr, int_val);
        }
    } else if (cmd == "TISMEMBER") {
        ss >> name >> val;
        Entry* e = find_entry(name);
        if (e) {
            int int_val = stoi(val);
            if (tree_find((Tree*)e->ptr, int_val)) cout << "TRUE" << endl;
            else cout << "FALSE" << endl;
        } else cout << "FALSE" << endl;
    } else if (cmd == "TCHECKFULL") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e && tree_is_full((Tree*)e->ptr)) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    } else if (cmd == "TGET") {
        ss >> name;
        Entry* e = find_entry(name);
        if (e) cout << tree_read((Tree*)e->ptr) << endl;
    } else if (cmd == "PRINT") {
        ss >> name;
        Entry* e = find_entry(name);
        if (!e) return 0;
        if (e->type == "ARRAY") cout << array_read((Array*)e->ptr) << endl;
        else if (e->type == "FLIST") cout << flist_read((Forward_List*)e->ptr) << endl;
        else if (e->type == "DLIST") cout << dlist_read((Doubly_List*)e->ptr) << endl;
        else if (e->type == "STACK") cout << stack_read((Stack*)e->ptr) << endl;
        else if (e->type == "QUEUE") cout << queue_read((Queue*)e->ptr) << endl;
        else if (e->type == "TREE") cout << tree_read((Tree*)e->ptr) << endl;
    }

    save_to_file(filename);
    return 0;
}
