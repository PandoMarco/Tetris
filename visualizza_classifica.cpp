#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include "visualizza_classifica.hpp"

using std::getline;
using std::ifstream;
using std::string;
using std::vector;



void visualizza_classifica(){

    /* AVVIO NCURSES*/
    initscr();
    noecho();
    refresh();

    int larghezza;
    vector<string> righe = readFile("classifica.txt", larghezza);

    WINDOW* win_classifica = newwin(righe.size() + 2, larghezza + 2, 5, 15);
    box(win_classifica, 0, 0);

    for(int i = 0; i < righe.size(); i++){
        mvwprintw(win_classifica, i+1, 1, righe[i].c_str());
    }

    wgetch(win_classifica);

    endwin();


}

vector<string> readFile(string nomefile, int &larghezza_massima){

    ifstream file(nomefile);
    vector<string> righe;
    string riga;
    int piu_lunga = 0;

    while (getline(file, riga))
    {
        righe.push_back(riga);
        if(riga.length() > piu_lunga){

            piu_lunga = riga.length();
        }
    }

    larghezza_massima = piu_lunga;

    return righe;
}