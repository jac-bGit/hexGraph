#pragma once
#include <vector>
#include <iostream>
#include "GraphManager.h"

enum PlayerSide {
	RedPlayer = 1,
	BluePlayer = 2
};

class Player
{

private:
	PlayerSide playerSide;
	vector<Node*> claimedNodes;
	//vector<Node*> claimedVortexes;

public:
	Player();
	Player(PlayerSide playerSide);
	~Player();

	void AddClaimedNode(Node* node);
	//void AddClaimedVortex(Node* node);

	PlayerSide GetPlayerSide();
	vector<Node*> GetClaimedNodes();
	vector<Node*> GetClaimedVortexes();
};

