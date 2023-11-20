#include "CTree.h"
#include "CNode.h"
#include "CConstantsTree.h"
#include "string"
#include "iostream"
#include "vector"
#include "cstdlib"
#include "cctype"
using namespace std;

CTree::CTree(string s_prefix){
    b_was_changed = false;
    int i_index = 0;
    root = vCreateTree(s_prefix, i_index);
    vCreateMap();
}

CTree::CTree(){
    b_was_changed = false;
    int i_index = 0;
    root = vCreateTree(S_SPACE, i_index);
    vCreateMap();
}

CTree::~CTree(){
    delete root;
}

CNode* CTree::vCreateTree(string s_prefix, int &i_index){
    while (i_index < s_prefix.size() && s_prefix[i_index] == C_SPACE){
        i_index++;
    }

    if (i_index >= s_prefix.size()){
        return NULL;
    }

    int i_start_index = i_index;
    while (i_index < s_prefix.size() && s_prefix[i_index] != C_SPACE){
        i_index++;
    }

    string s_expression = s_prefix.substr(i_start_index, i_index - i_start_index);

    if (!bIsOperator(s_expression) && !bIsVariable(s_expression) && !bIsNum(s_expression)) {
        cout << S_INVALID_VALUE_COMM << s_expression << endl;
        b_was_changed = true;
        return vCreateTree(s_prefix, i_index);
    }

    CNode* c_node = new CNode(s_expression);


    if (bIsOperator(s_expression)){
        int operandsNeeded = getOperandsNeeded(s_expression);
        for (int i = 0; i < operandsNeeded; i++){
            CNode* c_child = NULL;

            while (i_index < s_prefix.size() && s_prefix[i_index] == C_SPACE) {
                i_index++;
            }

            if (i_index < s_prefix.size()){
                c_child = vCreateTree(s_prefix, i_index);
            }

            if (c_child == NULL) {
                c_child = new CNode(S_DEFAULT_NODE_VALUE);
                b_was_changed = true;
            }

            c_node->vAdd(c_child);
        }
    }

    return c_node;
}

int CTree::getOperandsNeeded(const string op) {
    if(op==S_PLUS || op==S_SUB || op==S_MUL || op==S_DIV){
        return I_BINARY_OP_ARGS;
    }

    if(op==S_SIN || op==S_COS){
        return I_SINGLE_OP_ARGS;
    }

    else return I_OP_NOT_FOUND;
}

void CTree::vPrintTree() {
    vPrintNode(root, 0);
}

void CTree::vPrintNode(CNode* node, int i_depth) {
    if (node==NULL) {
        return;
    }

    string indent = string(i_depth * I_PRINTING_OFFSET, C_SPACE);
    cout << indent << node->getValue() << endl;

    for (int i=0; i<node->getChildren().size(); i++) {
        vPrintNode(node->getChildren()[i], i_depth + 1);
    }
}

int CTree::iCalculateTreeValue(CNode *c_node, const map<string, int> &variables){
    if (c_node == NULL) {
        return 0;
    }

    if (c_node->getChildren().empty()){
        if (bIsVariable(c_node->getValue())){
            map<std::string, int>::const_iterator varIt = variables.find(c_node->getValue());
            if (varIt != variables.end()){
                return varIt->second;
            }
        }
        return atoi(c_node->getValue().c_str());
    }

    vector<int> results;

    const vector<CNode*>& children = c_node->getChildren();
    for (vector<CNode*>::const_iterator it = children.begin(); it != children.end(); ++it) {
        results.push_back(iCalculateTreeValue(*it, variables));
    }


    if(c_node->getValue()==S_DIV && results[1]==0){
        throw invalid_argument(S_DIVISION_BY_ZERO_COMM);
    }

    else{
        map<string, COperation>::const_iterator op_it = operations.find(c_node->getValue());
        return op_it->second.execute(results);
    }

}

void CTree::vCreateMap(){
    operations.insert(make_pair(string(S_PLUS), COperation(COperation::i_add)));
    operations.insert(make_pair(string(S_SUB), COperation(COperation::i_sub)));
    operations.insert(make_pair(string(S_MUL), COperation(COperation::i_mul)));
    operations.insert(make_pair(string(S_DIV), COperation(COperation::i_div)));
    operations.insert(make_pair(string(S_SIN), COperation(COperation::i_sin)));
    operations.insert(make_pair(string(S_COS), COperation(COperation::i_cos)));
}

