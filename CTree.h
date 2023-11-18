#ifndef LAB3_TEP_CTREE_H
#define LAB3_TEP_CTREE_H

#include "CNode.h"
#include "COperation.h"
#include "string"
#include "iostream"
#include "vector"
#include "map"
#include "set"
using namespace std;

class CTree{
public:
    CTree(string s_prefix);
    CTree();
    CNode* vCreateTree(string s_prefix, int &i_index);
    bool bIsOperator(string s_expression);
    CNode* getRoot();
    void vPrintNode(CNode* c_node, int i_depth);
    void vPrintTree();
    int iCalculateTreeValue(CNode* c_node);
    int getOperandsNeeded(const string op);
    void vCreateMap();
    string sTreeToStr(CNode* c_node);
    set<string> vGetUniqueVariables(CNode* c_node, set<string>& variables);
    void vSubstituteVariables(CNode* c_node, vector<string> values, int &i_index);
    CNode* findLastLeaf(CNode* c_node);
    void vJoinTrees(CNode* c_new_root);
    bool bIsVariable(string s_value);
    bool bIsNum(string s_value);
    bool getWasChanged();

private:
    CNode* root;
    map<string, COperation> operations;
    bool b_was_changed;
};
#endif //LAB3_TEP_CTREE_H
