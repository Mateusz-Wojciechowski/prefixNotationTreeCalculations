#include "CUserInterface.h"
#include "CTree.h"
#include "CInterfaceConstants.h"
#include "iostream"
#include "string"
#include "sstream"

using namespace std;

CUserInterface::CUserInterface() {
    CTree tree(S_SPACE);
    c_tree = tree;
}

void CUserInterface::vRun() {
    string s_full_command;
    string s_command;
    string s_operation;
    string s_current_prefix;
    bool b_exit = false;

    do{
        cout << S_ENTER_COMMAND;
        getline(cin, s_full_command);
        cout << endl;

        int i_space_pos = s_full_command.find(S_SPACE);

        if(i_space_pos==-1){
            s_command = s_full_command.substr(0);
            s_operation = "";
        }
        else{
            s_command = s_full_command.substr(0, i_space_pos);
            s_operation = s_full_command.substr(i_space_pos + 1);
        }

        if(s_command=="enter"){
            s_current_prefix = s_operation;
            CTree tree(s_operation);
            c_tree = tree;
            if(c_tree.getWasChanged()){
                cout << S_TREE_CHANGED_COMM << endl;
                s_current_prefix = c_tree.sTreeToStr(c_tree.getRoot());
                cout << s_current_prefix << endl;
            }
        }

        if(s_command=="print"){
            cout << S_PREFIX_FORM_COMM;

            if(c_tree.getWasChanged()){
                s_current_prefix = c_tree.sTreeToStr(c_tree.getRoot());
                cout << s_current_prefix << endl;
            }
            else{
                cout << s_current_prefix << endl;
                cout << endl;
            }

            c_tree.vPrintTree();
        }

        if(s_command=="comp"){
            vector<string> values;

            istringstream iss(s_operation);
            string token;

            while(iss >> token){
                values.push_back(token);
            }

            set<string> variables;
            variables = c_tree.vGetUniqueVariables(c_tree.getRoot(), variables);

            if(values.size()<variables.size()){
                cout << S_NOT_ENOUGH_VALUES_COMM << endl;
            }

            else if(values.size()>variables.size()){
                cout << S_TOO_MANY_VALUES_COMM << endl;
            }

            else{
                int i_index = 0;
                cout << S_RESULT_COMM << c_tree.iCalculateTreeValue(c_tree.getRoot(), i_index, values) << endl;
            }
        }

        if(s_command=="vars"){
            set<string> variables;
            variables = c_tree.vGetUniqueVariables(c_tree.getRoot(), variables);
            if(variables.size()==0){
                cout << S_NO_VARIABLES_IN_TREE_COMM << endl;
            }

            else{
                set<string>::const_iterator it;
                for (it = variables.begin(); it != variables.end(); ++it) {
                    cout << *it << endl;
                }
            }
        }

        if(s_command=="join"){
            CTree c_second_tree(s_operation);
            CTree c_result_tree;
            c_result_tree = c_tree + c_second_tree;
            s_current_prefix = c_result_tree.sTreeToStr(c_result_tree.getRoot());
            cout << S_PREFIX_FORM_COMM << s_current_prefix << endl;
            c_tree = c_result_tree;
            c_result_tree.vPrintTree();
        }

        if(s_command=="exit"){
            b_exit = true;
        }
    }while(!b_exit);

}
