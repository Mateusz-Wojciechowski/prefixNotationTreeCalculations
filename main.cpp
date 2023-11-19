#include <iostream>
#include "CTree.h"
#include "CUserInterface.h"
using namespace std;
int main() {
//    set<string> variables;
//    CTree c_tree("+ % 1");
//    CTree c_tree2("+ 4 5");
//    CTree c_result = c_tree + c_tree2;
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
    /// nalezy wykonac jeszcze pomijanie znakow specjalnych jesli znajduja sie w formule (done)
    /// zredukowac drzewo jesli wpisane jest na przyklad za duzo operandow (done)
    // destruktor musi usuwac noda a nie czysci tablice
    /// dodac obsluge dwucyfrowych liczb przy comp (done)
    /// sprawdzic czy nie jest wiecej danych niz zmiennych (done)
    /// comp ma nie zmieniac drzewa (done)
    /// pozmieniac ewentualne wartosci >2 na stale (done)
    // zmodyfikowac wypisywanie info o specjalnym znaku
}
