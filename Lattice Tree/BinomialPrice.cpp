#include "BinomialPrice.h"
#include <math.h>

BinomialPrice::BinomialPrice(Option* pOpt, int nSteps)
: option(pOpt), steps(nSteps)
{
    lattice = new Lattice();
    dt = option->maturity / nSteps;
    u = exp(option->vol * sqrt(dt));
    d = 1/u;
    pu = (exp(option->rate * dt) - d) / (u - d);
    pd = 1.0 - pu;
    discount = exp(-option->rate * dt);
};

Node*    // return the rightChild of t
BinomialPrice::buildLattice(Node* t, Node* leftChild, int nFromLeafNode)
/*    Pseudo Code
 If lattice is empty (t==0)
 Create root node
 Fill in data for root node
 EndIf
 If height of lattice > 0 (nFromLeafNode > 0)
 If leftChild does not exist (leftChild == 0)
 Create leftChild node
 Fill in data for leftChild node
 build left sub-lattice (Call buildLattice recursively)
 Else
 Set the leftChild of t = leftChild
 Create rightChild node
 Fill in data for rightChild node
 build right sub-lattice (Call buildLattice recursively)
 EndIf
 */
{
    // TODO
    if(lattice->root == 0)
    {
        lattice->setLevel(steps);
        t = lattice->root = new Node(option->spotPrice);
        t->level = nFromLeafNode = lattice->getLevel();
    }
    
    if(nFromLeafNode > 0)
    {
        if(t->leftChild == 0)
        {
            t->leftChild = new Node(t->data.sharePrice * d);
            t->leftChild->parent = t;
            t->leftChild->level = nFromLeafNode - 1;
            BinomialPrice::buildLattice(t->leftChild, t->leftChild->leftChild, nFromLeafNode-1);
        }
        else
        {
            t->leftChild = leftChild;
        }
        
        if(t->rightChild == 0)
        {
            t->rightChild = new Node(t->data.sharePrice * u);
            t->rightChild->parent = t;
            t->rightChild->level = nFromLeafNode-1;
            BinomialPrice::buildLattice(t->rightChild, t->leftChild->rightChild, nFromLeafNode-1);
        }
        
    }
    
    return 0;
}

void
BinomialPrice::backwardEval(Node* t) {
    // TODO
    // Recursively evaluate option
    if( option->e_a == European || (option->e_a == American && option->c_p == Call) )
    {
        if(option->c_p == Call)
        {
            if(t->level == 0)
            {
                if(t->data.sharePrice - option->strikePrice > 0)
                {
                    t->data.optionPrice = t->data.sharePrice - option->strikePrice;
                }
                else
                {
                    t->data.optionPrice = 0;
                }
            }
        }
        else if(option->c_p == Put)
        {
            if(t->level == 0)
            {
                if(option->strikePrice - t->data.sharePrice > 0)
                {
                    t->data.optionPrice = option->strikePrice - t->data.sharePrice;
                }
                else
                {
                    t->data.optionPrice = 0;
                }
            }
        }
        
        if(t->level != 0)
        {
            BinomialPrice::backwardEval(t->leftChild);
            BinomialPrice::backwardEval(t->rightChild);
            
            t->data.optionPrice = (pd*(t->leftChild->data.optionPrice) + pu*(t->rightChild->data.optionPrice))*discount;
        }
    }
    
    else if(option->e_a == American && option->c_p == Put)
    {
        if(t->level == 0)
        {
            if(option->strikePrice - t->data.sharePrice > 0)
            {
                t->data.optionPrice = option->strikePrice - t->data.sharePrice;
            }
            else
            {
                t->data.optionPrice = 0;
            }
        }
        
        if(t->level != 0)
        {
            BinomialPrice::backwardEval(t->leftChild);
            BinomialPrice::backwardEval(t->rightChild);
            
            if( (option->strikePrice - t->data.sharePrice) >
               (pd*(t->leftChild->data.optionPrice) + pu*(t->rightChild->data.optionPrice))*discount )
            {
                t->data.optionPrice = option->strikePrice - t->data.sharePrice;
            }
            else
            {
                t->data.optionPrice = (pd*(t->leftChild->data.optionPrice) + pu*(t->rightChild->data.optionPrice))*discount;
            }
        }
    }
    
}


