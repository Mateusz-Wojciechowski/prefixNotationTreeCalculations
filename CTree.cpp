#include "CTree.h"
#include "CNode.h"
#include "string"
#include "iostream"
#include "vector"
#include "cstdlib"
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
    root = vCreateTree(" ", i_index);
    vCreateMap();
}

CTree::~CTree(){
    vDeleteTree(root);
}

CNode* CTree::vCreateTree(string s_prefix, int &i_index){
    while (i_index < s_prefix.size() && s_prefix[i_index] == ' '){
        i_index++;
    }

    if (i_index >= s_prefix.size()){
        return NULL;
    }

    int i_start_index = i_index;
    while (i_index < s_prefix.size() && s_prefix[i_index] != ' '){
        i_index++;
    }

    string s_expression = s_prefix.substr(i_start_index, i_index - i_start_index);
    CNode* c_node = new CNode(s_expression);

    if (bIsOperator(s_expression)){
        int operandsNeeded = getOperandsNeeded(s_expression);
        for (int i = 0; i < operandsNeeded; i++){
            while (i_index < s_prefix.size() && s_prefix[i_index] == ' ') {
                i_index++;
            }
            if (i_index < s_prefix.size()){
                CNode* c_child = vCreateTree(s_prefix, i_index);
                if (c_child != NULL) {
                    c_node->vAdd(c_child);
                }
                else{
                    delete c_node;
                }
            }

            else{
                CNode* c_default = new CNode("1");
                c_node->vAdd(c_default);
                b_was_changed = true;
            }
        }
    }
    return c_node;
}

int CTree::getOperandsNeeded(const string op) {
    if(op=="+" || op=="-" || op=="*" || op=="/"){
        return 2;
    }

    if(op=="sin" || op=="cos"){
        return 1;
    }

    else return -1;
}

void CTree::vPrintTree() {
    vPrintNode(root, 0);
}

void CTree::vPrintNode(CNode* node, int i_depth) {
    if (node==NULL) {
        return;
    }

    std::string indent = std::string(i_depth * 2, ' ');
    std::cout << indent << node->getValue() << std::endl;

    for (int i=0; i<node->getChildren().size(); i++) {
        vPrintNode(node->getChildren()[i], i_depth + 1);
    }
}

int CTree::iCalculateTreeValue(CNode *c_node){
    if (c_node == NULL) {
        return 0;
    }

    if (c_node->getChildren().empty()) {
        return atoi(c_node->getValue().c_str());
    }

    vector<int> results;

    const vector<CNode*>& children = c_node->getChildren();
    for (vector<CNode*>::const_iterator it = children.begin(); it != children.end(); ++it) {
        results.push_back(iCalculateTreeValue(*it));
    }

    std::map<std::string, COperation>::iterator op_it = operations.find(c_node->getValue());

    return op_it->second.execute(results);
}

void CTree::vCreateMap(){
    operations.insert(make_pair(string("+"), COperation(COperation::i_add)));
    operations.insert(make_pair(string("-"), COperation(COperation::i_sub)));
    operations.insert(make_pair(string("*"), COperation(COperation::i_mul)));
    operations.insert(make_pair(string("/"), COperation(COperation::i_div)));
    operations.insert(make_pair(string("sin"), COperation(COperation::i_sin)));
    operations.insert(make_pair(string("cos"), COperation(COperation::i_cos)));
}

set<string> CTree::vGetUniqueVariables(CNode *c_node, set<string>& variables){
    if(c_node==NULL){
        return variables;
    }

    string value = c_node->getValue();
    if(bIsVariable(c_node->getValue())){
        variables.insert(value);
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
        return "";
    }

    string result = c_node->getValue() + " ";

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
            cout << "Not enough values" << endl;
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
        vDeleteTree(root);
        root = copyTree(c_other.root);
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
    return !bIsOperator(s_value) && !bIsNum(s_value);
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
   return s_expression=="+" || s_expression=="-" || s_expression=="*" || s_expression=="/" || s_expression=="sin" || s_expression=="cos";
}

CNode* CTree::getRoot(){
    return root;
}

bool CTree::getWasChanged(){
    return b_was_changed;
}


