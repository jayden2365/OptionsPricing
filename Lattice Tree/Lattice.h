#ifndef LATTICE_H
#define LATTICE_H

#include "Node.h"

class Lattice
{
public:
    Node*    root;
    
    Lattice():    root(0), nLevel(0) {};
    void setLevel(int n) { nLevel = n; }
    int getLevel() { return nLevel; }
    
    void print(Node*); // print the lattice
    
    bool check_right_bound(Node*, Node*);
    bool check_left_bound(Node*, Node*);
    void print_tab(int);
    void print_right_part(Node*);
    void print_left_part(Node*);
    void print_the_same(Node*);
    
    
private:
    int        nLevel;
    
};

#endif
