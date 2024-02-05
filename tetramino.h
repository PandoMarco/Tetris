//
// Created by puzzoz on 2/4/24.
//

#ifndef TETRIS_DEF_TETRAMINO_H
#define TETRIS_DEF_TETRAMINO_H

class Tetramino {
protected:
    int pezzo[4][4]{};
    // Crea una copia esatta del pezzo
    explicit Tetramino(int tmp[4][4]);
public:
    Tetramino* creaCopiaRuotata(bool);
    void scriviPezzo(int tmp[4][4]);
    static Tetramino* generaPezzoRandom();

    constexpr static const int pieces[7][4][4] = {

            {{0 ,0 ,0 ,0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
            {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, // J
            {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}, // L
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, // O
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}, // S
            {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // T
            {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}  // Z
    };

    explicit Tetramino(int id);
};
#endif //TETRIS_DEF_TETRAMINO_H