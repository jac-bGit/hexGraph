#include "GraphManager.h"

GraphManager::GraphManager(vector<vector<Node>> nodes)
{
	//setup players
	players = new Player[2];
	players[0] = Player(PlayerSide::RedPlayer);
	players[1] = Player(PlayerSide::BluePlayer);

	//setup nodes
	this->nodes = nodes;

	//create edge matrix
	for (int x = 0; x < nodes[0].size(); x++) {
		vector<bool> row;
		for (int z = 0; z < nodes[0].size(); z++) {
			row.push_back(false);
		}
		edges.push_back(row);
	}

	//get all edge connections
	for (int x = 0; x < nodes.size(); x++) {
		for (int z = 0; z < nodes[0].size(); z++) {
			MakeEdgeConnections(nodes[x][z]);
		}
	}

	//show edge matrix
	for (int x = 0; x < edges.size(); x++) {
		for (int z = 0; z < edges[0].size(); z++) {
			std::cout << edges[x][z] << " ";
		}
		std::cout << endl;
	}

}

//set graph nodes to grey and player to beginning state
void GraphManager::DefaultState()
{
	//all node to grey
	for (int x = 0; x < nodes.size(); x++) {
		for (int z = 0; z < nodes[0].size(); z++) {
			nodes[x][z].SetState(Nodestate::Grey);
		}
	}

	//default player states
}

void GraphManager::ChangeStateOn(Vector3 position, Nodestate state)
{
	//find node with selected position
	/*for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].GetPosition() == position) {
			nodes[i].SetState(state);
			break;
		}
	}*/
	Node* p_node = nullptr;
	
	for (int x = 0; x < nodes.size(); x++) {
		for (int z = 0; z < nodes.size(); z++) {
			//change state if this choosed position
			if (nodes[x][z].GetPosition() == position) {
				nodes[x][z].SetState(state);
				p_node = &nodes[x][z];
				break;
			}
		}
	}

	//update players claimed nodes
	if (state > 0) {
		if (p_node->IsVortex())
			players[state - 1].AddClaimedVortex(*p_node);
		else
			players[state - 1].AddClaimedNode(*p_node);
	}
}

void GraphManager::MakeEdgeConnections(Node node)
{
	//check 
	for (int i = 0; i < s_nodeSides; i++) {
		Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], node.GetXOffset());
		//get node by direction
		int x = node.GetPosition().x + dir.x;
		int z = node.GetPosition().z + dir.z;
		//check if there is node in direction
		Node* p_nextNode = GetNodeByPosition(Vector3(x, 0, z));
		if (p_nextNode != nullptr) {
			int nextId = p_nextNode->GetId();
			int id = node.GetId();
			edges[id][nextId] = true;
			edges[nextId][id] = true;
			std::cout << "kurva on: " << id << ", " << nextId << endl;
		}
		/*if (x >= 0 && x < nodes[0].size() && z >= 0 && z < nodes.size()) {
			Node* p_nextNode = GetNodeByPosition(Vector3(x, 0, z));
			if (p_nextNode != nullptr) {
				int nextId = p_nextNode->GetId();
				int id = node.GetId();
				edges[id][nextId] = true;
				edges[nextId][id] = true;
				std::cout << "kurva on: " << id << ", " << nextId << endl;
			}
		}*/
	}
}

void GraphManager::CheckWinFor(GameState gameState)
{
	//choose claimed vortex
	 

	//find if there is another connected point

	//move to another point a check next connection
}

Node* GraphManager::GetNodeByPosition(Vector3 position)
{
	Node* node = nullptr;

	for (int x = 0; x < nodes.size(); x++) {
		for (int z = 0; z < nodes[0].size(); z++) {
			if (nodes[x][z].GetPosition() == position)
				node = &nodes[x][z];
		}
	}

	return node;
}

GameState GraphManager::GetGameState()
{
	return gameState;
}
