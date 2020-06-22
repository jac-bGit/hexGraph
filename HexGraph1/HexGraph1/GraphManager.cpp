#include "GraphManager.h"

GraphManager::GraphManager(vector<Node> nodes)
{
	//setup players
	players = new Player[2];
	players[0] = Player(PlayerSide::RedPlayer);
	players[1] = Player(PlayerSide::BluePlayer);

	//setup nodes
	//this->nodes = nodes;

	////create edge matrix
	//for (int x = 0; x < nodes.size(); x++) {
	//	vector<bool> row;
	//	for (int z = 0; z < nodes.size(); z++) {
	//		row.push_back(false);
	//	}
	//	edges.push_back(row);
	//}

	////get all edge connections
	//for (int x = 0; x < nodes.size(); x++) {
	//	/*for (int z = 0; z < nodes[0].size(); z++) {
	//		MakeAdjecencyOn(nodes[x][z]);
	//	}*/
	//	MakeAdjecencyOn(nodes[x]);
	//}

	////show edge matrix
	//for (int x = 0; x < edges.size(); x++) {
	//	for (int z = 0; z < edges[0].size(); z++) {
	//		std::cout << edges[x][z] << " ";
	//	}
	//	std::cout << endl;
	//}

}

GraphManager::GraphManager(Vector3 graphSize, int vortexCount)
{
	//setup players
	players = new Player[2];
	players[0] = Player(PlayerSide::RedPlayer);
	players[1] = Player(PlayerSide::BluePlayer);

	//setup nodes
	this->graphSize = graphSize;
	this->nodeGraph = new Node*[(int)graphSize.x];
	int id = 0;

	for (int x = 0; x < (int)graphSize.x; x++) {
		//set row
		nodeGraph[x] = new Node[(int)graphSize.z];
		for (int z = 0; z < (int)graphSize.z; z++) {
			//create nodes
			nodeGraph[x][z] = Node(id, Vector3(x, 0, z), false);
			id++;
		}
	}
	cout << "node graph created" << endl;

	//set neighbours
	for (int x = 0; x < (int)graphSize.x; x++) {
		for (int z = 0; z < (int)graphSize.z; z++) {

			//count neighbours
			int neighbourCount = 0;
			for (int i = 0; i < s_nodeSides; i++) {
				Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], nodeGraph[x][z].GetXOffset());
				//get node by direction
				int nextX = x + dir.x;
				int nextZ = z + dir.z;
				//check if there is node in direction
				if (nextX >= 0 && nextX < (int)graphSize.x && nextZ >= 0 && nextZ < (int)graphSize.z)
					neighbourCount++;
			}

			nodeGraph[x][z].SetNeighbourCount(neighbourCount);
			cout << "neighbourCount for node [" << x << ", " << z << "]: " << neighbourCount << endl;

			//add neighbour
			if (neighbourCount > 0) {
				Node** neighbours = new Node * [neighbourCount];
				for (int i = 0; i < s_nodeSides; i++) {
					Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], nodeGraph[x][z].GetXOffset());
					//get node by direction
					int nextX = x + dir.x;
					int nextZ = z + dir.z;
					//check if there is node in direction
					if (nextX >= 0 && nextX < (int)graphSize.x && nextZ >= 0 && nextZ < (int)graphSize.z) {
						neighbours[neighbourCount - 1] = &nodeGraph[nextX][nextZ];
						neighbourCount--;
						cout << "neighbour id for node [" << x << ", " << z << "]: " << ": #" << "[" << neighbours[neighbourCount]->GetPosition().x << ", " << neighbours[neighbourCount]->GetPosition().z << "]: " << endl;
					}
				}

				nodeGraph[x][z].SetNeighbourNodes(neighbours);
				//delete *neighbours;
			}
		}
	}

	//show neighbours
	for (int x = 0; x < (int)graphSize.x; x++) {
		for (int z = 0; z < (int)graphSize.z; z++) {
			
			cout << "node [" << x << ", " << z << "] neighbours: " << nodeGraph[x][z].GetNeighbourCount() << endl;
			for(int i = 0; i < nodeGraph[x][z].GetNeighbourCount(); i++)
				cout << "node #" << nodeGraph[x][z].GetId() << "["<< x << ", "<< z << "]: #" << nodeGraph[x][z].GetNeighbourNodes()[i]->GetId() <<
				" on cord: [" << nodeGraph[x][z].GetNeighbourNodes()[i]->GetPosition().x << "," <<
				nodeGraph[x][z].GetNeighbourNodes()[i]->GetPosition().y << "]"<< endl;
		}
	} 

	//set vortexes
	nodeGraph[0][0].SetIsVortex(true);
	nodeGraph[2][0].SetIsVortex(true);
}

//set graph nodes to grey and player to beginning state
void GraphManager::DefaultState()
{
	//all nodes to grey
	/*for (int x = 0; x < nodes.size(); x++) {
		nodes[x].SetState(Nodestate::Grey);
	}*/

	for (int x = 0; x < GetNodeGraphSize().x; x++) {
		for (int z = 0; z < GetNodeGraphSize().z; z++) {
			nodeGraph[x]->SetState(Nodestate::Grey);
		}
	}

	//default player states
	players[0].RestartPlayer();
	players[1].RestartPlayer();
}

