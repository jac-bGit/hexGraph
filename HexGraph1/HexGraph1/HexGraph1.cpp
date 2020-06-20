#include <iostream>
#include "GraphManager.h"
#include "Node.h"
#include <string>

int main()
{
    //short linear graph
    GraphManager manager = GraphManager(vector<vector<Node>>{ 
        {
            Node(0, Vector3(0, 0, 0), true),
            Node(1, Vector3(1, 0, 0), false),
            Node(2, Vector3(2, 0, 0), false),
            Node(3, Vector3(3, 0, 0), false),
            Node(4, Vector3(0, 0, 1), false),
            Node(5, Vector3(1, 0, 1), false),
            Node(6, Vector3(2, 0, 1), false),
            Node(7, Vector3(3, 0, 1), true)
        },
    });

    //claim nodes
    manager.ChangeStateOn(Vector3(0, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(1, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(2, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(3, 0, 0), Nodestate::Red);

    //check win
    //manager.CheckWin();

    //show node directions 
    for (int i = 0; i < s_nodeSides; i++) {
        Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], 0);
        std::cout << "even dir: " << dir.x << ", " << dir.z << endl;
    }

    for (int i = 0; i < s_nodeSides; i++) {
        Vector3 dir = NormalizeDirection2D(s_nodeDirections[i], s_nodeXOffset);
        std::cout << "odd dir: " << dir.x << ", " << dir.z << endl;
    }

    std::cout << "win: " << to_string(manager.GetGameState());
    //std::cout << endl << "node offset: " << s_nodeDirections[1].z;
}
