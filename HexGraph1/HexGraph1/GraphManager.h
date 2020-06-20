#pragma once

#include <iostream>
#include <vector>
#include "Node.h"
#include "Edge.h"
#include "Player.h"

using namespace std;

class Player;

enum GameState {
	Playing = 0,
	RedWin = 1,
	BlueWin = 2
};

class GraphManager
{
private:
	Player* players;

	vector<vector<Node>> nodes;
	//vector<Edge> edges;
	vector<vector<bool>> edges;
	GameState gameState = GameState::Playing;

public:
	GraphManager(vector<vector<Node>> nodes);

	void DefaultState();
	void ChangeStateOn(Vector3 position, Nodestate state);
	void ChangeStateOn(int x, int z, Nodestate state);
	void MakeEdgeConnections(Node node);
	void CheckWinFor(GameState gameState);

	Node* GetNodeByPosition(Vector3 position);

	GameState GetGameState();
};

