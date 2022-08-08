#include "Lattice.h"
#include <iostream>

using namespace std;

bool Lattice::check_right_bound(Node*real, Node*test){
    
    if(test->level == 0)
    {
        if(test == real)
        {
            return true;
        }
        else
            return false;
    }
    
    if(real->parent != 0 && test->level != 0)
    {
        if(test != real)
        {
            return check_right_bound(real, test->rightChild);
        }
        else
            return true;
    }
    
    if(real->parent == 0)
    {
        return false;
    }
    
    return false;
    
}

bool Lattice::check_left_bound(Node*real, Node*test){
    
    if(test->level == 0)
    {
        if(test == real)
        {
            return true;
        }
        else
            return false;
    }
    
    if(real->parent != 0 && test->level != 0)
    {
        if(test != real)
        {
            return check_left_bound(real, test->leftChild);
        }
        else
            return true;
    }
    
    if(real->parent == 0)
    {
        return false;
    }
    
    return false;
    
}

////print tab loop (chech bound change for loop)
void Lattice::print_tab(int level)
{
    if(level - nLevel == 0)
    {
        return;
    }
    if(nLevel - level > 0)
    {
        cout << "\t";
        print_tab(level + 1);
        return;
    }
}

void Lattice::print_the_same(Node*current){
    
    if(current->level == 0 || current -> level == 1)
    {
        return;
    }
    else
    {
        cout << "\t" << "\t" << current->data.sharePrice;
        print_the_same(current->leftChild->rightChild);
        return;
    }
}

void Lattice::print_right_part(Node* nd) {
    ///recurse right child
    if(nd->level != 0)
    {
        print_right_part(nd->rightChild);
    }
    //check bounding
    if(check_right_bound(nd, root) == true || check_left_bound(nd, root) == true)
    {
        print_tab(nd->level);
    }
    //if it is located at the end, not recurse
    if((nd->level == 0 || nd->level == 1 )&& nLevel > 1)
    {
        cout << nd->data.sharePrice << endl;
    }
    //if it is NOT located at the end, cout++recurse)
    else if(nd->level > 1)
    {
        cout << nd->data.sharePrice;
        print_the_same(nd);
        cout << endl;
    }
    else if(nLevel == 1)
    {
        cout << nd->data.sharePrice << endl;
        return;
    }
    
}

void Lattice::print_left_part(Node* nd) {
    
    //check bounding
    if(check_right_bound(nd, root) == true || check_left_bound(nd, root) == true)
    {
        print_tab(nd->level);
    }
    
    
    //if it is located at the end, not recurse
    if((nd->level == 0 || nd->level == 1 )&& nLevel > 1)
    {
        cout << nd->data.sharePrice << endl;
    }
    //if it is NOT located at the end, cout++recurse)
    else if(nd->level > 1 && nd->parent != 0)
    {
        cout << nd->data.sharePrice;
        print_the_same(nd);
        cout << endl;
    }
    else if(nLevel == 1 && nd->parent != 0)
    {
        cout << nd->data.sharePrice << endl;
        return;
    }
    if(nd->level != 0)
        ///recurse left child
    {
        print_left_part(nd->leftChild);
    }
    
}


void Lattice::print(Node* nd) {
    // TODO
    // After calling buildLattice('''), print the lattice. Refer to "SampleLattice.txt" for output format.
    // REQUIREMENT: printing must be done recursively.
    // HINT: You can add other private recursive function(s) to assist your printing
    
    print_right_part(nd);
    print_left_part(nd);
}

