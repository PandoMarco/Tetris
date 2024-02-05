#include <ncurses.h>
#include <string>
#include <cstring>
#include "visualizza_classifica.hpp"
using namespace std;

int main(){
   /* AVVIO NCURSES */
    initscr();
    noecho();
    cbreak();

    // dimensione dello schermo
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // creazione di una finestra per l'input
    WINDOW * menu = newwin(6, xMax-12, yMax-8, 5);
    refresh();
    
    box(menu, 0, 0);
    wrefresh(menu);

    // abilita l'uso delle frecce
    keypad(menu, true);

    string opzioni[2] = {"Nuova partita", "Visualizza classifica"}; // scelte del menù
    int scelta;
    int selezione = 0;

    // evidenzia l'opzione selezionata
    while(true){
        for(int i = 0; i < 2; i++){
            if(i == selezione){
                wattron(menu, A_REVERSE);
            }
            mvwprintw(menu, i+1, 1, opzioni[i].c_str());
            wattroff(menu, A_REVERSE);
        }
        scelta = wgetch(menu); // registra la scelta dell'utente

        switch(scelta){
            case KEY_UP:
                selezione--;
                if(selezione == -1)
                    selezione = 0;
                break;
            case KEY_DOWN:
                selezione++;
                if(selezione == 2)
                    selezione = 1;
                break;
            default:
                break;
        }
        if(scelta == 10){
            break;
        }
    }

 
    if(strcmp(opzioni[selezione].c_str(), "Nuova partita") == 0){
         Tetris tetr;
        clear();
        tetr.GameLoop();
    }
    else if (strcmp(opzioni[selezione].c_str(), "Visualizza classifica") == 0){
        clear();
        visualizza_classifica();
    }


    endwin();

    return 0;

}
