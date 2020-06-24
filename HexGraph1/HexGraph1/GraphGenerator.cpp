#include "GraphGenerator.h"

GraphGenerator::GraphGenerator()
{
}

//return node matrix with grey nodes by ratio - others are blocked
Node** GraphGenerator::GenerateGraph(Vector3 graphSize, float greyNodesRatio, int vortexCount)
{
	Node** nodeGraph = nullptr;
	this->graphSize = graphSize;

	//node count
	if (greyNodesRatio > 1.0f)
		greyNodesRatio = 1.0f;
	int greyCount = graphSize.x * graphSize.z * greyNodesRatio;

	//create base matrix
	int id = 0;
	for (int x = 0; x < (int)graphSize.x; x++) {
		//set row
		nodeGraph[x] = new Node[(int)graphSize.z];
		for (int z = 0; z < (int)graphSize.z; z++) {
			//create nodes
			nodeGraph[x][z] = Node(id, Vector3(x, 0, z), false);
			nodeGraph[x][z].SetState(Nodestate::BlockedNode);
			id++;
		}
	}

	//asign grey nodes
	SetGreyNodes(nodeGraph, greyCount);

	//get edge nodes
	vector<Node*> edgeNodes = AllEdgeNodes(nodeGraph);

	//set vortexes on edges
	SetVortexes(edgeNodes, vortexCount);

	//set nodes neighbour connections
	SetNeighbours(nodeGraph);

	return nodeGraph;
}

Vector3 GraphGenerator::GetGraphSize()
{
	return graphSize;
}

int GraphGenerator::RandomRange(int min, int max)
{
	srand(time(0));
	return (rand() % max) + min;
}

//distance is represented by longer axis distance, not real distance magnitude
int GraphGenerator::DistanceBetween(Node* nodeA, Node* nodeB)
{
	Vector3 posA = nodeA->GetPosition();
	Vector3 posB = nodeB->GetPosition();
	int x = abs(posA.x - posB.x);
	int z = abs(posA.z - posB.z);
	return (x > z)? x : z;
}

//setup grey node state on random positions within pattern
void GraphGenerator::SetGreyNodes(Node**& nodeGraph, int count)
{
	int rowSize = (int)graphSize.x;
	int avgInRow = count / rowSize / 2;
	bool firstIteration = true;
	int basePosX = RandomRange(0, rowSize - avgInRow - 1);
	int rowId = 0;

	while (count > 0) {

		if (firstIteration) {
			for (int i = 0; i < avgInRow; i++) {
				nodeGraph[rowId][basePosX + i].SetState(Nodestate::Grey);
				count--;
				//next base position
				int min = (basePosX - avgInRow > 0) ? basePosX - avgInRow : 0;
				int max = (basePosX + avgInRow < rowSize - 1) ? basePosX + avgInRow : rowSize - 1;
				basePosX = RandomRange(min, max);
			}

			//end first iteration
			if (rowId == rowSize - 1)
				firstIteration = false;
		}
		else {
			//randomly add grey edge node
			int addTo = RandomRange(-1, 1);
			if (addTo != 0) {
				Node* edgeNode = EdgeNodeWithin(nodeGraph, addTo, rowId);
				//row edge nodes will be skipped
				if (edgeNode != nullptr) {
					edgeNode->SetState(Nodestate::Grey);
					count--;
				}
			}
		}

		rowId++;
		if (rowId == rowSize)
			rowId = 0;
	}
}

//find node on edge in given row, -1 - left, +1 and 0 - right
Node* GraphGenerator::EdgeNode(Node**& nodeGraph, int side, int row)
{
	//normalize or zero fix to right
	side = (side != 0) ? side / side : 1;

	int len = (int)graphSize.z - 1;
 
	for (int i = 0; i < len; i++) {
		//withing row
		if (i > 0 && i + 1 < len) {
			if (nodeGraph[row][i].GetState() == Nodestate::Grey && nodeGraph[row][i + 1].GetState() == Nodestate::BlockedNode)
				return &nodeGraph[row][i];
		}
		//on row edges
		else {
			if(nodeGraph[row][0].GetState() == Nodestate::Grey) //right end
				return &nodeGraph[row][len];
			if(nodeGraph[row][0].GetState() == Nodestate::Grey) //left end
				return &nodeGraph[row][0];
		}
	}

	return nullptr;
}