set<string> CTree::vGetUniqueVariables(CNode *c_node, set<string>& variables){
    if(c_node==NULL){
        return variables;
    }

    string s_value = c_node->getValue();
    if(bIsVariable(c_node->getValue())){
        variables.insert(s_value);
    }

    vector<CNode*> children = c_node->getChildren();

    for(int i=0; i<children.size(); i++){
        vGetUniqueVariables(children[i], variables);
    }

    return variables;
}

string CTree::sTreeToStr(CNode *c_node){
    b_was_changed = false;
    if(c_node==NULL){
        return S_EMPTY_STRING;
    }

    string result = c_node->getValue() + S_SPACE;

    const vector<CNode*>& children = c_node->getChildren();
    for(int i=0; i<children.size(); i++){
        result += sTreeToStr(children[i]);
    }
    return result;
}

void CTree::vSubstituteVariables(CNode *c_node, vector<string> values, int &i_index){
    if(c_node==NULL){
        return;
    }

    if(bIsVariable(c_node->getValue())){
        b_was_changed = true;
        if(i_index<values.size()){
            c_node->setValue(values[i_index]);
            i_index++;
        }
        else{
            cout << S_NOT_ENOUGH_VALUES_COMM << endl;
            return;
        }
    }

    vector<CNode*> children = c_node->getChildren();
    for(int i=0; i<children.size(); i++){
        vSubstituteVariables(children[i], values, i_index);
    }
}

CNode* CTree::findLastLeaf(CNode *c_node){
    if(c_node==NULL){
        return NULL;
    }

    if(c_node->getChildren().empty()){
        return c_node;
    }

    vector<CNode*> children = c_node->getChildren();
    return findLastLeaf(children.back());
}

void CTree::vJoinTrees(CNode* c_new_root){
    CNode* leaf = findLastLeaf(root);
    if(leaf!=NULL){
        leaf->vReplaceNode(c_new_root);
    }
}

void CTree::vDeleteTree(CNode *c_node){
    if(c_node==NULL){
        return;
    }

    const vector<CNode*>& children = c_node->getChildren();
    for(int i=0; i<children.size(); i++){
        vDeleteTree(children[i]);
    }
    delete c_node;
}

CNode* CTree::copyTree(CNode *c_node){
    if(c_node==NULL){
        return NULL;
    }

    CNode* c_new_node = new CNode(c_node->getValue());
    const vector<CNode*>& children = c_node->getChildren();

    for(int i=0; i<children.size(); i++){
        c_new_node->vAdd(copyTree(children[i]));
    }
    return c_new_node;
}

CTree& CTree::operator=(const CTree &c_other){
    if(this!=&c_other){
        root = copyTree(c_other.root);
        b_was_changed = c_other.b_was_changed;
        operations = c_other.operations;
    }

    return *this;
}

CTree CTree::operator+(const CTree &c_other){
    CTree c_result;
    c_result.root = copyTree(this->root);

    CNode* c_second_root = copyTree(c_other.root);
    c_result.vJoinTrees(c_second_root);

    return c_result;
}

bool CTree::bIsVariable(string s_value){
    if(!bIsOperator(s_value) && !bIsNum(s_value)){

        for(int i=0; i<s_value.size(); i++){
            if(isalpha(s_value[i])){
                return true;
            }
        }
    }

    return false;
}

bool CTree::bIsNum(string s_value){
    for (int i = 0; i < s_value.size(); i++){
        if (!isdigit(s_value[i])) {
            return false;
        }
    }
    return true;
}

bool CTree::bIsOperator(string s_expression) {
   return s_expression==S_PLUS || s_expression==S_SUB || s_expression==S_MUL || s_expression==S_DIV || s_expression==S_SIN || s_expression==S_COS;
}

CNode* CTree::getRoot(){
    return root;
}

bool CTree::getWasChanged(){
    return b_was_changed;
}


