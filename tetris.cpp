
#include "tetris.h"
#include <ncurses.h>
#include <iostream>
#include "visualizza_classifica.hpp"
#include "visualizza_classifica.hpp"
#include "punteggio.hpp"
#include "menu.hpp"

Tetris::Tetris(){
    // genera il primo tetramino
    currentPiece = Tetramino::generaPezzoRandom();
    // genera il secondo tetramino
    nextPiece = Tetramino::generaPezzoRandom();
    score=0;
    full=0;
    //imposto la posizione iniziale del tetramino
    X=BOARD_WIDTH/2 -2; //vado nella meta'
    Y=0;

    srand(time(0));
}

//inizializza tutto lo schermo
void Tetris::schermo() {
    move(1, 30);
    printw("FULL LINES:");
    move(2, 30);
    printw("SCORE:");
    move(1,50);
    printw("COMMANDS:");
    move(2,50);
    printw("<- and -> to move");
    move(3,50);
    printw("A and S to rotate");
    move(4,50);
    printw("down arrow to hard drop");

    move(4,30);
    printw("upnext");
    refresh();

}

//mi cancella e scrive su upnext
void Tetris::upnext_stampa(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            move((6+j), 30+i*2);
            printw("  ");
        }
    }
    int tmp[4][4];
    nextPiece->scriviPezzo(tmp);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(tmp[i][j]!=0){
                move(6+j, 30+i*2);
                printw("[]");
            }
        }
    }
}


//pulisce lo schermo prima di riscriverci sopra
void Tetris::pulisci(){
    for(int i=0; i<BOARD_WIDTH*2+4; i++){
        for(int j=0; j < BOARD_HEIGHT; j++){
            move(j, i);
            printw("  ");
        }
    }
}


//funzione che mi disegna tutte le cose necessarie per il gioco
void Tetris::disegna() {
    pulisci();
    // disegna il bordo del gioco
    for (int i = 0; i <= BOARD_WIDTH * 2; i++) {
        mvprintw(BOARD_HEIGHT, i, "-");
    }
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        mvprintw(i, BOARD_WIDTH * 2, "|");
    }


    for (int i = 0; i < BOARD_WIDTH; ++i) {
        for (int j = 0; j < BOARD_HEIGHT; ++j) {
            if (board[i][j] != 0) {
                mvprintw(j, i * 2, "[]");
            }
        }
    }

    int tmp[4][4];
    currentPiece->scriviPezzo(tmp);

    // disegna il nostro pezzo
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tmp[i][j] != 0) {
                mvprintw(Y + j, (X + i) * 2, "[]");
            }
        }
    }

    // scrive lo score e le linee piene
    move(2, 30 + sizeof("SCORE:"));
    printw("%d", score);
    move(1, 30 + sizeof("FULL LINES:"));
    printw("%d", full);
    schermo();
    refresh();
}

//mi rileva una collisione e mi restituisce true se c'e'
bool Tetris::collisione(Tetramino* pezzo){
    int tmp[4][4];
    pezzo->scriviPezzo(tmp);
    bool coll=false;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(tmp[i][j] != 0){
                int x1=X+i;
                int y1=Y+j;

                // per ogni blocco, se rileva una collisione assegna a coll true
                if(x1<0 || x1>=BOARD_WIDTH || y1>=BOARD_HEIGHT || board[x1][y1]!=0){
                    coll=true;
                }
            }
        }
    }
    return coll;
}

void Tetris::check_complete(){
    int linee = 0;
    //mi controlla se ci sono linee complete
    for (int j = 0; j < BOARD_HEIGHT; j++) {
        bool lineaCompleta = true;
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (board[i][j] == 0) {
                lineaCompleta = false;
            }
        }
        if (lineaCompleta) {
            linee++;
            full++;
            for (int k = j; k > 0; k--) {
                for (int i = 0; i < BOARD_WIDTH; i++) {
                    board[i][k] = board[i][k - 1];

                }
            }

            //da chiamare la funzione del punteggio!!
        }
    }
    if (linee >= 4)
        score += 800;
    else
        score += linee * 100;
}

//controlla se in cima e' occupato
bool Tetris::prima_linea(){
    bool clean = true;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (board[i][0] == 1) {
            clean = false;
        }
    }
    return clean;
}

void Tetris::mettiPezzo(){
    int tmp[4][4];
    currentPiece->scriviPezzo(tmp);
    //aggiunge al blocco "fisso"
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(tmp[i][j] != 0) {
                int x1=X+i;
                int y1=Y+j;
                board[x1][y1]=1;
            }
        }
    }
    check_complete();

    //assegno il pezzo upnext trovato a quello attuale
    currentPiece = nextPiece;

    //genero il prossimo pezzo
    nextPiece = Tetramino::generaPezzoRandom();

    upnext_stampa();

    //resetto la posizione del tetramino
    X=BOARD_WIDTH/2 -2;
    Y=0;
    if(!prima_linea()){
        clear();
        move(0,0);
        printw("SCORE: %d", score);
        int gameover[11][20]={
                {0,1,1,1,0,0,1,1,1,0,1,0,0,0,1,0,1,1,1,1},
                {1,0,0,0,0,1,0,0,1,0,1,1,0,1,1,0,1,0,0,0},
                {1,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0},
                {1,1,1,1,0,1,0,0,1,0,1,0,0,0,1,0,1,1,1,1},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,0,0,1,0,0,0,1,0,1,1,1,1,0,1,1,1,0},
                {1,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1},
                {1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,0,1,1,1,1},
                {1,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,1,0,1,0},
                {0,1,1,1,0,0,0,1,0,0,0,1,1,1,1,0,1,0,0,1}
        };
        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < 20; ++j) {
                if (gameover[i][j] != 0) {
                    mvprintw((5+i), 5+(j*2), "[]");
                }
            }
        }
        refresh();
        while(getch()!='q'){
            //loop
        }
        //std::cout<<"gameover";
        salva_punteggio(score);
        clear();
        visualizza_classifica();
        while(getch()!='q'){
            //loop
        }
        clear();
        menu();
    }
}

void Tetris::mvright(){

    X++;
    if(collisione(currentPiece)){
        X--;
    }
}
void Tetris::mvleft(){
    X--;
    if(collisione(currentPiece)){
        X++;
    }
}
void Tetris::mvdown(){
    Y++;
    if(collisione(currentPiece)){
        Y--;
        mettiPezzo();
        //se raggiungo la fine allora devo piazzare il tetramino
    }
}

[[noreturn]] void Tetris::GameLoop(){
    //funzioni per lo schermo


    upnext_stampa();

    //loop del gioco
    while (true) {
        schermo();
        int t1=time(NULL);
        int t2=time(NULL);
        while(t2-t1<1){
            getmv();
            disegna();
            t2=time(NULL);
        }
        mvdown();

    }
}

void Tetris::getmv(){
    int userInput = getch();
    switch (userInput) {
        case KEY_DOWN: {
            mvdown();
            score++;
            break;
        }
        case KEY_LEFT: {
            mvleft();
            break;
        }
        case KEY_RIGHT: {
            mvright();
            break;
        }
        case 'a': {
            ruota(true);
            break;
        }
        case 's': {
            ruota(false);
            break;
        }
        case 'q': {
            endwin();
            exit(0);
        }
        default: {
            break;
        }
    }
}

void Tetris::ruota(bool orario) {
    auto copiaRuotata = currentPiece->creaCopiaRuotata(orario);
    // Se non collide, sostituisci il pezzo attuale con la copia ruotata
    if (!collisione(copiaRuotata)) {
        currentPiece = copiaRuotata;
    }
}