//find node by position and change its state
void GraphManager::ChangeStateOn(Vector3 position, Nodestate state)
{
	Node* node = nullptr;
	
	//for (int x = 0; x < nodes.size(); x++) {
	//	//change state if this choosed position
	//	if (nodes[x].GetPosition() == position) {
	//		nodes[x].SetState(state);
	//		node = &nodes[x];
	//		break;
	//	}
	//}

	//for (int x = 0; x < GetNodeGraphSize().x; x++) {
	//	for (int z = 0; z < GetNodeGraphSize().z; z++) {
	//		//change state if this choosed position
	//		if (nodeGraph[x][z].GetPosition() == position) {
	//			nodeGraph[x][z].SetState(state);
	//			node = &nodeGraph[x][z];
	//			break;
	//		}
	//	}
	//}
	node = GetNodeByPosition(position);
	node->SetState(state);

	//update players claimed nodes
	if (state > 0 && node != nullptr) {
		players[state - 1].AddClaimedNode(node);
		AddNodeConnections(node);
		cout << "adding node to player " << state << endl;
	}
}


//
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
			std::cout << "connection between: " << id << ", " << nextId << endl;
		}
	}
}


//look on each neighbour and add reference to every node of same color
void GraphManager::AddNodeConnections(Node* node)
{
	//for each side
	for (int i = 0; i < node->GetNeighbourCount(); i++) {
		Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], node->GetXOffset());
		//get node by direction
		int x = node->GetPosition().x + dir.x;
		int z = node->GetPosition().z + dir.z;
		//check if there is node in direction
		Node* nextNode = node->GetNeighbourNodes()[i];
		if (nextNode != nullptr) {
			//is same state (color)
			if (node->GetState() == nextNode->GetState() && node->GetState() > 0) {
				node->AddConnection(nextNode);
				//backwards connect
				nextNode->AddConnection(node);
			}
		}
	}
}

//check if player has connection between atleast two vortexes
bool GraphManager::IsWinner(int playerSide)
{
	vector<Node*> nodes = players[playerSide - 1].GetClaimedNodes();
	vector<Node*> vortexes = players[playerSide - 1].GetClaimedVortexes();
	int vortexCount = vortexes.size();

	if (vortexCount < 2) {
		cout << "player hasn't claim even 2 vortexes" << endl;
	}
	
	//find path if there are still atleast 2 unsearched vortexes
	while (vortexCount > 1) {
		vector<Node*>* path = new vector<Node*>();

		//choose start point - one of claimed vortexes
		Node currentNode = *vortexes[vortexCount - 1];
		path->push_back(&currentNode);

		while (true) {
			cout << "connected to current: " << currentNode.GetConnectedNodes().size() << endl;
			//move to next connection
			if (currentNode.IsContected()) {
				Node nextNode = *currentNode.GetConnectedNodes()[0];

				//is next node vertex
				if (nextNode.IsVortex()) {
					delete path;
					return true; //connection is succesful
				}
				else {
					//add to path
					path->push_back(&nextNode);
					//delete connection
					currentNode.RemoveConnection(0);
					//move to next
					currentNode = nextNode;
				}
			}
			else {				
				//return back
				currentNode = *(*path->end() - 1);
				path->erase(path->end());
			}
			if (path->size() == 0)
				break;
		}

		vortexCount--;
		delete path;
	}

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
			cout << "red node #" << p_player->GetClaimedNodes()[i]->GetId() << " neigbour to: #" << p_player->GetClaimedNodes()[i]->GetNeighbourNodes()[x]->GetId() << endl;
		}
	}

	for (int i = 0; i < p_player->GetClaimedVortexes().size(); i++) {
		for (int x = 0; x < p_player->GetClaimedVortexes()[i]->GetConnectedNodes().size(); x++) {
			cout << "red vortex #" << p_player->GetClaimedVortexes()[i]->GetId() << " neigbour to: #" << p_player->GetClaimedVortexes()[i]->GetNeighbourNodes()[x]->GetId() << endl;
		}
	}
}

Node* GraphManager::GetNodeByPosition(Vector3 position)
{
	//Node* node = nullptr;

	/*for (int x = 0; x < nodes.size(); x++) {
		if (nodes[x].GetPosition() == position)
			node = &nodes[x];
	}*/

	/*Vector3 vec = graphSize;
	cout << "vec.x: " << vec.x << endl;
	cout << "vec.z: " << vec.z << endl;

	for (int x = 0; x < GetNodeGraphSize().x; x++) {
		for (int z = 0; z < GetNodeGraphSize().z; z++) {
			if (nodeGraph[x][z].GetPosition() == position)
				node = &nodeGraph[x][z];
		}
	}

	return node;*/
	if(position.x >= 0 && position.x < graphSize.x && position.z >= 0 && position.z < graphSize.z)
		return &nodeGraph[(int)position.x][(int)position.z];
	else {
		cout << "Node position is out of range" << endl;
		return nullptr;
	}
}

Vector3 GraphManager::GetNodeGraphSize()
{
	return graphSize;
}

GameState GraphManager::GetGameState()
{
	return gameState;
}

void GraphManager::SetGameState(GameState gameState)
{
	this->gameState = gameState;
}
