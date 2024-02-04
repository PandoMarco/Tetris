//
// Created by puzzoz on 2/3/24.
//

#ifndef TETRIS_DEF_TETRIS_H
#define TETRIS_DEF_TETRIS_H
#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#endif //TETRIS_DEF_TETRIS_H

class Tetris {
protected:
    const int BOARD_WIDTH = 10;
    const int BOARD_HEIGHT = 20;
    int score;
    int board[10][20]={0};
    int currentPiece[4][4];
    int nextPiece[4][4];
    int X, Y;
    int full;

public:
    Tetris(){
        score=0;
        full=0;
        //imposto la posizione iniziale del tetramino
        X=BOARD_WIDTH/2 -2; //vado nella meta'
        Y=0;

        srand(time(0));
    }

    //inizializza tutto lo schermo
    void schermo(){
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
    void upnext_stampa(){
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                move((6+j), 30+i*2);
                printw("  ");
                }
            }
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(nextPiece[i][j]!=0){
                    move(6+j, 30+i*2);
                    printw("[]");
                }
            }
        }
    }

    //pulisce lo schermo prima di riscriverci sopra
    void pulisci(){
        for(int i=0; i<BOARD_WIDTH*2+4; i++){
            for(int j=0; j < BOARD_HEIGHT; j++){
                move(j, i);
                printw("  ");
            }
        }
    }

    //funzione che mi disegna tutte le cose necessarie per il gioco
    void disegna() {
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

        // disegna il nostro pezzo
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (currentPiece[i][j] != 0) {
                    mvprintw(Y + j, (X + i) * 2, "[]");
                }
            }
        }

        //scrive lo score e le linee piene
        move(2,30);
        printw("SCORE: %d", score);
        move(1,30);
        printw("FULL LINES: %d", full);
        schermo();
        refresh();
    }

    //funzione per il tetramino
    void generaPezzi(){
        int pieces[7][4][4] = {
                {{0 ,0 ,0 ,0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
                {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, // J
                {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}, // L
                {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, // O
                {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}, // S
                {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // T
                {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}  // Z
        };
        int pezzorandom=rand()%7;

        //assegno il pezzo appena trovato a nextpiece
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                nextPiece[i][j]=pieces[pezzorandom][i][j];
            }
        }
    }

    //mi rileva una collisione e mi restituisce true se c'e'
    bool collisione(int pezzo[4][4]){
        bool coll=false;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(pezzo[i][j]!=0){
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

    void check_complete(){
        //mi controlla se ci sono linee complete
        for(int j=0; j< BOARD_HEIGHT; j++){
            bool lineaCompleta=true;
            for(int i=0; i<BOARD_WIDTH; i++){
                if(board[i][j]==0){
                    lineaCompleta=false;
                }
            }
            if(lineaCompleta){
                for(int k=j; k>0; k--){
                    for(int i=0; i< BOARD_WIDTH; i++){
                        board[i][k]=board[i][k-1];

                    }
                }
                full++;
                //da chiamare la funzione del punteggio!!
            }
        }
    }

    //controlla se in cima e' occupato
    bool prima_linea(){
        bool clean=true;
        for(int i=0; i<BOARD_WIDTH; i++){
            if(board[i][0]==1){
                clean=false;
            }
        }
        return clean;
    }

    void mettiPezzo(){
        //aggiunge al blocco "fisso"
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(currentPiece[i][j]!=0){
                    int x1=X+i;
                    int y1=Y+j;
                    board[x1][y1]=1;
                }
            }
        }
        check_complete();
        //assegno il pezzo upnext trovato a quello attuale
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                currentPiece[i][j]=nextPiece[i][j];
            }
        }
        //genero il prossimo pezzo
        generaPezzi();
        upnext_stampa();

        //resetto la posizione del tetramino
        X=BOARD_WIDTH/2 -2;
        Y=0;
        if(!prima_linea()){
            endwin();
            std::cout<<"gameover";
            exit(-1);
            //qui va richiamata la classe del punteggio e classifica
        }


    }

    //movimento del tetramino

    void mvdown(){
        Y++;
        if(collisione(currentPiece)){
            Y--;
            mettiPezzo();
            //se raggiungo la fine allora devo piazzare il tetramino
        }
    }

    void mvleft(){
        X--;
        if(collisione(currentPiece)){
            X++;
        }
    }

    void mvright(){
        X++;
        if(collisione(currentPiece)){
            X--;
        }
    }


    void ruota(bool orario) {
        int tmp[4][4];

        //ricopio il pezzo su tmp
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tmp[i][j] = currentPiece[j][i];
            }
        }

        //ruoto il pezzo

        if (orario) {
            // Rotate the piece clockwise
            for(int i=0; i<4; i++){
                for(int j=0; j<2; j++){
                    std::swap(tmp[i][j], tmp[i][3-j]);
                }
            }
        } else {
            // Rotate the piece counterclockwise
            for(int i=0; i<2; i++){
                for(int j=0; j<4; j++){
                    std::swap(tmp[i][j], tmp[3-i][j]);
                }
            }
        }



        //se vede che c'e' una collisione nel caso il pezzo ruoti non lo fa
        if (!collisione(tmp)) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    currentPiece[i][j] = tmp[i][j];
                }
            }
        }

    }


    //prende la mossa
    void getmv(){
        int userInput = getch();
        switch (userInput) {
            case KEY_DOWN:
                mvdown();
                score++;
                break;
            case KEY_LEFT:
                mvleft();
                break;
            case KEY_RIGHT:
                mvright();
                break;
            case 'a':
                ruota(true);
                break;
            case 's':
                ruota(false);
                break;
            case 'q':
                endwin();
                exit(0);
        }
    }

    void GameLoop(){
        //funzioni per lo schermo
        initscr();
        noecho();
        cbreak();
        curs_set(0);
        timeout(0);
        keypad(stdscr, true);

        //genera il primo tetramino
        generaPezzi();
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                currentPiece[i][j]=nextPiece[i][j];
            }
        }
        generaPezzi();
        upnext_stampa();

        //loop del gioco
        while(true){
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
};