#pragma once

#include "Vector.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

const float PI = 3.1415927;

//definition of node shape
const static int s_nodeSides = 6;
static float s_nodeXOffset = 0.5f;
static Vector3 s_nodeDirections[s_nodeSides] = {
	Vector3(1,0,0), //right
	Vector3(cos(60 * PI / 180),0, sin(60 * PI / 180)), //60 deg
	Vector3(cos(120 * PI / 180),0, sin(120 * PI / 180)), //120 deg
	Vector3(-1,0,0), //left
	Vector3(cos(240 * PI / 180),0, sin(240 * PI / 180)), //240 deg
	Vector3(cos(300 * PI / 180),0, sin(300 * PI / 180)) //300 deg
};

//normalize vectors X and Z
static Vector3 NormalizeDirection2D(Vector3 direction, float xOffset) {
	//x
	direction.x = round(direction.x - 0.1 + xOffset);
	/*if(direction.x != 0)
		direction.x /= abs(direction.x);*/
	//z
	direction.z = round(direction.z);
	/*if (direction.z != 0)
		direction.z /= abs(direction.z);*/

	return direction;
}

//enums
enum Nodestate
{
	Grey = 0,
	Red = 1,
	Blue = 2
};

class Node
{
private:
	int id;
	Vector3 position;
	float xOffset = 0;
	Nodestate state = Nodestate::Grey;
	bool isVortex;
	Node** neighbourNodes;
	int neighbourCount = 0;
	vector<Node*> connectedNodes;

public:
	Node();
	Node(int id, Vector3 position, bool isVortex);
	~Node();

	int GetId();
	Vector3 GetPosition();
	int GetState();
	void SetState(Nodestate state);
	bool IsVortex();
	void SetIsVortex(bool isVortex);
	bool IsContected();
	float GetXOffset();
	void SetNeighbourNodes(Node** neighbourNodes);
	Node** GetNeighbourNodes();
	int GetNeighbourCount();
	void SetNeighbourCount(int neighbourCount);
	vector<Node*> GetConnectedNodes();

	void AddConnection(Node* node);
	void RemoveConnection(int id);
};

