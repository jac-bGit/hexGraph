#include "Node.h"

Node::Node()
{
}

Node::Node(int id, Vector3 position, bool isVortex)
{
	this->id = id;
	this->position = position;
	this->isVortex = isVortex;

	//offset for odd z position
	if ((int)position.z % 2 != 0)
		xOffset = s_nodeXOffset;
}

Node::~Node()
{
}

int Node::GetId()
{
	return id;
}

Vector3 Node::GetPosition()
{
	return position;
}

int Node::GetState()
{
	return state;
}

void Node::SetState(Nodestate state)
{
	this->state = state;
}

bool Node::IsVortex()
{
	return isVortex;
}

void Node::SetIsVortex(bool isVortex)
{
	this->isVortex = isVortex;
}

bool Node::IsContected()
{
	if (connectedNodes.size() > 0)
		return true;
	return false;
}

float Node::GetXOffset()
{
	return xOffset;
}

void Node::SetNeighbourNodes(Node** neighbourNodes)
{
	this->neighbourNodes = neighbourNodes;
}

Node** Node::GetNeighbourNodes()
{
	return neighbourNodes;
}

int Node::GetNeighbourCount()
{
	return neighbourCount;
}

void Node::SetNeighbourCount(int neighbourCount)
{
	this->neighbourCount = neighbourCount;
}

vector<Node*> Node::GetConnectedNodes()
{	
	return connectedNodes;
}

void Node::AddConnection(Node* node)
{
	connectedNodes.push_back(node);
	//cout << "connectedNodes size: " << connectedNodes.size() << endl;
	//cout << "add is empty: " << endl;
}

//remove connection to this node
void Node::RemoveConnection(int id)
{
	connectedNodes.erase(connectedNodes.begin() + id);
	//cout << "remove is empty: " << endl;
}
