/*
UNOS: dimenzije n, m
UCITAJE SE MATRICA n x m
U IZLAZU SE STAMPA MATRICA GDE SVAKO POLJE MATRICE SE STAMPA NA 3 DECIMALE SA 8 MESTA ZA STAMPU
PRIMER
ULAZ
2 2 1.234567 0.123456 0.234567 5.1234567
IZLAZ
     1.234     0.123
     0.234     5.123

     cout << fixed << setw(8) << setprecision(3)
U DATOM RESENJU KORISTI SE I ZNAK '.' ZA POPUNJAVANJE PRAZNINA
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int nr, nc;
    cin >> nr >> nc;
    float a [nr] [nc];
    for (int r = 0; r < nr; r ++) {
        for (int c = 0; c < nc; c ++) cin >> a [r] [c];
    }
    for (int r = 0; r < nr; r ++) {
        for (int c = 0; c < nc; c ++) {
            cout.fill('.');
            cout << fixed << setw(8) << setprecision(3) << a [r] [c];
        }
        cout << endl;
    }
}
