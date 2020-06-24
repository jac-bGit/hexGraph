#pragma once

#include <ctime>
#include <cstdlib>
#include <vector>

#include "Node.h"
#include "Vector.h"

class GraphGenerator
{
private:
	Vector3 graphSize;
	int vortexDistance = 5;

public:
	GraphGenerator();

	Node** GenerateGraph(Vector3 graphSize, float greyNodesRatio, int vortexCount);
	Vector3 GetGraphSize();

private:
	int RandomRange(int min, int max);
	int DistanceBetween(Node* nodeA, Node* nodeB);

	void SetGreyNodes(Node**& nodeGraph, int count);
	Node* EdgeNode(Node**& nodeGraph, int side, int row);
	Node* EdgeNodeWithin(Node**& nodeGraph, int side, int row);
	vector<Node*> AllEdgeNodes(Node**& nodeGraph);
	void SetVortexes(vector<Node*> edgeNodes, int vortexCount);
	void SetNeighbours(Node**& nodeGraph);
};

