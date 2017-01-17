#ifndef __NODE_H
#define __NODE_H

#include <tuple>
#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

typedef tuple<int,int> bi_tuple;
typedef set<bi_tuple> node_set;

class Node {
public:
    int m_row;
    int m_column;
    Node* m_left;
    Node *m_right;
    Node *m_parent;
    node_set* m_tree;
    //Node(tuple x) : index(x), left(NULL), right(NULL) {}
    Node();
    Node(node_set);
    Node(Node * parent, int pos);//pos 0 if left, pos 1 if right
    ~Node();
    void doNothing();
    void addNode(int pos);
    void toSet();
    bi_tuple leftChild();
    bi_tuple rightChild();
    void addFromSet(Node* parent, bi_tuple pair, node_set tree);
    friend std::ostream& operator<<(std::ostream& os, const Node& nd);
};

string tupleToString(const bi_tuple& tp);
std::ostream& operator<<(std::ostream& os, const bi_tuple& tp);
std::ostream& operator<<(std::ostream& os, const node_set& st);
node_set stringToSet(string s);
#endif // __NODE_H
