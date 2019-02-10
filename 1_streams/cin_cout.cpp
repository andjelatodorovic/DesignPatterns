#include <ostream>
#include <iostream> /* u biblioteci iostream se nalaze stream objekti cin, cout */
#include <iomanip>
#include <ios>

using namespace std;

int main() {
    /* cin je objekat tipa istream a cout tipa ostream, cin odgovara standardnom ulazu stdin,
       dok cout odgovara standardnom izlazu stdout */
	/* za stampanje na standardan izlaz koristimo cout, moguce je stampati
	   razlicite tipove, sa endl ili '\n' se stampa kraj linije */
    bool bTrue = true;
    char ch = 'a';
    string s = "ja sam stringa.";
    short si = 123;
    int i = 1234567;
    long long l = 1234567890123456;
    float f = 0.12345678901234567901234;
    double d = 0.12345678901234567901234;

    /* cin i cout objekti nalaze se u opsegu imena (namespace) std pa ako
       nismo stavili da kristimo taj prostor imena (nismo stavili using namespace std;)
       moramo da pristupimo tim objektima sa std::cin ili std::cout */
    cout << "Stampam bool, char, string, short, int, long long, float i double\n";
    std::cout << bTrue << '\n';
    cout << ch << endl;
    cout << s << endl;
    cout << si << endl;
    cout << i << endl;
    cout << l << endl;
    cout << f << endl;
    cout << d << endl;
	/* moguce je vezati stampanje vise stvari odjednom */
	cout << "Stampam sa lancanim vezivanjem operatora <<\n";
	cout << ch << ' ' << s << " " << si << endl;

    /* moguce je podesiti na koliko decimala zelimo da stampamo neki float/double
       to je moguce uraditi sa cout.precision(BROJ_DECIMALA) ili prosledjivanjem
       modifikatora putem operatora <<, tj. cout << setprecision(BROJ_DECIMALA) */
    cout << "Stampam float sa menjanjem broja decimala sa cout.precision(12)\n";
    cout.precision(12);
    cout << f << endl;
    cout << "Stampam float sa menjanjem broja decimala sa cout << setprecision(8) << f << endl \n";
    cout << setprecision(8) << f << endl;

    /* moguce je stampati decimalne brojeve u fiksnoj (cela prezentacija) ili naucnoj/scientific
       prezentaciji (oblika x.cccc  10^eksponent. To se ostvaruje prosledjivanjem modifikatora
       fixed putem operatora << ako hocemo fiksnu prezentaciju ili modifikatora scientific za naucnu */
    cout << "Stampam prvo sa cout << fixed a onda sa << scientific isti broj d\n";
    cout << "fixed: " << fixed << f << ", scientific: " << scientific << d << endl;

    /* moguce je stampati samo jedan karakter */
    cout << "Stampam samo jedan karakter sa cout.put('t'), a nakon toga cout.put('\\n'): ";
    cout.put('t');
    cout.put('\n');

    /* postoje i drugi izlazni stream-ovi za logovanje toka progama koristi se clog a za prikaz
       gresaka stream cerr (koji odgovara standardnom izlazu stderr) Ukoliko ne preusmerimo ove stream-ove
       na neko drugo mesto (npr. file) oni ce u Windowsu biti prikazani na standardnom izlazu kao da smo
       koristili cout */
    clog << "Ovo je napisano sa clog" << endl;
    cerr << "Ovo je napisano sa cerr ali opet prikazano kao sa cout" << endl;

    /* ovi izlazni stream-ovi poseduju razne markere/flags cijim postavljanjem/uklanjanjem mozemo
       da menjamo neke karakteristike: npr. vec vidjen i scientific/fixed nacin prikaza decimalnih,
       baza u kojoj brojeve (npr decimalni, oktalni, hexadecimalni), znak baze, poravnanje (levo/desno..) itd */
    /* sa komandom cout.flags(maska) mozemo da postavimo celokupnu masku/flags na izlaznom stream-u cout,
       a ako koristimo cout.flags() dobijamo trenutno postavljenu masku na stream-u*/
    ios::fmtflags stara_maska = cout.flags();
    cout << "Trenutna maska: " << stara_maska << endl;
    /* ios::left je marker za poravnanje na levo, ios::hex sluzi za prikaz u heksadecimalnom obliku,
       i ios::showbase da se prikaze baza */
    cout.flags(ios::right | ios::hex | ios::showbase );
    cout << "Nova maska: " << cout.flags();
    cout.flags(ios::dec);
    cout << ", u decimalnom nova maska je: " << cout.flags() << endl;
    cout.flags(stara_maska);

    /* sa cout.setf(formatFlag) se postavljaju markeri koje zelimo, ti markeri su u stvari bitmaske
        pa je ova operacija u stvari stara_maska | formatFlag, dok drugi oblik cout.setf(formatFlag, maska)
        menja masku u ((formatFlag & maska) | (flags() & ~maska)), tj. postavlja bitove koji su postavljeni
        i u maska i formatFlag a brise one koji su postavljeni u maska a ne u formatFlag. Obe komande
        vracaju staru masku pre izmene*/
    /* npr. da postavimo stampanje u hexadecimalnom obliku */
    cout.setf(ios_base::hex , ios_base::basefield);
    /* i da postavimo stampanje baze 0x */
    cout.setf(ios_base::showbase);
    cout << "Stampam broj 1234 u hexadecimalnom: " << 1234 << endl;
    /* sa unsetf(maska) se uklanja maska iz markera, npr. da uklonimo stampanje baze (0x) */
    cout.unsetf(ios_base::showbase);
    cout << "Stampam broj 1234 u hexadecimalnom bez znaka za bazu: " << 1234 << endl;
    /* ostali markeri za baze su ios_base::dec za decimalni (10) i ios_base::oct za oktalni (8) */
    cout.setf(ios_base::oct , ios_base::basefield);
    cout.setf (ios_base::showbase);
    cout << "Stampam broj 1234 u oktalnom sa znakom za bazu: " << 1234 << '\n';
    /* uklanjamo marker za oktalnu bazu */
    cout.unsetf(ios_base::oct);

    /* tip koji vrati flags i koji cuva masku/markere je ios_base::fmtflags */
    ios_base::fmtflags ff;
    ff = cout.flags(); /* uzimamo trenutnu masku */
    ff &= ~cout.basefield;   /* drugi nacin (rucno) da se ukloni marker basefield */
    ff |= cout.hex;          /* drugi nacin da se postavi hex marker */
    ff |= cout.showbase;     /* i da prikaze bazu */
    cout.flags(ff); /* postavljamo ovako konstruisanu masku */
    cout << "Stampam broj 1234 sa rucno podesenom maskom: " << 1234 << endl;

    /* moguce je stampati i sa manipulatorima, dec, oct, hex, showbase */
    cout << "Stampam broj 1234 u oktalnom i showbase sa manipulatorima: " << oct << showbase << 1234 << endl;
    cout << "Stampam broj 1234 u heksadecimalnom i showbase sa manipulatorima: " << hex << showbase << 1234 << endl;

    /* moguce je podesiti sirinu stampanja nekog polja sa cout.width(SIRINA_STAMPE), moguce je i popuniti
       razmake u sirini sa nekim znakom i to postavljamo sa cout.fill(ZNAK). Ove promene vaze samo za
       narednu stampu, posle koje se vraca u normalno stanje stampanje */
    cout.flags(ios::right | ios::dec | ios::showbase);
    cout << "Stampam broj 1234 na 9 mesta sirine: '";
    cout.width(9); /* postavljamo sirinu stampa na 9 */
    cout << 1234 << "'" << endl;
    cout << "Stampam broj 1234 na 9 mesta sirine sa znakom $ na praznim mestima: '";
    cout.width(9);
    cout.fill('$'); /* postavljamo znak $ da popuni prazna mesta */
    cout << 1234 << "'" << endl;
    cout << 1234 << " Vise ne vaze promene sa cout.width(9) i cout.fill('$') stampa je normalna" << endl;
    /* moguce je menjati sirinu stame sa modifikatorom setw(SIRINA) dok se znak na praznom mestu
       moze postaviti sa setfill(ZNAK) */
    cout << "Stampam broj 1234 na 9 mesta sirine i znakom $ na praznim sa modifikatorima: '" << setw(9)
            << setfill('$') << 1234 << "'" << endl;

    /* Sa standardnog ulaza (stdin) ucitajemo pomocu objekta cin tipa istream. Ucitavanje je
       moguce preko overload-ovanog operatora >> kao sto je bio slucaj za izlazom i cout i << */
    int intBroj;
    long long longBroj;
    float floatBroj;
    string stringa;
    char karakter;
    cout << "Upisi redom int broj, long broj, float broj, string i char: ";
    /* otkomentarisati narednu liniju u slucaju testiranja */
    //cin >> intBroj >> longBroj >> floatBroj >> stringa >> karakter;
    cout << "Unesene vrednosti: " << intBroj << ", " << longBroj << ", " << floatBroj << ", '" << stringa << "', '" << karakter << "'" << endl;

    /* karakter je moguce uneti i sa cin.get(ch) ova funkcija vraca procitani karakter ili EOF (end of file)
       ukoliko je doslo do kraja stream-a i u ovom slucaju je failbit postavljen na stream-u
       Ova funkcija preskace takozvane 'whitespace' karaktere (razmake, tabove, krajeve redova) i
       ucitava direktno naredni neprazan karakter */
    cout << "Upisi karakter: ";
    cin.get(ch);
    cout << "Ucitan je karakter '" << ch << "' pomocu cin.get(ch)" << endl;
    /* moguce je podesiti modifikator posle koga ce da funkcija ucitaje i prazne karaktere
       to je moguce uraditi sa noskipws modifikatorom tj. cin >> noskipws */
    cin >> noskipws;
    /* sad hoce white space da ucitava */
    cout << "Unosite znakove, za kraj pritisnite CTRL+Z (na Windows masinama) to je EOF karakter" << endl;
    while (cin >> ch) cout << "'" << ch << "'" << endl;
    if (cin.eof())                      // check for EOF
        cout << "[EoF reached]\n";
    else
        cout << "[error reading]\n";
    /* da bi pocistili markere greske na stream-u koristimo .clear koji podesi status greske na goodbit,
       tj. da je stream u dobrom stanju. Markeri greske koji mogu da se jave su eofbit (kada se dodje do EndOfFile),
       failbit (logicka greska pri I/O) i badbit (greska prilikom citanja/pisanja). Moguce je proveriti
       stanje svakog od bitova sa cin/cout.good() (za goodbit), cin/cout.fail() (za failbit),
       cin/cout.eof() (za eofbit) i cin/cout.bad() (za badbit).*/
    cin.clear();

    /* Moguce je ucitati celu jednu liniju sa ulaza (sve do znaka za kraj reda) pomocu naredbe
       getline(cin, s) gde je s stringa u koju cemo da upisemo ulaz */
    string celaLinija;
    cout << "Unosite linije, za kraj unesite EOF znak (CTRL+Z na Windows masinama):\n";
    while (getline(cin, celaLinija)) {
        cout << "Ucitana linija:'" << celaLinija << "'" << endl;
    }
    cin.clear();
    /* Umesto da granicnik za novu liniju bude sistemski znak za novi red, moguce je ucitavati do
       znaka koji sami postavimo da oznacava kraj reda i to se radi sa komandom getline(cin, ZNAK_ZA_KRAJ_REDA)
       znaci po default-u getline(cin) je isto kao i getline(cin, '\n'). Mi mozemo da stavimo da kraj reda bude
       znak tacka '.' pa je komanda u tom slucaju getline(cin, '.') */
    cout << "Sad je svaka nova linija razdvojena sa znakom '.' Unos se prekida sa CTRL+Z" << endl;
    while (getline(cin, celaLinija, '.')) {
        cout << "Ucitana linija:'" << celaLinija << "'" << endl;
    }
    /* da bi vratili stanje stream-a da preskace blanko karaktere koristimo modifikator skipws */
    cin >> skipws;
    cin.clear();
    cout.clear();

    return 0;
}
