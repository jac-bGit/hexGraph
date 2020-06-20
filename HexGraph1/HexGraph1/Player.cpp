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

void Player::AddClaimedNode(Node node)
{
	claimedNodes.push_back(node);
}

void Player::AddClaimedVortex(Node node)
{
	if (node.IsVortex())
		claimedVortexes.push_back(node);
	else
		std::cout << "added node is not vortex!" << endl;
}

PlayerSide Player::GetPlayerSide()
{
	return playerSide;
}

vector<Node> Player::GetClaimedNodes()
{
	return claimedNodes;
}

vector<Node> Player::GetClaimedVortexes()
{
	return claimedVortexes;
}
