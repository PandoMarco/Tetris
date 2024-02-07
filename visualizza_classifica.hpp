#include <ncurses.h>

#include <string>
#include <fstream>

using std::getline;
using std::ifstream;
using std::string;


void visualizza_classifica();
int readFile(string nomefile, string righe[], int max_righe, int &larghezza_massima);