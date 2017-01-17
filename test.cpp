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
    //std::tuple<int, int> x;
    //cout << "Execution continues past the first assert\n";
    //assert(2+2==5);
    //std::cout << "Execution continues past the second assert\n";
}
