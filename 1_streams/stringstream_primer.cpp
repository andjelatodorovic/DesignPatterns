/*
IZ FILE-A SE UCITAVAJU REDOVI KARAKTERA
  NA PRIMER (ulaz.txt)
  1   , 2  , 33,    55, 66
  , 53 34, 43 53, 66, 22

    UCITAVATI U NEKU STRINGU SA GETLINE SA ',' DO EOF
    A ONDA KORISTECI ISTRINGSTREAM IZ TOGA IZVUCI BROJEVE
    I UPISATI IH U OSTRINGSTREAM
    I NA KRAJU STAMPATI SADRZAJ OSTRINGSTREAM OBJEKTA
    U FILE izlaz.txt

    NAPOMENA: ovo nije uradjeno na bas optimalan nacin vec vise sluzi kao
              primer primene naucenog
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    ifstream in("ulaz.txt");
    if (!in.is_open()) {
        cout << "Greska prilikom otvaranja file-a ulaz.txt" << endl;
        exit(1);
    }
    string line, all = "";
    while (!in.eof()) {
        getline(in, line, ',');
        all += " " + line;
    }
    istringstream ins(all);
    ostringstream outs;
    int tmp;
    while (ins >> tmp) {
        outs << tmp << ' ';
    }
    cout << "Pisem rezultate u izlazni file izlaz.txt" << endl;
    ofstream out("izlaz.txt");
    out << outs.str() << endl;
    out.close();
    in.close();
}
