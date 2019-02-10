#include <iostream>
#include <algorithm>

using namespace std;

/* apstraktna strategija za uporedjivanje elemenata tipa T */
template <class T>
class IComparator {
public:
    virtual int Compare(const T& a, const T& b) = 0;
};
/* konkretna strategija za uporedjivanje elemenata tipa T
   tako da omogucava sortiranje u rastucem poretku */
template <class T>
class CAscComparator: public IComparator<T> {
public:
    virtual int Compare(const T& a, const T& b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }
};
/* konkretna strategija za uporedjivanje elemenata tipa T
   tako da omogucava sortiranje u opadajucem poretku */
template <class T>
class CDescComparator: public IComparator<T> {
public:
    virtual int Compare(const T& a, const T& b) {
        if (a < b) return 1;
        if (a > b) return -1;
        return 0;
    }
};
/* apstraktna strategija za sortiranje niza ciji su elementi tipa T
   objedinjuje razlicite algoritme za sortiranje niza
   metodu Sort se prosledjuje pored duzine niza i niza elemenata takodje
   i konkretna strategija za uporedjivanje dva elementa niza */
template <class T>
class ISortStrategy {
public:
    ISortStrategy() { }
    virtual ~ISortStrategy() { }
    virtual void Sort(int n, T data[], IComparator<T>& comparator) = 0;
};
/* konkretna strategija koja implementira bubble sort algoritam za sortiranje */
template <class T>
class CBubbleSortStrategy: public ISortStrategy<T> {
public:
    CBubbleSortStrategy() {}
    virtual ~CBubbleSortStrategy() { }
    virtual void Sort(int n, T data[], IComparator<T>& comparator) {
        for (int k = 0; k < n; k ++) {
            for (int i = 0; i < n - 1; i ++) {
                if (comparator.Compare(data[i], data[i + 1]) > 0) {
                    swap(data[i], data[i+1]);
                }
            }
        }
    }
};
/* konkretna strategija koja implementira insertion sort algoritam za sortiranje */
template <class T>
class CInsertionSortStrategy: public ISortStrategy<T> {
public:
    CInsertionSortStrategy() {}
    virtual ~CInsertionSortStrategy() { }
    virtual void Sort(int n, T data[], IComparator<T>& comparator) {
        for (int i = 1; i < n; i ++) {
            for (int j = i - 1; j >= 0; j --) {
                if (comparator.Compare(data[j], data[j + 1]) > 0) {
                    swap(data[j], data[j + 1]);
                } else {
                    break;
                }
            }
        }
    }
};

#define MAXCAP 1000
/* kontekst,
   ima dva objekta konkretnih strategija za sortiranje kao i za uporedjivanje elemenata niza
   mozemo da menjamo bilo koju od ovih strategija
   prilikom poziva metoda Sort na vektoru/kontekstu poziva se metod Sort na dodeljenoj konkretnoj
   strategiji za sortiranje sa prosledjenim objektom strategije za uporedjivanje elemenata
   na ovaj nacin imamo neku vrstu eksponencijalnosti efekta
   ako imamo n razlicitih strategija za sortiranje i m razlicitih strategija za uporedjivanje
   imacemo n * m razlicitih efekata dobijenih kao kombinacija dve strategije */
template <class T>
class Vector {
public:
    Vector(): m_size(0) {
        m_data = new T[MAXCAP];
        m_sorter = new CBubbleSortStrategy<T>();
        m_comparator = new CAscComparator<T>(); }
    virtual ~Vector() { delete m_data; if (m_sorter != NULL) delete m_sorter; if (m_comparator != NULL) delete m_comparator; }
    virtual void Add(T data) { m_data[m_size++] = data; }
    virtual void SetSorter(ISortStrategy<T>* sorter) {
        if (m_sorter != NULL) delete m_sorter;
        m_sorter = sorter;
    }
    virtual void SetComparator(IComparator<T>* comparator) {
        if (m_comparator != NULL) delete m_comparator;
        m_comparator = comparator;
    }
    virtual void Sort() {
        m_sorter->Sort(m_size, m_data, *m_comparator);
    }
    virtual void Print() {
        cout << "[";
        for (unsigned int i = 0; i < m_size; i ++) {
            if (i == 0) cout << m_data[i];
            else cout << " " << m_data[i];
        }
        cout << "]" << endl;
    }

protected:
    T*                      m_data;
    int                     m_size;
    ISortStrategy<T>*       m_sorter;
    IComparator<T>*         m_comparator;
};
/* kreiramo vektor, zatim dodamo par elemenata i pozovemo metod Sort,
   u konstruktoru za Vector postavicemo neke osnovne strategije za sortiranje i uporedjivanje,
   sortiramo niz i prikazemo sadrzaj niza, zatim dodamo jos neke elemente, promenimo
   strategiju za uporedjivanje, sortiramo i opet prikazemo niz itd. */
int main() {
    Vector<int> v;
    v.Add(8);
    v.Add(4);
    v.Add(3);
    v.Print();
    v.Sort();
    v.Print();


    v.Add(5);
    v.Add(6);

    v.SetComparator(new CDescComparator<int>());
    v.Sort();
    v.Print();

    v.Add(7);
    v.Add(9);
    v.Print();

    v.SetComparator(new CAscComparator<int>());
    v.SetSorter(new CInsertionSortStrategy<int>());
    v.Sort();
    v.Print();

    return 0;
}
