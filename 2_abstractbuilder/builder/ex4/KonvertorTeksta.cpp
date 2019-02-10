#include <iostream>
#include <cstring>

using namespace std;

/* apstraktan graditelj */
class KonvertorTeksta {
public:
	virtual void konvertujZnak(char c) = 0;
	virtual void konvertujParagraf() = 0;
};

/* konkretan proizvod */
class ASCIITekst {
public:
	void dodaj(char c) {
	    cout << "dodajem znak " << c << " u finalni tekst." << endl;
	}
};

/* konkretan graditelj, kreira konkretan proizvod ASCIITekst */
class ASCIIConverter: public KonvertorTeksta {
public:
    /* proizvod koji vracamo kao rezultat gradnje, u ovom slucaju parsiranja tekst u ASCII format */
	ASCIITekst asciiTekst;

	/* graditeljski metod, konvertuje samo jedan znak procitan iz dokumenta u ASCII format */
	void konvertujZnak(char c) {
		char asciiChar = toupper(c);
			//gets the ascii character
        cout << "konvertujem karakter u ASCIITekst" << endl;
		asciiTekst.dodaj(asciiChar);
	}
	/* drugi graditeljski metod, konvertuje paragraf procitan iz dokumenta u ASCII format */
	void konvertujParagraf() {
	    cout << "konvertujem paragraf u ASCIITekst" << endl;
	}
	/* vraca izgradjeni proizvod, u ovom slucaju ASCII format procitanog dokumenta */
	ASCIITekst dajTekst() {
		return asciiTekst;
	}
};

class Dokument;

/* upravljac / director, pomocu prosledjenog graditelja (KonvertorTeksta) generise proizvod,
   dokument konvertovan u neki drugi format koji konkretan graditelj generise */
class RTFCitac {
public:
	static const char EOF = '&'; /* npr. znak za kraj fajla */
	static const char CHAR = 'c';
	static const char PARA = '$'; /* npr. znak za kraj paragrafa */
	KonvertorTeksta *builder;
	RTFCitac(KonvertorTeksta *obj) {
		builder = obj;
	}
	void parsirajRTF(Dokument *dokument);
};

/* ovo je dokument koji iscitavamo i konvertujemo u neki drugi oblik pomocu graditelja */
class Dokument {
public:
	char token;
	string sadrzaj;
	int idxSadrzaj;
    Dokument() {
        idxSadrzaj = 0;
        sadrzaj = "Ovo je sadrzaj dokumenta.$Ovo je novi paragraf.&";
    }
	char dajNaredniToken() {
		if (idxSadrzaj < sadrzaj.length() - 1) {
            return sadrzaj [idxSadrzaj ++];
		} else {
		    return RTFCitac::EOF;
		}
		return token;
    }
};

void RTFCitac::parsirajRTF(Dokument *dokument) {
    char znak;
    if (builder == NULL) {
        return;
    }
    while ((znak = dokument->dajNaredniToken()) !=  EOF) {
        switch (znak) {
            case PARA:
                builder->konvertujParagraf();
                break;
            default:
                builder->konvertujZnak(znak);
                break;
        }
    }
}

/* klijent, kreira konkretnog graditelja (koji pravi ASCII tekst file) prosledjuje ga
  upravljacu/direktoru (RTFCitac) koji zatim kreira konkretan proizvod */
class Klijent {
public:
	void napraviASCIITekst(Dokument *dokument){
		ASCIIConverter *asciiBuilder = new ASCIIConverter();
		RTFCitac *rtfCitac = new RTFCitac(asciiBuilder);
		rtfCitac->parsirajRTF(dokument);
		/* pretvaramo se da uzimamo fajl koji prestavlja ASCII format prosledjenog dokumenta */
		ASCIITekst asciiTekst = asciiBuilder->dajTekst();
	}
};

int main() {
    Klijent *klijent = new Klijent();
	Dokument *dokument = new Dokument();
	klijent->napraviASCIITekst(dokument);

	delete klijent;
	delete dokument;
}
