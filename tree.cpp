#include <string>
#include <iostream>
#include "tree.h"
#include <cstdlib>

using namespace std;




Node::Node() : m_column(0), m_row(0), m_left(NULL), m_right(NULL), m_parent(NULL) {
    m_tree = new node_set;
    m_leafs = new node_set;
};

Node::Node(Node * parent, int pos): m_left(NULL), m_right(NULL), m_parent(parent), m_tree(parent -> m_tree), m_leafs(parent -> m_leafs) {
    m_column = 2 * (parent -> m_column) + pos;
    m_row = parent -> m_row + 1;
};

Node::~Node(){
    if (m_left != NULL) {delete m_left;}
    if (m_right !=NULL) {delete m_right;}
    if (m_row == 0 && m_column == 0) {
        delete m_tree;
        delete m_leafs;
    }
}

// // Overloading <<
std::ostream& operator<<(std::ostream& os, const Node& nd)
{
    os <<  nd.m_row << "," <<nd.m_column; 
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
    else {
        bi_tuple leaf = make_tuple(
        (this -> m_row) + 1, 2 * (this -> m_column));
        cout << "this " << * this << " wt leaf " << leaf << endl;
        (* m_leafs).insert(leaf);        
    }
    if (m_right != NULL) {(* m_right).toSet();}
    else {
        bi_tuple leaf = make_tuple(
        (this -> m_row) + 1, 2 * (this -> m_column) + 1);
        cout << "this " << * this << " wt leaf " << leaf << endl;
        (* m_leafs).insert(leaf); 
    }
}

bi_tuple Node::leftChild(){
    return make_tuple(m_row+1,2 * m_column);
}

bi_tuple Node::rightChild(){
    return make_tuple(m_row+1,2 * m_column+1);
}

void Node::addFromSet(Node* node, bi_tuple pair, node_set* tree){//Simingly fixed
    //cout << "function addFromSet of " << node << " indexed " << pair << endl;
    //cout << "set is " << * tree << endl;
    tree -> erase(make_tuple(node -> m_row, node -> m_column));
    if ((*tree).empty()) return;
    bi_tuple leftChildIndex = node -> leftChild();
    bi_tuple rightChildIndex = node -> rightChild();
    //cout << "childred " << leftChildIndex << " " << rightChildIndex << endl;
    //cout << "before searhing for left child of " << node << endl;
    if (tree -> find(leftChildIndex) != (*tree).end()){
        //cout << "found left of " << node << endl;
        node -> addNode(0);
        //cout << "node added " << *(node -> m_left) << endl;
        node -> addFromSet(node -> m_left,make_tuple(node -> m_left -> m_row,node -> m_left -> m_column),tree);
     }
    //cout << "before searhing for right child of " << node << endl;
    if (tree -> find(rightChildIndex) != (*tree).end()){
        //cout << "found right of " << node << endl;
        node -> addNode(1);
        //cout << "node added " << *(node -> m_right) << endl;
        node -> addFromSet(node -> m_right,make_tuple(node -> m_right -> m_row,node -> m_right -> m_column),tree);
     }   
};


// Node* Node::accessChild(bi_tuple childIndex){
//     
// }

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




///////////////////////////////////////////////////////////
/*
 * HERE FUNCTIONS FOR WORKING WITH MOLECULAR TREES
 * 
 */
///////////////////////////////////////////////////////////

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


Node createFromSet(node_set* tree){
    Node root = Node();
    root.addFromSet(&root, make_tuple(0,0),tree);
    root.toSet();
    return root;
}

void findLineage(int row,int col,node_stack* nStack){
    nStack -> push(make_tuple(row,col));
    if (row == 0 && col == 0) return;
    findLineage(row-1,col/2,nStack);
    
}

Node* findNode(Node* root, int row, int col){
    node_stack nStack;
    findLineage(row, col, &nStack);
    bi_tuple root_tuple = nStack.top();
    if (root_tuple != make_tuple(0,0)){
        throw runtime_error("Stack must have root node");
    }
    Node* current = root;
    nStack.pop();
    while (!nStack.empty()){
        bi_tuple tp = nStack.top();
        //cout << "current node " << *current << endl;
        //cout << "current tuple " << tp << endl;
        if (get<0>(tp) != current -> m_row + 1){
            //cout << "tuple " << tp << " " << current -> m_row << endl;
            throw runtime_error("wrong daughter row");
        }
        else if (get<1>(tp) == (current -> m_column) * 2 + 1){
            //cout << *current << " and " << get<1>(tp) << " ?\n";
            current = current -> m_right;
        }
        else if (get<1>(tp) == (current -> m_column) * 2 ){
            //cout << *current << " and " << get<1>(tp) << " ??\n";
            //cout << *(current -> m_left) << " and \n";
            current = current -> m_left;
            //cout << "cool?\n";
        }
        else {
            throw runtime_error("wrong daughter col");
        }
        //cout << "still cool?\n";  
        nStack.pop();
        //cout << "current is " << *current << endl;
    }
    return current;
}


