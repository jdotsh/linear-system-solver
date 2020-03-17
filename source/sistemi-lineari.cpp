#include <iostream>
#include <fstream>
#include <math.h>
#define MAX 100
using namespace std;

// VARIABILI GLOBALI

double matrice[MAX][MAX+1];
double alfa; // Variabile di appoggio che contiene il valore di matrice[i][k]
double elemento_max; // Elemento massimo della colonna
double appo; // Variabile di appoggio
double ck; // Coefficiente che moltiplica le righe per la diagonalizzazione
double s = 0; // Variabile per il calcolo delle soluzioni all'indietro

int n, i, j, k, ind = 0; // Dimensione dell'input e contatori
int sistema_operativo;  // Serve per selezionare il sistema operativo

fstream file; //Variabile di tipo fstream

void pausa(){
    if (sistema_operativo)system("pause");
    else {
        cout << " Qualsiasi lettera per continuare... " << endl;
        getchar();
    }
}

void stampa(){
    cout << endl;
    for (int i=1; i<=n; i++) {
        for (int j=1;j<=n+1;j++) {
            cout << matrice[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl << endl;
    pausa();
}

void inizializza(int k) {
    for (int i=0; i<k;i++) {
        for(int j=0; i<k+1; i++) {
            matrice[i][j] = 0;
        }
    }
}

void acquisisciMatrice() {
    char o[15];
    cout << " File disponibili: " << endl;
    if (sistema_operativo)system("dir");
    else system("ls");
    cout << " Inserisci nome del file contente la matrice da analizzare\n ";
    cout << " [specifica l'estensione .txt] " << endl;
    cin >> o;
    file.open(o,ios::in);
    if (file.good())
    {  // Recupera il numero delle equazioni
        file >> n;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n+1; j++) {
                file >> matrice[i][j]; // AQUISIZIONE
            }
        }
    }
    file.close();
    cout << " File letto con successo. " << endl;
    pausa();
    return;
}

// GAUSS

void Gauss() {
    cout << " Gauss " << endl;
    double soluzione[n]; // Inizializzo il vettore soluzione
    
    for (k=1; k<=n-1; k++) {
        elemento_max = fabs(matrice[k][k]);
        ind = k; // La variabile ind indica la riga sulla quale si sta operando
        for (i=k+1; i<=n; i++) {
            alfa = fabs(matrice[i][k]);
            if (alfa > elemento_max) {
                elemento_max=alfa;
                ind=i; // Indica la riga che contiene il massimo
            }
        }
        if (elemento_max == 0) {
            cout << " Il sistema non ammette soluzione " << endl;
            pausa();
            return;
        }
        if (ind != k) { // Per tutti gli elementi della riga
            for (j=k; j<=n+1; j++) {
                appo=matrice[ind][j];
                matrice[ind][j]=matrice[k][j];
                matrice[k][j]=appo;
            }
        }
        // Rendo la matrice triangolare
        for (i=k+1; i<=n; i++) {
            ck = matrice[i][k]/matrice[k][k];
            for (j=k; j<=n+1; j++) {
                matrice[i][j]-=ck*matrice[k][j];
            }
        }
    }
    // Calcolo del vettore delle soluzioni
    if (matrice[n][n] == 0) {
        cout << " Il sistema e' indeterminato " <<endl;
        pausa();
    }
    soluzione[n] = matrice[n][n+1]/matrice[n][n];
    for (i=n-1; i>=1; i--) {
        for (j=i+1; j<=n; j++) {
            s+= matrice[i][j]*soluzione[j];
        }
        soluzione[i] = (matrice[i][n+1]-s)/matrice[i][i];
    }
    // Stampa del vettore soluzione
    cout << " La soluzione e': ";
    for(i=1; i<=n; i++) cout << soluzione[i] << endl;
    cout << endl << endl;
    pausa();
    inizializza(n);
}

// JACOBI

void Jacobi() {
    cout << " Jacobi " << endl;
    // Controllo che la matrice sia a diagonale dominante
    for (i=1; i<=n; i++) {
        double s = 0;
        for (j=1; j<=n; j++) {
            s += fabs(matrice[i][j]);
        }
        s = s - fabs(matrice[i][i]);
        if (s < 0) {
            cout << " La matrice non è diagonale dominante " << endl;
            pausa();
            return;
        }
    }
    int m; // Numero di iterazioni
    cout << " Inserire il numero di iterazioni " << endl;
    cin >> m;
    
    // Creo il vettore tentativo
    double tentativo[n], tentativo2[n];
    
    for (i=1; i<=n; i++) {
        tentativo[i] = matrice[i][n+1]/matrice[i][i];
    }
    
    while (m > 0) {
        for (i=1; i<=n; i++) {
            double s=0;
            for (j=1; j<=n; j++) {
                if (j != i) {
                    s += matrice[i][j]*tentativo[j];
                }
            }
            tentativo2[i] = (matrice[i][n+1]-s)/matrice[i][i];
            tentativo[i] = tentativo2[i];
        }
        m--;
    }
    cout << " La soluzione e': " << endl;
    
    for (i=1; i<=n; i++) {
        //tentativo[i]=tentativo2[i];
        cout << tentativo[i] << endl;
    }
    cout << endl << endl;
    pausa();
    inizializza(n);
}




// GAUSS-SEIDEL

void GSeidel() {
    cout << " Gauss-Seidel " << endl;
    // Controllo diagonale dominante
    for (i=1; i<=n; i++) {
        double s = 0;
        for (j=1; j<=n; j++) {
            s += fabs(matrice[i][j]);
        }
        s -= fabs(matrice[i][i]);
        if (s < 0) {
            cout << " La matrice non è diagonale dominante " << endl;
            pausa();
            return;
        }
    }

    //Creazione vettore tentativo
    double tentativo[n];
    double tentativo1;
   
    
    // Calcolo del vettore soluzione
    int m;
    cout << " Inserire il numero di iterazioni: " << endl;
    cin >> m;
    
    while (m > 0){
        
        for (i=1; i<=n; i++) {
            s = 0;
            
            for (j=1; j<=i-1; j++) {
                s += matrice[i][j]*tentativo[j];
            }
            for (j=i+1; j<=n; j++) {
                s += matrice[i][j]*tentativo[j];
                tentativo1 = (matrice[i][n+1]-s)/matrice[i][i];
                tentativo[i] = tentativo1;
            }
        
        }
        m--;
    }
    
    cout << " Il vettore soluzione e':\n\n";
    
    for (i=1; i<=n; i++) {
        cout << tentativo[i] << endl;
    }
    
    cout << endl;
    pausa();
    inizializza(n);
    return ;
}












// PROGRAMMA PRINCIPALE

int main() {
    char c;
    cout << " Quale Sistema Operativo stai utilizzando? " << endl;
    cout << " 0 - UNIX - LINUX - OSX " << endl;
    cout << " 1 - WINDOWS " << endl;
    cin >> sistema_operativo;
    while(1)
    {
        if (sistema_operativo)system("cls");
        else system("clear");
        
        cout << " METODI RISOLUTIVI PER SISTEMI LINEARI:\n " << endl;
        cout << " 0: acquisici da file " << endl;
        cout << " 1: stampa " << endl;
        cout << " 2: Gauss " << endl;
        cout << " 3: Jacobi " << endl;
        cout << " 4: Gauss-Seidel " << endl;
        cout << " 5: esci " << endl;
        cin >> c;
        
        switch(c)
        {
            case '0': acquisisciMatrice();break;
            case '1': stampa(); break;
            case '2': Gauss(); break;
            case '3': Jacobi(); break;
            case '4': GSeidel(); break;
            case '5': return 0;
            default:
                cout << " CARATTERE NON VALIDO! " << endl;
        }
    }
}

// FINE DEL PROGRAMMA
