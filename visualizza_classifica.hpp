#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>

using std::getline;
using std::ifstream;
using std::string;
using std::vector;

void visualizza_classifica();
vector<string> readFile(string, int &);