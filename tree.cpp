#include <string>
#include <iostream>
#include "tree.h"
using namespace std;

Node::Node() : m_column(0), m_row(0), m_left(NULL), m_right(NULL), m_parent(NULL) {};

Node::Node(Node * parent, int pos): m_left(NULL), m_right(NULL), m_parent(parent) {
    m_column = parent -> m_column + pos;
    m_row = parent -> m_row + 1;
};

Node::~Node(){
    if (m_left != NULL) {delete m_left;}
    if (m_right !=NULL) {delete m_right;}
}

// // Overloading <<
std::ostream& operator<<(std::ostream& os, const Node& nd)
{
    os <<  nd.m_row << "," <<nd.m_column << endl; 
    //os << "x";
    
    return os;
}

void Node::doNothing(){
    cout << "Doing nothing" << endl;
}
    
void Node::addNode(int pos){
    if (pos == 0) {
        m_left = new Node(this, 0);
    }
    if (pos == 1) {
        m_right = new Node(this,1);
    }
}


