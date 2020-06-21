#include "GraphManager.h"

GraphManager::GraphManager(vector<Node> nodes)
{
	//setup players
	players = new Player[2];
	players[0] = Player(PlayerSide::RedPlayer);
	players[1] = Player(PlayerSide::BluePlayer);

	//setup nodes
	this->nodes = nodes;

	//create edge matrix
	for (int x = 0; x < nodes.size(); x++) {
		vector<bool> row;
		for (int z = 0; z < nodes.size(); z++) {
			row.push_back(false);
		}
		edges.push_back(row);
	}

	//get all edge connections
	for (int x = 0; x < nodes.size(); x++) {
		/*for (int z = 0; z < nodes[0].size(); z++) {
			MakeAdjecencyOn(nodes[x][z]);
		}*/
		MakeAdjecencyOn(nodes[x]);
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
		/*for (int z = 0; z < nodes[0].size(); z++) {
			nodes[x][z].SetState(Nodestate::Grey);
		}*/
		nodes[x].SetState(Nodestate::Grey);
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
	Node* node = nullptr;
	
	for (int x = 0; x < nodes.size(); x++) {
		//for (int z = 0; z < nodes[0].size(); z++) {
		//	cout << "search node!" << endl;
		//	//change state if this choosed position
		//	if (nodes[x][z].GetPosition() == position) {
		//		cout << "found node by pos!" << endl;
		//		nodes[x][z].SetState(state);
		//		p_node = &nodes[x][z];
		//		break;
		//	}
		//}
		cout << "search node!" << endl;
		//change state if this choosed position
		if (nodes[x].GetPosition() == position) {
			cout << "found node by pos!" << endl;
			nodes[x].SetState(state);
			node = &nodes[x];
			break;
		}
	}

	//update players claimed nodes
	if (state > 0 && node != nullptr) {
		cout << "adding to player" << endl;
		if (node->IsVortex())
			players[state - 1].AddClaimedVortex(node); //vortexes
		else
			players[state - 1].AddClaimedNode(node); //nodes
	}

	AddNodeConnections(node);
}

void GraphManager::MakeAdjecencyOn(Node node)
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

void GraphManager::AddNodeConnections(Node* node)
{
	//for each side
	for (int i = 0; i < s_nodeSides; i++) {
		Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], node->GetXOffset());
		//get node by direction
		int x = node->GetPosition().x + dir.x;
		int z = node->GetPosition().z + dir.z;
		//check if there is node in direction
		Node* nextNode = GetNodeByPosition(Vector3(x, 0, z));
		if (nextNode != nullptr) {
			//is same color
			if (node->GetState() == nextNode->GetState() && node->GetState() > 0) {
				node->AddConnection(nextNode);
				//backwards connect
				nextNode->AddConnection(node);
			}
		}
	}
}

bool GraphManager::IsWinner(int playerSide)
{
	vector<Node*>* nodes = &players[playerSide - 1].GetClaimedNodes();
	vector<Node*>* vortexes = &players[playerSide - 1].GetClaimedVortexes();
	int vortexCount = vortexes->size();

	if (vortexCount < 2) {
		cout << "player hasn't claim even 2 vortexes" << endl;
	}
	
	//find path if there are still atleast 2 unsearched vortexes
	while (vortexCount > 1) {
		//choose start point - one of claimed vortexes
		Node* currentNode = players[playerSide - 1].GetClaimedVortexes()[vortexCount - 1];
		//find another connected nodes
		

		vortexCount--;
	}

	//move to another point a check next connection

	return false;
}

void GraphManager::ShowClaimedNodes(int playerSide)
{
	Player* p_player = &players[playerSide - 1];

	for (int i = 0; i < p_player->GetClaimedNodes().size(); i++) {
		cout << "red node #"<< p_player->GetClaimedNodes()[i]->GetId() << endl;
	}

	for (int i = 0; i < p_player->GetClaimedVortexes().size(); i++) {
		cout << "red vortex #" << p_player->GetClaimedVortexes()[i]->GetId() << endl;
	}
}

void GraphManager::ShowClaimedNodesConnections(int playerSide)
{
	Player* p_player = &players[playerSide - 1];

	for (int i = 0; i < p_player->GetClaimedNodes().size(); i++) {
		cout << "size: " << p_player->GetClaimedNodes()[i]->GetConnectedNodes().size() << endl;
		for (int x = 0; x < p_player->GetClaimedNodes()[i]->GetConnectedNodes().size(); x++) {
			cout << "red node #" << p_player->GetClaimedNodes()[i]->GetId() << " connection to: #" << p_player->GetClaimedNodes()[i]->GetConnectedNodes()[x]->GetId() << endl;
		}
	}

	for (int i = 0; i < p_player->GetClaimedVortexes().size(); i++) {
		for (int x = 0; x < p_player->GetClaimedVortexes()[i]->GetConnectedNodes().size(); x++) {
			cout << "red vortex #" << p_player->GetClaimedVortexes()[i]->GetId() << " connection to: #" << p_player->GetClaimedVortexes()[i]->GetConnectedNodes()[x]->GetId() << endl;
		}
	}
}

Node* GraphManager::GetNodeByPosition(Vector3 position)
{
	Node* node = nullptr;

	for (int x = 0; x < nodes.size(); x++) {
		/*for (int z = 0; z < nodes[0].size(); z++) {
			if (nodes[x][z].GetPosition() == position)
				node = &nodes[x][z];
		}*/
		if (nodes[x].GetPosition() == position)
			node = &nodes[x];
	}

	return node;
}

//Node* GraphManager::GetNodeByConnetion(Node& nodeBase, Vector3 direction)
//{
//	int baseId = nodeBase.GetId();
//
//	for (int i = 0; i < edges[baseId].size(); i++) {
//		int id = edges[baseId][i];
//		if (nodes[id].GetPosition() == nodeBase.GetPosition() + direction)
//			return &nodes[id];
//	}
//
//	return nullptr;
//}

GameState GraphManager::GetGameState()
{
	return gameState;
}
