#ifndef LAB3_TEP_CNODE_H
#define LAB3_TEP_CNODE_H

#include "string"
#include "iostream"
#include "vector"

using namespace std;

class CNode{
public:
    CNode(string s_Value);
    CNode(string s_Value, CNode* c_parent);
    ~CNode();
    void vRemoveChild(CNode* child);
    void vAdd(CNode* child);
    CNode* getParent() const;
    string getValue();
    vector<CNode*> getChildren();
    void vReplaceNode(CNode* c_new_node);
    void setValue(string s_new_value);
private:
    string s_value;
    CNode* c_parent;
    bool b_is_operator;
    vector<CNode*> c_children;
};
#endif //LAB3_TEP_CNODE_H
