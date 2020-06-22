#include "Player.h"

Player::Player()
{
}

Player::Player(PlayerSide playerSide)
{
	this->playerSide = playerSide;
}

Player::~Player()
{
}

void Player::AddClaimedNode(Node* node)
{
	claimedNodes.push_back(node);
}

void Player::RestartPlayer()
{
	claimedNodes.clear();
}

PlayerSide Player::GetPlayerSide()
{
	return playerSide;
}

vector<Node*> Player::GetClaimedNodes()
{
	return claimedNodes;
}

//return only vortex nodes
vector<Node*> Player::GetClaimedVortexes()
{
	vector<Node*> vortexes;
	for (int i = 0; i < claimedNodes.size(); i++) {
		if (claimedNodes[i]->IsVortex())
			vortexes.push_back(claimedNodes[i]);
	}
	return vortexes;
}
