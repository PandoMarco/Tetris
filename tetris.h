

#ifndef TETRIS_DEF_TETRIS_H
#define TETRIS_DEF_TETRIS_H


#include "tetramino.h"

class Tetris {
protected:
    const int BOARD_WIDTH = 10;
    const int BOARD_HEIGHT = 20;
    int score;
    int board[10][20] = {0};
    Tetramino* currentPiece;
    Tetramino* nextPiece;
    int X, Y;
    int full;

public:
    Tetris();

    void schermo();

    void upnext_stampa();

    void pulisci();

    void disegna();

    bool collisione(Tetramino* tetr);

    void mettiPezzo();

    bool prima_linea();

    void check_complete();

    //movimento del tetramino
    void mvleft();

    void mvright();

    void mvdown();

    void getmv();

    [[noreturn]] void GameLoop();

    void ruota(bool orario);

    void assign_nextPiece(Tetramino* m){
        nextPiece = m;
    }

    void assign_currentPiece(Tetramino* m){
        currentPiece = m;
    }

    Tetramino* getCurrentPiece(){
        return currentPiece;
    }

};
#endif //TETRIS_DEF_TETRIS_H
