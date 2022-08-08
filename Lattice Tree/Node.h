#ifndef NODE_H
#define NODE_H

class NData
{
public:
	double	sharePrice;
	double	optionPrice;

	NData() : sharePrice(0.0), optionPrice(0.0) {};
};

class Node
{
public:
	NData	data;
	Node*	leftChild;
	Node*	rightChild;
	Node*	parent;
	int		level;

	Node(double price)
		: leftChild(0), rightChild(0), parent(0) { data.sharePrice = price; }
};

#endif