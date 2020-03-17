# Implementazione ed Analisi di algoritmi per la risoluzione di sistemi lineari (C++)

## Abstract:
L’obiettivo di questa relazione riguarda l’implementazione dei tre principali algoritmi per la risoluzione di sistemi lineari, ovvero il metodo diretto di Gauss e i due metodi iterativi Jacobi e Gauss-Seidel, in linguaggio di programmazione (C++). Durante la scrittura abbiamo prestato particolare attenzione alla complessità computazionale. 

## Complessità computazionale:
La complessità computazionale è un indice di efficienza di un algoritmo, essa può essere suddivisa in complessità spaziale e complessità temporale. In questa discussione ci occuperemo della seconda, in quanto il tempo rappresenta una risorsa non riutilizzabile, mentre la quantità di memoria occupata risulta trascurabile poiché riutilizzabile e soprattutto perché grazie alle odierne tecnologie, volte a risolvere problemi ben più complessi della semplice risoluzioni di sistemi lineari, disponiamo di una vastissima capacità di memoria-dati.
Basandoci sul modello ideale di Macchina ad accesso casuale (RAM) e considerando i seguenti “costi” (in termini di tempo macchina) per le istruzioni:
	* Unitario per lettura, scrittura, assegnamento, operazioni elementari, return, accesso all’array e valutazioni booleane.
	* Non unitario  per istruzioni composte, cicli, valutazioni condizionali e chiamate a sottofunzioni. 

Il programma è composto da un unico file sorgente, il main e una serie di sottofunzioni che offrono all’utente un’interfaccia essenziale e funzionale con un menù a selezione e la possibilità di acquisire le matrici da un file di testo a patto che sia presente nella directory da dove viene lanciato l’eseguibile del programma.

## Calcolo della complessità computazionale di ciascuna sottofunzione presente nel sorgente:

### pausa()
Una funzione che arresta i processi permettendo all’utente di visualizzare i risultati delle precedenti operazioni. È volta esclusivamente ad ottimizzare l’esperienza dell’utente ed è costituita da una semplice istruzione condizionale contenente operazioni a costo unitario. Ciò permette di ottenere una complessità computazionale pari all’incirca a θ(1), pertanto una tale procedura, sebbene non abbia alcuno scopo funzionale, non pregiudica assolutamente la tempistica dei sottoprogrammi in cui viene richiamata.

### stampa()
Funzione di stampa a video della matrice completa precedentemente acquisita. Essendo la matrice inizializzata come array bidimensionale, questa subroutine produce una complessità computazionale pari a θ(n^2).
inizializza()
Metodo che inizializza a zero tutti gli elementi della matrice. Come la funzione di stampa, anche essa è legata alla tecnica implementativa della matrice e quindi ha complessità computazionale θ(n^2).

### acquisisciMatrice()
Funzione che acquisisce da file di testo una matrice bidimensionale di dimensione massima n=100x101. È una funzione molto comoda che agevola l’inserimento delle matrici ed evita errori di battitura da parte dell’utente, piuttosto frequenti quando si lavora con sistemi molto grandi. Il tutto è implementato tramite un ciclo if a costo unitario con due cicli for annidati al suo interno, con una conseguente complessità computazionale pari a θ(n^2).
In base alla sistema operativo che si sta utilizzando (sistemi UnixLike o varie versioni di Windows) il programma visualizza a schermo l’elenco dei file disponibili nella directory.

I file di testo devono presentarsi nella seguente forma:
nomefile.txt
  * Inserire la dimensione della matrice n nella prima riga
	* Successivamente vengono letti i primi (n)x(n+1) coefficienti della matrice completa con ultima colonna il vettore dei termini noti

### Gauss()
Questa funzione implementa il metodo numerico per il calcolo del vettore soluzione di un sistema rappresentato da una matrice completa del tipo [A|B].Il sottoprogramma inizia con una prima valutazione della matrice per mezzo di due cicli for annidati e una condizione if per valutare se effettivamente il sistema ammetta soluzioni, tale operazione comporta una complessità θ(n^2).

Successivamente il codice provvede a rendere triangolare superiore la matrice (complessità θ(n^3)) e alla risoluzione del sistema all’indietro (complessità θ(n^2)).
Oltre a ciò sono presenti una semplice funzione di stampa del vettore soluzione, avente complessità θ(n), e le chiamate alle funzioni pausa() (θ(1)) e inizializza() (θ(n^2)).

