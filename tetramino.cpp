

#include "tetramino.h"
#include <random>

Tetramino::Tetramino(int id) {
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            pezzo[i][j]=Tetramino::pieces[id][i][j];
        }
    }
}

Tetramino::Tetramino(int tmp[4][4]) {
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            this->pezzo[i][j] = tmp[i][j];
        }
    }
}

void Tetramino::scriviPezzo(int tmp[4][4]) {
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            tmp[i][j] = pezzo[i][j];
        }
    }
}

Tetramino *Tetramino::generaPezzoRandom() {
    int pezzorandom = rand() % 7;

    //assegno il pezzo appena trovato a nextpiece
    return new Tetramino(pezzorandom);
}

Tetramino* Tetramino::creaCopiaRuotata(bool orario) {
    int tmp[4][4];

    // Copio in tmp il currentPiece
    for (int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            tmp[i][j] = pezzo[i][j];
        }
    }

    //ruoto il pezzo
    if (orario) {
        for (int i = 0; i < 4 / 2; i++) {
            for (int j = i; j < 4 - i - 1; j++) {
                int temp = tmp[i][j];
                tmp[i][j] = tmp[4 - 1 - j][i];
                tmp[4 - 1 - j][i] = tmp[4 - 1 - i][4 - 1 - j];
                tmp[4 - 1 - i][4 - 1 - j] = tmp[j][4 - 1 - i];
                tmp[j][4 - 1 - i] = temp;
            }
        }
    } else {
        for (int i = 0; i < 4 / 2; i++) {
            for (int j = i; j < 4 - i - 1; j++) {
                int temp = tmp[i][j];
                tmp[i][j] = tmp[j][4 - i - 1];
                tmp[j][4 - i - 1] = tmp[4 - i - 1][4 - j - 1];
                tmp[4 - i - 1][4 - j - 1] = tmp[4 - j - 1][i];
                tmp[4 - j - 1][i] = temp;
            }
        }
    }

    //se vede che c'e' una collisione nel caso il pezzo ruoti non lo fa
    return new Tetramino(tmp);
}
