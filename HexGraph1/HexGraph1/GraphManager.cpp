#include "GraphManager.h"

GraphManager::GraphManager(vector<Node> nodes)
{
	//setup players
	players = new Player[2];
	players[0] = Player(PlayerSide::RedPlayer);
	players[1] = Player(PlayerSide::BluePlayer);

}

GraphManager::GraphManager(Vector3 graphSize, int vortexCount)
{
	//setup players
	players = new Player[2];
	players[0] = Player(PlayerSide::RedPlayer);
	players[1] = Player(PlayerSide::BluePlayer);

	//setup nodes
	CreateGraph(graphSize);
	cout << "node graph created" << endl;
}

GraphManager::~GraphManager()
{
	delete nodeGraph;
}

//set graph nodes to grey and player to beginning state
void GraphManager::DefaultState()
{
	//all node to grey
	for (int x = 0; x < GetNodeGraphSize().x; x++) {
		for (int z = 0; z < GetNodeGraphSize().z; z++) {
			nodeGraph[x]->SetState(Nodestate::Grey);
		}
	}

	//default player states
	players[0].RestartPlayer();
	players[1].RestartPlayer();
}

void GraphManager::CreateGraph(Vector3 graphSize)
{
	this->graphSize = graphSize;
	this->nodeGraph = new Node * [(int)graphSize.x];
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

	//set neighbours
	for (int x = 0; x < (int)graphSize.x; x++) {
		for (int z = 0; z < (int)graphSize.z; z++) {

			//count neighbours
			int neighbourCount = 0;
			for (int i = 0; i < s_nodeSides; i++) {
				Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], nodeGraph[x][z].GetXOffset());
				int nextX = x + dir.x;
				int nextZ = z + dir.z;
				//within graph size
				if (nextX >= 0 && nextX < (int)graphSize.x && nextZ >= 0 && nextZ < (int)graphSize.z)
					neighbourCount++;
			}
			nodeGraph[x][z].SetNeighbourCount(neighbourCount);

			//add neighbour
			if (neighbourCount > 0) {
				Node** neighbours = new Node * [neighbourCount];
				for (int i = 0; i < s_nodeSides; i++) {
					Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], nodeGraph[x][z].GetXOffset());
					int nextX = x + dir.x;
					int nextZ = z + dir.z;
					//check if there is node in direction
					if (nextX >= 0 && nextX < (int)graphSize.x && nextZ >= 0 && nextZ < (int)graphSize.z) {
						neighbours[neighbourCount - 1] = &nodeGraph[nextX][nextZ];
						neighbourCount--;
					}
				}

				nodeGraph[x][z].SetNeighbourNodes(neighbours);
			}
		}
	}

	//set vortexes
	nodeGraph[0][0].SetIsVortex(true);
	nodeGraph[7][4].SetIsVortex(true);
}

//find node by position and change its state
void GraphManager::ChangeStateOn(Vector3 position, Nodestate state)
{
	Node* node = nullptr;
	
	node = GetNodeByPosition(position);
	node->SetState(state);

	//update players claimed nodes
	if (node != nullptr) {
		if (state > 0) {
			players[state - 1].AddClaimedNode(node);
			AddNodeConnections(node);
			cout << "adding node to player " << state << endl;
		}
		else
			cout << "node [" << position.x << "," << position.z << "] is occupied";
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
	//get player nodes
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

				//is next node vortex
				if (nextNode.IsVortex()) {
					delete path;
					gameState = (GameState)playerSide;
					cout << "player " << playerSide << " won" << endl;
					return true; //connection is succesful
				}
				else {
					//add to path and move to next
					path->push_back(&nextNode);
					//delete searched connection 
					currentNode.RemoveConnection(0);
					currentNode = nextNode;
				}
			}
			else {	
				if (path->size() < 2) {
					cout << "path lost" << endl;
					break;
				}
				//return back
				currentNode = *(*path->end() - 1);
				path->erase(path->end());
			}
		}

		vortexCount--;
		delete path;
	}

	return false;
}

Node* GraphManager::GetNodeByPosition(Vector3 position)
{
	//is within graph size
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
