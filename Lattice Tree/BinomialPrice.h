#ifndef BINOMIALPRICE_H
#define BINOMIALPRICE_H

#include "Option.h"
#include "Lattice.h"

class BinomialPrice
{
public:
	Option*			option;
	int				steps;
	Lattice*		lattice;
	
	BinomialPrice(Option* pOpt, int nSteps);

	Node* buildLattice(Node* node, Node* leftChild, int nFromLeafNode);
	void backwardEval(Node*); // for European Call ONLY

private:
	double			dt;		// delta time
	double			u;		// up factor
	double			d;		// down factor = 1/u
	double			pu;		// up probability
	double			pd;		// down probability = 1 - pu
	double			discount;
};

#endif