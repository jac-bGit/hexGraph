#pragma once
#include <vector>
#include "Node.h"
#include "Edge.h"
#include <iostream>

using namespace std;

enum GameState {
	Playing = 0,
	RedWin = 1,
	BlueWin = 2
};

class GraphManager
{
private:
	vector<vector<Node>> nodes;
	//vector<Edge> edges;
	vector<vector<bool>> edges;
	GameState gameState = GameState::Playing;

public:
	GraphManager(vector<vector<Node>> nodes);

	void DefaultState();
	void ChangeStateOn(Vector3 position, Nodestate state);
	void ChangeStateOn(int x, int z, Nodestate state);
	void GetConnectedNodesOn(Node node);

	void CheckWin();

	Node* GetNodeByPosition(Vector3 position);

	GameState GetGameState();
};

