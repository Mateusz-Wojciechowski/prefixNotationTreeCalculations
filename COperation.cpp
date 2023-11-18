#include "COperation.h"
#include "vector"
#include "cmath"

using namespace std;

COperation::COperation(OperationFunction op_Fun){
    op_fun = op_Fun;
}

int COperation::execute(const vector<int> &operands){
    return op_fun(operands);
}

int COperation::i_add(const vector<int> &operands) {
    return operands[0] + operands[1];
}

int COperation::i_sub(const vector<int> &operands){
    return operands[0] - operands[1];
}

int COperation::i_mul(const vector<int> &operands){
    return operands[0] * operands[1];
}

int COperation::i_div(const vector<int> &operands){
    if(operands[1]==0){
        throw exception();
    }
    return operands[0]/operands[1];
}

int COperation::i_sin(const vector<int> &operands){
    return sin(operands[0]*M_PI/180);
}

int COperation::i_cos(const vector<int> &operands){
    return cos(operands[0]*M_PI/180);
}