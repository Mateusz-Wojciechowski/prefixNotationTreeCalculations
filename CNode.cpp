#include "CNode.h"
#include "iostream"
#include "string"
#include "vector"
using namespace std;

CNode::CNode(string s_Value) {
    c_parent = NULL;
    s_value = s_Value;
}

CNode::CNode(string s_Value, CNode* parent){
    s_value = s_Value;
    c_parent = parent;
}

CNode::~CNode(){
    for(int i=0; i<c_children.size(); i++){
        delete c_children[i];
    }
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

void CNode::vReplaceNode(CNode *c_new_node){
    if(c_parent!=NULL){
        vector<CNode*>& children = c_parent->c_children;
        for(int i=0; i<c_parent->c_children.size(); i++){
            if(children[i]==this){
                children[i] = c_new_node;
            }
        }
    }

    c_new_node->c_parent = this->c_parent;
    delete this;
}

void CNode::setValue(string s_new_value){
    s_value = s_new_value;
}