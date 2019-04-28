//
// Created by Maverick on 4/24/2017.
//

#include <iostream>
#include <list>
#include <string>

using namespace std;

class IPosetilac;

class IDokument {
public:
    IDokument(const string& str) : tekst(str) {}
    virtual ~IDokument() {}
    void setTekst(const string& s) { tekst = s; }
    string getTekst() const { return tekst; }
    virtual void docekaj(IPosetilac* p) const = 0;
protected:
    string tekst;
};

template <typename Izvedena>
class Posetnik : public IDokument {
public:
    Posetnik(const string& s) : IDokument(s) {}
    virtual ~Posetnik() {}
    virtual void docekaj(IPosetilac* p) const;
};

class Tekst : public Posetnik<Tekst> {
public:
    Tekst(const string& s) : Posetnik<Tekst>(s) {}

    void docekaj(IPosetilac *p) const;
};

class BoldTekst : public Posetnik<BoldTekst> {
public:
    BoldTekst(const string& s) : Posetnik<BoldTekst>(s) {}

    void docekaj(IPosetilac *p) const;
};

class Hyperlink : public Posetnik<Hyperlink> {
public:
    Hyperlink(const string& s, const string _url) : Posetnik<Hyperlink>(s), url(_url) {}
    string getUrl() const { return url; }
private:
    string url;

    void docekaj(IPosetilac *p) const;
};

class Dokument : public list<IDokument*> {
public:
    typedef list<IDokument*> base;
    void docekaj(IPosetilac* posetilac) const {
        for (base::const_iterator itr = begin(); itr != end(); ++itr) {
            (*itr)->docekaj(posetilac);
        }
    }
};

class IPosetilac {
public:
    IPosetilac() : output("") {}
    virtual ~IPosetilac() {}
    virtual void Poseti(const Tekst*) = 0;
    virtual void Poseti(const BoldTekst*) = 0;
    virtual void Poseti(const Hyperlink*) = 0;
    string get() const { return output; }
protected:
    string output;
};

class HTMLPosetilac : public IPosetilac {
public:
    HTMLPosetilac() :IPosetilac() {}
    virtual ~HTMLPosetilac() {}
    virtual void Poseti(const Tekst *deo) {
        output += deo->getTekst();
    }
    virtual void Poseti(const BoldTekst *deo) {
        output += "<b>" + deo->getTekst() + "</b>";
    }
    virtual void Poseti(const Hyperlink *deo) {
        output += "<a href=\"" + deo->getUrl() + "\">" + deo->getTekst() + "</a>";
    }
};

class LaTeXPosetilac : public IPosetilac {
public:
    LaTeXPosetilac() :IPosetilac() {}
    virtual ~LaTeXPosetilac() {}
    virtual void Poseti(const Tekst *deo) {
        output += deo->getTekst();
    }
    virtual void Poseti(const BoldTekst *deo) {
        output += "\\textbf{" + deo->getTekst() + "}";
    }
    virtual void Poseti(const Hyperlink *deo) {
        output += "\\href{" + deo->getUrl() + "}{" + deo->getTekst() + "}";
    }
};

void Tekst::docekaj(IPosetilac* p) const {
    p->Poseti(this);
}
void BoldTekst::docekaj(IPosetilac* p) const {
    p->Poseti(this);
}
void Hyperlink::docekaj(IPosetilac *p) const {
    p->Poseti(this);
}

template <typename Izvedena>
void Posetnik<Izvedena>::docekaj(IPosetilac* p) const {
    p->Poseti(static_cast<const Izvedena*>(this));
};

int main() {
    Dokument* d = new Dokument();

    d->push_back(new BoldTekst("Naslov"));
    d->push_back(new Hyperlink("Google", "www.google.com"));
    d->push_back(new Tekst("Lorem ipsum"));

    HTMLPosetilac* html = new HTMLPosetilac();
    d->docekaj(html);
    cout << html->get() << endl;

    LaTeXPosetilac* latex = new LaTeXPosetilac();
    d->docekaj(latex);
    cout << latex->get() << endl;
    return 0;
}