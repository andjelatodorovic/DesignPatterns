/* da bismo mogli da koristimo klase ifstream za citanje iz file-a i ofstream za pisanje
   u file potrebno je da koristimo biblioteku <fstream> u kojoj se nalaze ove klase */
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    /* sve sto je vazilo i sto smo radili za cin stream moze da se koristi za ifstream,
       takodje i cout stream vazi isto za ofstream jer su oba naslednici istream i ostream klasa redom */

    /* za ucitavanje file-ova koristimo klasu ifstream koja nasledjuje istream klasu
       pa samim tim i sve javne i zasticene funkcije */
    /* konstruktor za ifstream moze da bude ifstream(IME_FILE) ili ifstream(IME_FILE, NACIN_OTVARANJA)
       gde IME_FILE je ime file-a koji otvaramo za iscitavanje dok NACIN_OTVARANJA je mode/nacin na koji
       cemo da citamo iz file-a. Sa jednim parametrom konstruktora podrazumeva se da je ovaj nacin otvaranja
       ifstream::in, drugi modovi su out (za pisanje u file), binary (za citanje u binarnom modu, a ne tekstualnom),
       ate, app i trunc koje cemo vise obraditi za pisanje u file, klasa ofstream */
    /* ovde kreiramo jedan ifstream objekat koji ce da cita iz file-a "test1.txt" */
    ifstream in("test1.txt");
    /* da bi testirali da li smo uspesno otvorili file koristimo funkciju in.is_open(),
       koja ce da bude true ako smo uspesno otvorili file */
    if (in.is_open()) {
        cout << "File uspesno otvoren" << endl;
    } else {
        cout << "Greska prilikom otvaranja file-a" << endl;
        exit(1);
    }
    /* za pisanje u file koristimo klasu ofstream gde je konstruktor kao kod ifstream, i imamo dve mogucnosti
       ofstream(IME_FILE) gde je podrazumevani nacin otvaranja file-a za pisanje ofstream::out gde se pise u
       novi file, sve prethodno se brise. Drugi nacini su ofstream::binary (binarno pisanje), ofstream::ate
       (pocetna pozicija za pisanje je kraj file-a, moze se promeniti pozicija za pisanje 'rucno'),
       app (sve sto se pise se doda na kraj file-a) i trunc (sve sto je prethodno bilo u file-u je izbrisano) */
    ofstream out("test1_copy.txt");
    /* isto imamo funkciju za proveru da li smo uspesno otvorili file */
    if (out.is_open()) {
        cout << "File za pisanje otvoren uspesno" << endl;
    } else {
        cout << "Greska prilikom otvaranja file-a" << endl;
        exit(1);
    }
    /* sada cemo iscitati sve karaktere iz ulaznog file-a i upisati ih u izlazni file,
       nacin citanja i pisanje je isti kao sto smo video kod cin/cout stream-ova */
    char ch;
    while (!in.eof()) {
        in.get(ch);
        out.put(ch);
    }
    /* sa close se zatvara file i prekida se veza sa stream-om, sve sto je u cekanju da bude upisano u file
       ce biti upisano */
    in.close();
    out.close();
    return 0;
}
