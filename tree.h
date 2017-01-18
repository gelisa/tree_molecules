#ifndef __NODE_H
#define __NODE_H

#include <tuple>
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>

using namespace std;

typedef tuple<int,int> bi_tuple;
typedef set<bi_tuple> node_set;
typedef stack<bi_tuple> node_stack;

class Node {
public:
    int m_row;
    int m_column;
    Node* m_left;
    Node *m_right;
    Node *m_parent;
    node_set* m_tree;
    node_set* m_leafs;
    //Node(tuple x) : index(x), left(NULL), right(NULL) {}
    Node();
    Node(Node * parent, int pos);//pos 0 if left, pos 1 if right
    ~Node();
    void doNothing();
    void addNode(int pos);
    void toSet();
    bi_tuple leftChild();
    bi_tuple rightChild();
    void addFromSet(Node* node, bi_tuple pair, node_set* tree);
    friend std::ostream& operator<<(std::ostream& os, const Node& nd);
};

string tupleToString(const bi_tuple& tp);
std::ostream& operator<<(std::ostream& os, const bi_tuple& tp);
std::ostream& operator<<(std::ostream& os, const node_set& st);
node_set stringToSet(string s);
Node createFromSet(node_set* tree);
void findLineage(int row,int col,node_stack* nStack);
Node* findNode(Node* root, int row, int col);
#endif // __NODE_H
