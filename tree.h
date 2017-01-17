#ifndef __NODE_H
#define __NODE_H

#include <tuple>
#include <iostream>
#include <string>
#include <set>

using namespace std;

//typedef tuple<int,int> bi_tuple;

class Node {
public:
    int m_row;
    int m_column;
    Node *m_left;
    Node *m_right;
    Node *m_parent;
    //Node(tuple x) : index(x), left(NULL), right(NULL) {}
    Node();
    Node(Node * parent, int pos);//pos 0 if left, pos 1 if right
    ~Node();
    void doNothing();
    void addNode(int pos);
    
    friend std::ostream& operator<<(std::ostream& os, const Node& nd);
};



#endif // __NODE_H
