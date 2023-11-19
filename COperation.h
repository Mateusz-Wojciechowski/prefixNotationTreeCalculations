#ifndef LAB3_TEP_COPERATION_H
#define LAB3_TEP_COPERATION_H
#include "vector"
using namespace std;

typedef int(*OperationFunction)(const vector<int>&);

class COperation{
public:
    COperation(OperationFunction op_Fun);
    int execute(const vector<int>& operands)const;
    static int i_add(const vector<int>& operands);
    static int i_sub(const vector<int>& operands);
    static int i_mul(const vector<int>& operands);
    static int i_div(const vector<int>& operands);
    static int i_sin(const vector<int>& operands);
    static int i_cos(const vector<int >& operands);
    OperationFunction getOpFunction();

private:
    OperationFunction op_fun;
};

#endif //LAB3_TEP_COPERATION_H
