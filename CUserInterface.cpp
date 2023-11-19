#include "CUserInterface.h"
#include "CTree.h"
#include "CInterfaceConstants.h"
#include "iostream"
#include "string"
#include "sstream"
#include "cstdlib"

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
            s_operation = S_EMPTY_STRING;
        }
        else{
            s_command = s_full_command.substr(0, i_space_pos);
            s_operation = s_full_command.substr(i_space_pos + 1);
        }

        if(s_command==S_ENTER){
            s_current_prefix = s_operation;
            CTree tree(s_operation);
            c_tree = tree;
            string s_new_prefix = c_tree.sTreeToStr(c_tree.getRoot());
            if(s_current_prefix + S_SPACE != s_new_prefix){
                cout << S_TREE_CHANGED_COMM << endl;
                s_current_prefix = s_new_prefix;
                cout << s_current_prefix << endl;
            }
        }

        if(s_command==S_PRINT){
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

        if(s_command==S_COMP){
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
                map<string, int> variable_map;
                set<string>::const_iterator it;
                int i_iter = 0;
                for (it=variables.begin(); it!=variables.end(); it++) {
                    variable_map[*it] = atoi(values[i_iter].c_str());
                    i_iter++;
                }
                try{
                    int i_result = c_tree.iCalculateTreeValue(c_tree.getRoot(), variable_map);
                    cout << S_RESULT_COMM << S_SPACE << i_result;
                }
                catch(invalid_argument){
                    cout << S_DIVISION_BY_ZERO << endl;
                }
            }
        }

        if(s_command==S_VARS){
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

        if(s_command==S_JOIN){
            if(s_operation==S_SPACE){
                CTree c_second_tree(s_operation);
                CTree c_result_tree;
                c_result_tree = c_tree + c_second_tree;
                s_current_prefix = c_result_tree.sTreeToStr(c_result_tree.getRoot());
                cout << S_PREFIX_FORM_COMM << s_current_prefix << endl;
                c_tree = c_result_tree;
                c_result_tree.vPrintTree();
            }
        }

        if(s_command==S_EXIT){
            b_exit = true;
        }
    }while(!b_exit);

}