//similar to EdgeNode(), nodes on row edge are not counted
Node* GraphGenerator::EdgeNodeWithin(Node**& nodeGraph, int side, int row)
{
	//normalize or zero fix to right
	side = (side != 0) ? side / side : 1;

	int len = (int)graphSize.z - 1;

	for (int i = 0; i < len; i++) {
		//withing row
		if (i > 0 && i + 1 < len) {
			if (nodeGraph[row][i].GetState() == Nodestate::Grey && nodeGraph[row][i + 1].GetState() == Nodestate::BlockedNode)
				return &nodeGraph[row][i];
		}
	}

	return nullptr;
}

//return all edges nodes of graph
vector<Node*> GraphGenerator::AllEdgeNodes(Node**& nodeGraph)
{
	vector<Node*> edgeNodes;
	int lenX = (int)graphSize.x - 1;
	int lenZ = (int)graphSize.z - 1;

	//all top nodes
	for (int i = 0; i < lenZ; i++) {
		edgeNodes.push_back(&edgeNodes[0][i]);
	}

	//center nodes
	for (int i = 1; i < lenX - 1; i++) {
		edgeNodes.push_back(EdgeNode(nodeGraph, -1, i));
		edgeNodes.push_back(EdgeNode(nodeGraph, 1, i));
	}

	//all botom nodes
	for (int i = 0; i < lenZ; i++) {
		edgeNodes.push_back(&edgeNodes[lenX][i]);
	}

	return edgeNodes;
}

//set vortexes on random positions
void GraphGenerator::SetVortexes(vector<Node*> edgeNodes, int vortexCount)
{
	vector<Node*> vortexes;
	int closest = 0;

	while (vortexCount > 0) {
		int id = RandomRange(0, edgeNodes.size());

		if (vortexes.size() > 1) {
			//get distance to closest vortex
			closest = DistanceBetween(edgeNodes[id], edgeNodes[0]);
			for (int i = 0; i < edgeNodes.size(); i++) {
				if (closest > DistanceBetween(edgeNodes[id], edgeNodes[i]))
					closest = DistanceBetween(edgeNodes[id], edgeNodes[i]);
			}
		}

		//set vortex if is not allready
		if (edgeNodes[id]->IsVortex() == false) {
			//compare if distance to closest vortex is reasonable
			if (vortexes.size() > 1) {
				if (closest < vortexDistance) {
					edgeNodes[id]->SetIsVortex(true);
					vortexes.push_back(edgeNodes[id]);
					vortexCount--;
				}
			}
			else {
				edgeNodes[id]->SetIsVortex(true);
				vortexes.push_back(edgeNodes[id]);
				vortexCount--;
			}
		}
	}

	vortexes.clear();
}

//set connections for every not blocked node to every node in reach
void GraphGenerator::SetNeighbours(Node**& nodeGraph)
{
	for (int x = 0; x < (int)graphSize.x; x++) {
		for (int z = 0; z < (int)graphSize.z; z++) {

			if (nodeGraph[x][z].GetState() != Nodestate::BlockedNode) {

				//count neighbours
				int neighbourCount = 0;
				for (int i = 0; i < s_nodeSides; i++) {
					Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], nodeGraph[x][z].GetXOffset());
					int nextX = x + dir.x;
					int nextZ = z + dir.z;
					//within graph size
					if (nextX >= 0 && nextX < (int)graphSize.x && nextZ >= 0 && nextZ < (int)graphSize.z) {
						if (nodeGraph[nextX][nextZ].GetState() != Nodestate::BlockedNode)
							neighbourCount++;
					}
				}
				nodeGraph[x][z].SetNeighbourCount(neighbourCount);

				//add neighbours
				if (neighbourCount > 0) {
					Node** neighbours = new Node * [neighbourCount];
					for (int i = 0; i < s_nodeSides; i++) {
						Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], nodeGraph[x][z].GetXOffset());
						int nextX = x + dir.x;
						int nextZ = z + dir.z;
						//check if there is node in direction
						if (nextX >= 0 && nextX < (int)graphSize.x && nextZ >= 0 && nextZ < (int)graphSize.z) {
							if (nodeGraph[nextX][nextZ].GetState() != Nodestate::BlockedNode) {
								neighbours[neighbourCount - 1] = &nodeGraph[nextX][nextZ];
								neighbourCount--;
							}
						}
					}

					nodeGraph[x][z].SetNeighbourNodes(neighbours);
				}

			}//end of blocked node check
		}
	}
}
