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

public:
	Player();
	Player(PlayerSide playerSide);
	~Player();

	void AddClaimedNode(Node* node);
	void RestartPlayer();

	PlayerSide GetPlayerSide();
	vector<Node*> GetClaimedNodes();
	vector<Node*> GetClaimedVortexes();
};

