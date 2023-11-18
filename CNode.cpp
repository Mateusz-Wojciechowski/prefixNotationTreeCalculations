#include "CNode.h"
#include "iostream"
#include "string"
#include "vector"
using namespace std;

// konstruktor do ustawiania roota
CNode::CNode(string s_Value) {
    c_parent = NULL;
    s_value = s_Value;
}

CNode::CNode(string s_Value, CNode* parent){
    s_value = s_Value;
    c_parent = parent;
}

CNode::~CNode(){
    if(c_parent!=NULL){
        c_parent->vRemoveChild(this);
    }
    c_parent = NULL;
}

void CNode::vRemoveChild(CNode *child){
    for(int i=0; i<c_children.size(); i++){
        if(c_children[i]==child){
            c_children.erase(c_children.begin()+i);
        }
    }
}

void CNode::vAdd(CNode *child){
    c_children.push_back(child);
    child->c_parent = this;
}

CNode* CNode::getParent() const {
    return c_parent;
}

string CNode::getValue(){
    return s_value;
}

vector<CNode*> CNode::getChildren() {
    return c_children;
}

void CNode::setValue(string s_new_value){
    s_value = s_new_value;
}