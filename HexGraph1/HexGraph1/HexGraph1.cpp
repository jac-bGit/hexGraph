#include <iostream>
#include "GraphManager.h"
#include "Node.h"
#include <string>

int main()
{

    GraphManager manager = GraphManager(Vector3(8, 0, 8), 0);

    //claim nodes
    cout << "node 0 0 " << manager.GetNodeByPosition(Vector3(2, 0, 0))->GetId() << endl;

    //red nodes
    manager.ChangeStateOn(Vector3(0, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(1, 0, 0), Nodestate::Red);
    manager.ChangeStateOn(Vector3(2, 0, 0), Nodestate::Red);

    std::cout << "red win: " << manager.IsWinner(PlayerSide::RedPlayer) << endl;

    manager.ChangeStateOn(Vector3(2, 0, 1), Nodestate::Red);
    manager.ChangeStateOn(Vector3(2, 0, 2), Nodestate::Red);
    manager.ChangeStateOn(Vector3(3, 0, 1), Nodestate::Red);
    manager.ChangeStateOn(Vector3(4, 0, 1), Nodestate::Red);

    std::cout << "red win: " << manager.IsWinner(PlayerSide::RedPlayer) << endl;

    manager.ChangeStateOn(Vector3(5, 0, 2), Nodestate::Red);
    manager.ChangeStateOn(Vector3(5, 0, 3), Nodestate::Red);
    manager.ChangeStateOn(Vector3(6, 0, 4), Nodestate::Red);
    manager.ChangeStateOn(Vector3(7, 0, 4), Nodestate::Red);

    std::cout << "red win: " << manager.IsWinner(PlayerSide::RedPlayer) << endl;
    

    manager.DefaultState();
    std::cout << "red win after restart: " << manager.IsWinner(PlayerSide::RedPlayer) << endl;

}
