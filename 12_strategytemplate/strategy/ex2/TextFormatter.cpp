#include <sstream>
#include <iostream>

using namespace std;

/* strategija / strategy
   poseduje metod Format koji formatira prosledjeni tekst i kao rezultat vraca taj
   formatirani tekst */
class IFormatter {
public:
    virtual string Format(string text) = 0;
};
/* konkretna strategija / concrete strategy
   formatira tekst u neki kvazi XML format */
class CXMLFormatter: public IFormatter {
public:
    virtual string Format(string text) {
        istringstream in(text);
        ostringstream out;
        out << "<XML version = 0.1>\n";
        string word;
        while (!in.eof()) {
            in >> word;
            out << "\t<WORD>\n\t\t" << word << "\n\t</WORD>\n";
        }
        out << "</XML>\n";
        return out.str();
    }
};
/* konkretna strategija / concrete strategy
   formatira tekst u mala slova */
class CSmallLettersFormatter: public IFormatter {
public:
    virtual string Format(string text) {
        string res = text;
        for (unsigned int i = 0; i < res.size(); i++) {
            if (isupper(res[i])) res[i] = tolower(res[i]);
        }
        return res;
    }
};
/* konkretna strategija / concrete strategy
   formatira tekst u velika slova */
class CLargeLettersFormatter: public IFormatter {
public:
    virtual string Format(string text) {
        string res = text;
        for (unsigned int i = 0; i < res.size(); i++) {
            if (islower(res[i])) res[i] = toupper(res[i]);
        }
        return res;
    }
};
/* kontekst
   dokument koji poseduje sadrzaj cuvan u ostringstream
   kada se pozove metod Format koristi trenutno postavljen objekat konkretne strategije
   da formatira trenutni tekst dokumenta/konteksta */
class CDocument {
public:
    CDocument(): m_formatter(new CSmallLettersFormatter()) { m_text.str(""); }
    CDocument(IFormatter* formatter): m_formatter(formatter) { m_text.str(""); }
    virtual ~CDocument() { if (m_formatter != NULL) delete m_formatter; }
    virtual void Add(string word) {
        m_text << " " << word;
    }
    virtual void Clear() {
        m_text.str("");
    }
    virtual string Format() {
        return m_formatter->Format(m_text.str());
    }
    virtual void SetFormatter(IFormatter *formatter) {
        if (m_formatter != NULL) delete m_formatter;
        m_formatter = formatter;
    }
protected:
    IFormatter*     m_formatter;
    ostringstream   m_text;
};
/* kreiramo dokument (osnovni konstruktor ce da kreira neku pocetnu konkretnu strategiju),
   dodamo neki tekst, zatim zatrazimo da se tekst formatira i to prikazemo na ekranu
   zatim promenimo konkretnu strategiju, dodamo opet neki tekst, opet fa formatiramo itd
   tok izvrsavanja prikazujemo na ekranu */
int main() {
    CDocument doc;
    doc.Add("Naslov");
    doc.Add("Prica o tri praseta.");
    doc.Add("Prvi napravio kucicu od slame.");
    cout << doc.Format() << endl;

    doc.SetFormatter(new CXMLFormatter());
    doc.Add("Drugi napravio kucicu od DRVETA");
    cout << doc.Format() << endl;

    doc.SetFormatter(new CLargeLettersFormatter());
    doc.Add("A treci od cigli...");
    cout << doc.Format() << endl;

    return 0;
}
