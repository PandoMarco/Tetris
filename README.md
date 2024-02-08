#Tetris
Questo applicativo permette di giocare al Tetris classico direttamente da terminale di linux.

#Compilazione
Dopo aver scaricato "Tetris" selezionare sul terminale la directory del progetto e eseguire il comando "make -f makefile" 

#Avvio
Per avviare il programma selezionare su terminale la directory del progetto e eseguire il comando "./tetris".
Se l'avvio viene eseguito correttamente si aprirà un menù sul terminale.

#Menu
Il menù presenta 3 opzioni: "Nuova partita","Visualizza classifica" e "Esci dal gioco".
Ci si muove nel menù con l'ausilio delle frecce ^(Up arrow) e v(down arrow).
Si seleziona l'opzione desiderata con "INVIO".

#"Nuova partita"
Selezionando "Nuova partita" si comincerà la sessione di gioco:
A sinistra c'è la griglia di gioco (Larga 10 blocchi e alta 20),
AL centro invece vengono mostrati il numero di linee completate ("FULL LINES"),il punteggio ("SCORE"), e la forma del prossimo Tetramino ad apparire ("upnext").
Per finire a destra vengono mostrati a schermo i comandi di gioco ("COMMANDS").

#Regole del gioco
Di seguito sono elencati le regole e gli elementi caratterizzanti del Tetris

#-Tetramini
Come nel Tetris classico ci sono 7 pezzi  detti "Tetramini" composti da 4 blocchi "[]" posizionati in maniera tale che creino la forma di una lettera ("I","T","J","L","O","S","Z").
I tetramini possono anche apparire ruotati in senso antiorario, in senso orario o essere specchiati verticalmente.

#-Scopo del gioco
Lo scopo del gioco è quello di fare più punti possibili prima che un blocco di un qualunque tetramino superi la cima della griglia.

#-Situazione di gioco
Il gioco comincia dal centro della riga più in alto della griglia (punto di generazione) generando casualmente un tetramino tra i 7 disponibili, lentamente il pezzo scenderà dalla cima della griglia finchè non colliderà su almeno uno dei lati inferiori con la griglia o un altro tetramino precedentemento posizionato, quando ciò avviene si posiziona il tetramino il che significa che non potrà più essere modificato o controllato dal giocatore.
Nel mentre il tetramino scende, il giocatore può muovere, ruotare o far accelerare il tetramino.
Dopo che un tetramino viene posizionato, viene inserito il tetramino rappresentato nella sezione "upnext" nel punto di generazione e sostituito da uno nuovo generato casualmente tra quelli validi.
Quando una riga orizzontale è completamente occupata da dei blocchi, allora la riga viene cancellata e tutti i blocchi soprastanti vengono spostati di 1 blocco verso il basso.

#-Comandi
Con "A" e "S" si ruota il tetramino in gioco rispettivamente in senso orario e antiorario.
Con le frecce '<-'(Left arrow) '->'(right arrow), si può movere a sinistra o a destra il tetramino.
Con la freccia v (Down arrow) è possibile accelerare la caduta del tetramino.

#-Collisioni
Lo spostamento e la rotazione del tetramino non possono essere fatte se vanno a collidere sui lati destri e sinistri con uno o più blocchi o i lati della griglia. 

#-Punti
Si ottengono punti in 2 modi differenti:
-1 punto per unità percorse con la caduta accellerata di un tetramino.
-Completando una o più linee si ottengono 100 punti per linea.
Se si completano 4 righe con una mossa si fa un "Tetris" che vale 800 punti.

#-Gameover
Quando un tetramino posizionato raggiunge la cima della griglia si ha il gameover e il punteggio viene salvato nella classifica.
Premendo "Q" si può visualizzare la classifica.

#"Visualizza classifica"
Selezionando "Visualizza classifica" dal menù si apre un riquadro dove si possono vedere i punteggi delle partite effettuate, dal meno al più recente.
Ogni linea del riquadro segna:
Il punteggio a sinistra;
La data e l'orario al centro;
L'anno nel quale è stata effettuata la partita a destra.
Premendo "Q" si ritorna al menù.

#"Esci dal gioco"
Selezionando "Esci dal gioco" dal menù, si arresta l'esecuzione del programma.

#-------------------Progetto per il corso di Programmazione,Informatica triennale 1°anno-------------------#
#Autori (Nome Cognome Matricola):
Elena Dattilo 0001114060
Federico Manuel Semprini 
Sara Negrini 0001113789
Marco Pandolfi 0001114391
