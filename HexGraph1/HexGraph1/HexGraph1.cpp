#include <iostream>
#include "GraphManager.h"
#include "Node.h"
#include <string>

int main()
{
    //short linear graph
    /*GraphManager manager = GraphManager(vector<Node>
        {
            Node(0, Vector3(0, 0, 0), true),
            Node(1, Vector3(1, 0, 0), false),
            Node(2, Vector3(2, 0, 0), false),
            Node(3, Vector3(3, 0, 0), false),
            Node(4, Vector3(4, 0, 0), false),
            Node(5, Vector3(5, 0, 0), false),
            Node(6, Vector3(6, 0, 0), false),
            Node(7, Vector3(0, 0, 1), false),
            Node(8, Vector3(1, 0, 1), false),
            Node(9, Vector3(2, 0, 1), false),
            Node(10, Vector3(3, 0, 1), false),
            Node(11, Vector3(4, 0, 1), false),
            Node(12, Vector3(5, 0, 1), false),
            Node(13, Vector3(6, 0, 1), true),
            Node(14, Vector3(0, 0, 2), false),
            Node(15, Vector3(1, 0, 2), false),
            Node(16, Vector3(2, 0, 2), false),
            Node(17, Vector3(3, 0, 2), false),
            Node(18, Vector3(4, 0, 2), false),
            Node(19, Vector3(5, 0, 2), false),
            Node(20, Vector3(6, 0, 2), false),
            Node(21, Vector3(0, 0, 3), false),
            Node(22, Vector3(1, 0, 3), false),
            Node(23, Vector3(2, 0, 3), true),
            Node(24, Vector3(3, 0, 3), false),
            Node(25, Vector3(4, 0, 3), false),
            Node(26, Vector3(5, 0, 3), false),
            Node(27, Vector3(6, 0, 3), false),
        }
    );*/

    GraphManager manager = GraphManager(Vector3(3, 0, 3), 0);

    //claim nodes
    cout << "node 0 0 " << manager.GetNodeByPosition(Vector3(2, 0, 0))->GetId() << endl;
    manager.ChangeStateOn(Vector3(0, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(1, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(2, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(0, 0, 1), Nodestate::Red);
    manager.ChangeStateOn(Vector3(1, 0, 1), Nodestate::Red);
    manager.ChangeStateOn(Vector3(2, 0, 1), Nodestate::Red);
    manager.ChangeStateOn(Vector3(0, 0, 2), Nodestate::Red);
    manager.ChangeStateOn(Vector3(1, 0, 2), Nodestate::Red);
    manager.ChangeStateOn(Vector3(2, 0, 2), Nodestate::Red);

    //show red claimed list
    //manager.ShowClaimedNodes(PlayerSide::RedPlayer);
    manager.ShowClaimedNodesConnections(PlayerSide::RedPlayer);

    //check win
    std::cout << "red win: " << manager.IsWinner(PlayerSide::RedPlayer) << endl;
    std::cout << "blue win: " << manager.IsWinner(PlayerSide::BluePlayer) << endl;

    //show node directions 
    /*for (int i = 0; i < s_nodeSides; i++) {
        Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], 0);
        std::cout << "even dir: " << dir.x << ", " << dir.z << endl;
    }

    for (int i = 0; i < s_nodeSides; i++) {
        Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], s_nodeXOffset);
        std::cout << "odd dir: " << dir.x << ", " << dir.z << endl;
    }*/
    std::cout << "win: " << to_string(manager.GetGameState());
    //std::cout << endl << "node offset: " << s_nodeDirections[1].z;
}
