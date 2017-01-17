#include <string>
#include <iostream>
#include "tree.h"
#include <cstdlib>

using namespace std;

void Node::addFromSet(Node*  parent, bi_tuple pair, node_set tree){//FIXME pointers?
    if (tree.empty()) return;
    bi_tuple leftPair = leftChild();
    bi_tuple rightPair = rightChild();
    if (tree.find(leftPair) != tree.end()){
        tree.erase(leftPair);
        parent.m_left = Node(&parent, 0);
        addFromSet(parent.m_left,make_tuple(parent.m_left.row,parent.m_left.column,tree);
    }
    if (tree.find(rightPair) != tree.end()){
        tree.erase(rightPair);
        parent.m_right = Node(&parent, 1);
        addFromSet(parent.m_right,make_tuple(parent.m_right.row,parent.m_right.column,tree);
    }
};

Node::Node(node_set tree){
    Node root = Node();
    addFromSet(&root,make_tuple(0,0),tree);
    return root;
}

Node::Node() : m_column(0), m_row(0), m_left(NULL), m_right(NULL), m_parent(NULL) {
    m_tree = new node_set;
};

Node::Node(Node * parent, int pos): m_left(NULL), m_right(NULL), m_parent(parent), m_tree(parent -> m_tree) {
    m_column = parent -> 2 * m_column + pos;
    m_row = parent -> m_row + 1;
};

Node::~Node(){
    if (m_left != NULL) {delete m_left;}
    if (m_right !=NULL) {delete m_right;}
    if (m_row == 0 && m_column == 0) {delete m_tree;}
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

void Node::toSet(){
    (* m_tree).insert(make_tuple(m_row, m_column));
    if (m_left != NULL) {(* m_left).toSet();}
    if (m_right != NULL) {(* m_right).toSet();}
}

bi_tuple Node::leftChild(){
    return make_tuple(m_row+1,2 * m_column);
}

bi_tuple Node::rightChild(){
    return make_tuple(m_row+1,2 * m_column+1);
}

//////////////////////////

string tupleToString(const bi_tuple& tp){
    std::ostringstream foo;
    foo << std::get<0>(tp) << "," << std::get<1>(tp);
    return foo.str();
}

std::ostream& operator<<(std::ostream& os, const bi_tuple& tp)
{
    os << std::get<0>(tp) << "," << std::get<1>(tp);
    //os << "x";
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const node_set& st){
    node_set::iterator iter;
    //cout<<st.size()<<endl;
    int ii=0;
    for(iter=st.begin(); iter!=st.end();++iter){
        //cout<<(*iter)<<endl;
        ii+=1;
        os<<(*iter)<<" ";
    }
    return os;
}

node_set stringToSet(string s){
    node_set result;
    std::istringstream iss(s);
    for(std::string s; iss >> s; ){
        int comma = s.find(",");
        int x = stoi(s.substr(0,comma));
        int y = stoi(s.substr(comma+1,s.length()-comma));
        result.insert(make_tuple(x,y));
    }
    return result;
}
