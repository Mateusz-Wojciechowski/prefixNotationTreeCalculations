#include <iostream>
#include "CTree.h"
#include "CUserInterface.h"
using namespace std;
int main() {
//    set<string> variables;
//    CTree c_tree("+ * 1 2 a");
//    variables = c_tree.vGetUniqueVariables(c_tree.getRoot(), variables);
//    set<string>::const_iterator it;
//    for (it = variables.begin(); it != variables.end(); ++it) {
//        cout << *it << endl;
//    }

    CUserInterface c_ui;
    c_ui.vRun();

    // + sin 0 8
    /// metoda tworzenia drzewa powinna ustawiac flage czy wyrazenie zostalo zmienione (done)
    /// i uwzglednic to potem przy enter (done)
    /// przydalby sie enum w ktorym beda zapisane operatory i odpowiadajace im wagi (done bez enuma)
    // trzeba pamietac o dodaniu destruktorow np w CTree
    /// jakos trzeba obsluzyc liczby ujemne (done)
    /// trzeba ustawic zeby po zmianie przez comp print wyswietlal odpowiednie drzewo (done)
    /// sprawdzic czy przy comp zostalo podane wystarczajaco wartosci do podstawienia pod zmienne (done)
    // nalezy wykonac jeszcze pomijanie znakow specjalnych jesli znajduja sie w formule
    // zredukowac drzewo jesli wpisane jest na przyklad za duzo operandow
}
