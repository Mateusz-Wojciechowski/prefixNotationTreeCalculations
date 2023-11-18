#include "CUserInterface.h"
#include "CTree.h"
#include "iostream"
#include "string"

using namespace std;

CUserInterface::CUserInterface() {
    CTree tree(" ");
    c_tree = tree;
}

void CUserInterface::vRun() {
    string s_full_command;
    string s_command;
    string s_operation;
    string s_current_prefix;
    bool b_exit = false;

    do{
        cout << "Enter command:  ";
        getline(cin, s_full_command);
        cout << endl;

        int i_space_pos = s_full_command.find(" ");

        s_command = s_full_command.substr(0, i_space_pos);
        s_operation = s_full_command.substr(i_space_pos + 1);

        if(s_command=="enter"){
            s_current_prefix = s_operation;
            CTree tree(s_operation);
            c_tree = tree;
        }

        if(s_command=="print"){
            cout << "Prefix notation: ";

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
            for(int i=0; i<s_operation.size(); i++){
                if(s_operation[i]!=' '){
                    values.push_back(string(1, s_operation[i]));
                }
            }
            c_tree.vSubstituteVariables(c_tree.getRoot(), values, 0);
            cout << c_tree.iCalculateTreeValue(c_tree.getRoot()) << endl;
        }

        if(s_command=="vars"){
            set<string> variables;
            variables = c_tree.vGetUniqueVariables(c_tree.getRoot(), variables);
            if(variables.size()==0){
                cout << "No variables in the tree" << endl;
            }

            else{
                set<string>::const_iterator it;
                for (it = variables.begin(); it != variables.end(); ++it) {
                    cout << *it << endl;
                }
            }
        }

        if(s_command=="exit"){
            b_exit = true;
        }
    }while(!b_exit);

}
