/* Salvataggio del punteggio ottenuto nella partita
 * Il programma salva anche la data di quando è
 * finita la partita  
*/

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void salva_punteggio(int punteggio){

    //Dichiarazione argomento per time()
    time_t tt; 

    // Dichiarazione variabile contentente localtime() 
    struct tm* ti; 
  
    // Applicazione di time() 
    time(&tt); 
  
    // Uso di localtime() 
    ti = localtime(&tt); 

    ofstream outputFile; /* Dichiarazione di tipo */
    outputFile.open("classifica.txt",ios::app); /* Apertura del file */

    outputFile << punteggio << " " << asctime(ti)<< endl;
    outputFile.close();
}