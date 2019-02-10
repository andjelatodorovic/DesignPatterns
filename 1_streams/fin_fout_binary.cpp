#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    /* otvaranje file-a za citanje u binary modu, iscitava se file byte po byte */
    ifstream in("test2.txt", ios::binary);
    /* opet testiramo da li smo uspesno otvorili file */
    if (in.is_open()) {
        cout << "Ulazni file otvoren uspesno." << endl;
    } else {
        cout << "Greska prilikom otvaranja file-a." << endl;
        exit(1);
    }
    /* otvaramo file za pisanje u binarnom modu */
    ofstream out("test2_copy.txt", ios::binary);

    /* testiramo da l' smo uspesno otvorili izlazni file */
    if (out.is_open()) {
        cout << "Izlazni file otvoren uspesno." << endl;
    } else {
        cout << "Greska prilikom otvaranja file-a." << endl;
        exit(1);
    }
    /* pokazivac za iscitavanje mozemo da pomeramo na odredjenu poziciju pomocu naredbe seekg
       mozemo da uradimo in.seekg(POZICIJA) da je naredni byte koji citamo na poziciji POZICIJA od
       pocetka file-a a drugi nacin je in.seekg(OFFSET, NACIN) gde NACIN moze da bude ios_base::beg
       (u odnosu na pocetak file-a), ios_base::cur (u odnosu na trenutnu poziciju) i ios_base::end
       (u odnosu na kraj file-a), a OFFSET je pomeraj pozicije u odnosu na NACIN odabran, sa
       in.seekg(0, in.end) postavili smo pokazivac za citanje na kraj file-a */
    in.seekg(0, in.end);
    /* sa tellg() mozemo da uzmemo trenutnu poziciju u file-u koji iscitavamo, ako je doslo do neke greske
       vraca -1, posto smo na kraju file-a pozicija koju dobijemo je velicina file-a u byte-ovima */
    long fileSize = in.tellg();
    cout << "Velicina file-a: " << fileSize << " bytes" << endl;

    /* vracamo pokazivac na pocetak datoteke */
    in.seekg (0);

    /* koristicemo in.read(BAFER, VELICINA) da u BAFER iscitamo VELICINA byte-ova iz ulazne datoteke
       u ovom slucaju iscitacemo ceo file u jednom cugu - jer citamo fileSize byteova odjednom bafer.
       Obicaj je da se iz stream-a iscitavaju podaci u blokovima velicine BAFERA i onda je iscitavanje
       u nekoliko iteracija (u nekoj petlji) dok ne dodjemo do kraja stream-a */
    char* buffer = new char[fileSize];
    in.read(buffer, fileSize);
    /* sa out.write(BAFER, VELICINA) mozemo da upisujemo u izlazni file VELICINA byte-ova iz BAFER. U ovom
       slucaju ispisacemo ceo file koji je dugacak fileSize byte-ova i nalazi se u buffer */
    out.write(buffer, fileSize);

    delete[] buffer;
    /* na kraju zatvaramo izlazne/ulazne stream-ove kako bi ih diskonektovali u odnosu na file nad kojim su
       operisali. Izlazni file ako ima byte-ove koji cekaju na upis, ce prvo biti upisani pre konacnog zatvaranja */
    out.close();
    in.close();
    return 0;
}
