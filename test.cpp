#include <iostream>
// uncomment to disable assert()
// #define NDEBUG
#include <tuple>
#include <string>
#include <cassert>
#include "tree.h"

using namespace std;

int main()
{
//     Node root = Node();
//     root.doNothing();
//     root.addNode(0);
//     root.addNode(1);
//     cout << root << endl;
//     cout << * root.m_left << endl;
//     cout << * root.m_right << endl;
//     root.toSet();
//     cout << *(root.m_tree) << endl;
    
    std::string s = "0,0 1,1 1,0 2,0 2,3 3,0 3,1 3,6 3,7, 4,14 ";
    node_set theSet =  stringToSet(s);
    cout << theSet << endl;
    Node newNode = createFromSet(& theSet);
//     cout << "!!!\n";
//     Node* current = findNode(&newNode, 4, 14);
//     cout << * current << endl;
    cout << *(newNode.m_leafs) << endl;
}        



