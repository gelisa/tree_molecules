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
    Node root = Node();
    root.doNothing();
    root.addNode(0);
    root.addNode(1);
    cout << root << endl;
    cout << * root.m_left << endl;
    cout << * root.m_right << endl;
    root.toSet();
    cout << *(root.m_tree) << endl;
    //assert(2+2==5);
    //std::cout << "Execution continues past the second assert\n";
    
    std::string s = "0,0 1,1 1,0 2,0 2,3 ";
    cout << stringToSet(s) << endl;
}        



