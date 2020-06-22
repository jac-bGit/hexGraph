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

vector<Node*> Node::GetConnectedNodes()
{	
	return connectedNodes;
}

void Node::AddConnection(Node* node)
{
	connectedNodes.push_back(node);
	//cout << "connectedNodes size: " << connectedNodes.size() << endl;
}

//remove connection to this node
void Node::RemoveConnection(int id)
{
	connectedNodes.erase(connectedNodes.begin() + id);
}
