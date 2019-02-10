/* umesto pisanja/citanja sa standardnog ulaza/izlaza ili iz file-a moguce je konstruisati ulazne/izlazne
   stream-ove nad string-ama. Biblioteka koja nam to omogucava je <sstream> */
#include <sstream>
#include <iostream>

using namespace std;

int main() {
    /* istringstream klasa nam omogucava da kreiramo istream objekte koji citaju iz string-i.
       Konstruktor je istringstream(STRING) gde se konstruise istream nad stringom STRING */
    istringstream in("1 2 3 4 5");
    /* ostringstream je klasa za ostream za string-e, tj pisanje u stream-u koji radi nad string-om */
    ostringstream out;
    int tmp;
    /* sve ostalo za in/out je isto kao i za ostale objekte tipa istream/ostream, kao sto su bili cin/cout */
    while (!in.eof()) {
        in >> tmp;
        out << tmp;
    }
    /* da bi odstampali sadrzaj stream-a koristimo f-ju out.str() */
    cout << "Sadrzaj stream-a out: '" << out.str() << "'" << endl;

    /* sa rdbuf moguce je dobiti pristup (pokazivac na) buffer-u nad kojim stream operise, ovde cemo da uzmemo
       pokazivac na buffer nad kojim out stream operise i upisemo '67' ma poziciji 2, to se radi sa funkcijom
       sputn(STRING, DUZINA) koja upisuje u buffer DUZINA karaktera stringe STRING. Klasa stringbuf
       se nalazi u biblioteci <streambuf> */
    stringbuf *buf = out.rdbuf();
    buf->sputn("67",2);
    cout << "buf->str: '" << buf->str() << "'" << endl;

    return 0;
}
