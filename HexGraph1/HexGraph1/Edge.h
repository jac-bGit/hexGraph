#pragma once

#include "Node.h"

class Edge 
{
private:
	Node nodeA;
	Node nodeB;

public:
	Edge(Node nodeA, Node nodeB) {
		this->nodeA = nodeA;
		this->nodeB = nodeB;
	};
};