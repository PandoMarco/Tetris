#include <ncurses.h>
#include <string>
#include <fstream>
#include "visualizza_classifica.hpp"

using std::getline;
using std::ifstream;
using std::string;

void visualizza_classifica() {
    // Avvio ncurses
    initscr();
    noecho();
    refresh();

    int larghezza;
    const int MAX_RIGHE = 100;  // Numero massimo di righe da leggere
    string righe[MAX_RIGHE];  // Array per memorizzare le righe del file
    int num_righe = 0;  // Numero effettivo di righe lette

    num_righe = readFile("classifica.txt", righe, MAX_RIGHE, larghezza);

    WINDOW* win_classifica = newwin(num_righe + 2, larghezza + 2, 5, 15);
    box(win_classifica, 0, 0);

    for (int i = 0; i < num_righe; i++) {
        mvwprintw(win_classifica, i + 1, 1, righe[i].c_str());
    }

    wgetch(win_classifica);
    clear();
    menu();

    endwin();
}

// Funzione per leggere il file e memorizzare le righe in un array
int readFile(string nomefile, string righe[], int max_righe, int &larghezza_massima) {
    ifstream file(nomefile);
    string riga;
    int piu_lunga = 0;
    int num_righe = 0;

    while (getline(file, riga) && num_righe < max_righe) {
        righe[num_righe++] = riga;
        if (riga.length() > piu_lunga) {
            piu_lunga = riga.length();
        }
    }

    larghezza_massima = piu_lunga;

    return num_righe;
}