Caso migliore = Caso medio = Caso peggiore

Uno svantaggi di questo metodo è che, essendo di tipo diretto, il numero di passaggi che esegue è predeterminato, questo fatto non ne ottimizza né la precisione (errore di arrotondamento), né il tempo di esecuzione. La complessità computazionale complessiva è pari a θ(n^3).

### Jacobi()
Questo procedimento richiede un ulteriore condizione affinché il programma restituisca un valore corretto: la matrice deve essere a diagonale dominante. 

Il codice inizia con due cicli for annidati che controllano la diagonale dominanza del sistema (complessità θ(n^2)).
Successivamente viene richiesto all’utente il numero di iterazioni desiderate. Bisogna considerare che più alto sarà tale valore e più basso sarà l’errore di troncamento, pertanto il vettore soluzione convergerà ad un risultato sempre più preciso; al contrario però aumenterà l’errore di arrotondamento, con un conseguente allontanamento dal risultato esatto. È dunque fondamentale scegliere con criterio il numero di iterazioni da eseguire tenendo conto di questi due fattori e cercando un compromesso che minimizzi l’influenza di entrambi gli errori.

Successivamente viene applicato iterativamente il metodo per m-volte, ogni iterazione contiene due cicli for annidati con un'istruzione condizionale a costo unitario e un ulteriore ciclo for che copia i valori dal vettore tentativo2 al vettore tentativo.

Chiudono come sempre le funzioni stampa(), pausa() e inizializza() rispettivamente θ(n^2), θ(1) e  θ(n^2).

* Caso Migliore:
La matrice non è a diagonale dominante quindi, non essendo applicabile il metodo di Jacobi, il programma esegue solo i due cicli for iniziali con conseguente complessità θ(n^2).

* Caso Medio:
Per m sufficientemente piccolo rispetto ad n (m<<n) il programma esegue poche iterazioni includenti i due cicli for annidati (θ(n^2)), pertanto la complessità computazionale risultante è θ(m⋅n^2)=m⋅θ(n^2).

* Caso Peggiore:
Per m sufficientemente grande il programma esegue molte iterazioni comprendenti i due cicli for annidati con conseguente complessità che tende a O(n^3).

### GSeidel()

Questo algoritmo è un perfezionamento di quello di Jacobi. Il vantaggio principale consiste nell’utilizzo di un unico vettore tentativo, con un conseguente abbassamento della complessità computazionale spaziale ma non di quella temporale.

## Errori nei metodi numerici:
I vari metodi numerici ci consentono di arrivare ad una soluzione approssimata del problema che si sta affrontando mediante una serie di operazioni algebriche elementari. Dal momento che tali operazioni vengono eseguite da un computer, sorgono spontaneamente due tipi di errori (errori di rappresentazione) durante l’esecuzione del metodo numerico:
  * Errore di troncamento: si presenta quando si passa dalla soluzione puramente teorica di un problema matematico a quella algoritmica. Dopo un determinato numero di cifre siamo costretti a trascurare una parte di informazione a causa della capacità limitata di memoria della macchina. (numero insufficiente di iterazioni del metodo numerico)
  * Errore di arrotondamento: legato, come il primo, alla rappresentazione numerica al calcolatore, ma si rivela nel momento in cui i valori numerici vengono arrotondati al numero di cifre richieste. (numero troppo elevato di iterazioni) 

Tendenzialmente siamo portati a pensare che più si aumenti il numero di iterazioni eseguite dall’algoritmo più ci si avvicini alla soluzione esatta, andando a diminuire gradualmente l’errore commesso.
Questo è vero solo in parte, infatti all’aumentare delle iterazioni l’errore di troncamento tenderà a rimpicciolirsi, viceversa quello di arrotondamento aumenterà per l’accrescersi della quantità di operazioni da eseguire.
Dato che non è possibile trovare un punto preciso nel quale i due errori si incontrano, occorrerà lavorare nell’intorno di un punto che rappresenti l’intersezione fra le due curve.

### Miglioramenti:
Un possibile miglioramento del programma potrebbe consistere:
  * Inserire i prototipi delle sottofunzioni in un Header-File e le sottofunzioni stesse in un file linkato al sorgente precompilato, diminuendo così il tempo di esecuzione.
  * Creare una procedura in grado di acquisire non solo le matrici ma anche sistemi di equazioni. 


