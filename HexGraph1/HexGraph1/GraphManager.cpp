#include "GraphManager.h"

GraphManager::GraphManager(vector<vector<Node>> nodes)
{
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
			GetConnectedNodesOn(nodes[x][z]);
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

void GraphManager::ChangeStateOn(Vector3 position, Nodestate state)
{
	//find node with selected position
	/*for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].GetPosition() == position) {
			nodes[i].SetState(state);
			break;
		}
	}*/

	for (int x = 0; x < nodes.size(); x++) {
		for (int z = 0; z < nodes.size(); z++) {
			if (nodes[x][z].GetPosition() == position) {
				nodes[x][z].SetState(state);
				break;
			}
		}
	}
}

void GraphManager::GetConnectedNodesOn(Node node)
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

void GraphManager::CheckWin()
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
