#include <iostream>

using namespace std;

/* ovo je ciljani interfejs, Target */
template<class T>
class Kolekcija {
public:
    virtual int uzmi(int idx) = 0;
};

template<class T> class HashMapKolekcijaAdapter;

/* ovo je klasa koju zelimo da adaptiramo, Adaptee */
template<class T>
class HashMap {
private:
    T v;
public:
    void stavi(T x) {
        cout << "Stavljam u hash mapu " << x << endl;
        v = x;
    }
    int vrednost(int key) {
        return v;
    }
    Kolekcija<T>* dajKolekciju() {
        return new HashMapKolekcijaAdapter<T>(this);
    }
};

/* klasa koja adaptira HashMap ciljanom interfejsu Kolekcija,
   metod uzmi implementira pozivom javnih metoda na instanci tipa HashMap */
template<class T>
class HashMapKolekcijaAdapter: public Kolekcija<T> {
private:
    HashMap<T> *hashMap;
public:
    HashMapKolekcijaAdapter(HashMap<T> *hashMap) {
        this->hashMap = hashMap;
    }
    int uzmi(int idx) {
        return hashMap->vrednost(idx);
    }
};

/* neki metod kojem zelimo da prosledimo nasu HashMap<int>, ali posto HashMap nije tipa Kolekcija<int>
potreban nam je adapter */
void radiNestoSaKolekcijom(Kolekcija<int> *Kolekcija) {
    cout << "radim nesto sa kolekcijom: uzeo sam vrednost " << Kolekcija->uzmi(0)<< endl;
}

int main() {
    HashMap<int> *hashMap = new HashMap<int>();
    hashMap->stavi(143);
    /* u ovom slucaju smo stavili da HashMap moze sama da vrati adaptiranu verziju sebe pomocu metoda
    dajKolekciju koja vraca instancu adaptera */
    Kolekcija<int> *kolekcija = hashMap->dajKolekciju();
    radiNestoSaKolekcijom(kolekcija);

    delete kolekcija;
    delete hashMap;
    return 0;
}
