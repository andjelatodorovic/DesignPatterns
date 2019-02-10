/* primer preuzet sa https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Iterator */

#include <iterator>
#include <vector>
#include <set>
#include <iostream>
#include <string>

using namespace std;

/* iterator nad vektor agregatom Aggregate, koji je implementiran koristeci klasu vector iz STL
   T je tip elemenata koji se cuvaju u agregatu a U je tip konkrentog agregata za koji je iterator kreiran
   internoj strukturi mozemo da pristupamo (m_pData->m_data) zato sto je Iterator napravljen prijateljem klase U
   Iterator je jednostavno omotac/wrapper oko klasicnog iteratora dobijenog iz klase vector iz standardne biblioteke STL
   pa koristi njegove metode da bi iplementirao metode first, next...*/
template<class T, class U>
class Iterator {
public:
	typedef typename vector<T>::iterator iter_type;
	Iterator(U *pData): m_pData(pData) {
		m_it = m_pData->m_data.begin();
	}
	void first() {
		m_it = m_pData->m_data.begin();
	}
	void next() {
	    if (m_it != m_pData->m_data.end()) m_it++;
	}
	bool isDone() {
		return (m_it == m_pData->m_data.end());
	}
	iter_type current() {
		return m_it;
	}
private:
	U*          m_pData;
	iter_type   m_it;
};
/* iterator nad skupom, koji je uredjen i implementiran koristeci klasu set iz STL
   T je tip elemenata koji se cuvaju u skupu, U je klasa sa metodom za uporedjivanje dva
   elementa skupa, A a je tip konkretnog agregata nad kojim je napravljen SetIterator
   internoj strukturi mozemo da pristupamo (m_pData->m_data) zato sto je Iterator napravljen prijateljem klase A
   SetIterator je jednostavno omotac/wrapper oko klasicnog iteratora dobijenog iz klase set iz standardne biblioteke STL
   pa koristi njegove metode da bi iplementirao metode first, next...*/
template<class T, class U, class A>
class SetIterator {
public:
	typedef typename std::set<T, U>::iterator iter_type;
	SetIterator(A *pData): m_pData(pData) {
		m_it = m_pData->m_data.begin();
	}
	void first() {
		m_it = m_pData->m_data.begin();
	}
	void next() {
	    if (m_it != m_pData->m_data.end()) m_it++;
	}
	bool isDone() {
		return (m_it == m_pData->m_data.end());
	}
	iter_type current() {
		return m_it;
	}

private:
	A*          m_pData;
	iter_type	m_it;
};
/* obican agregat, implementiran koristeci klasu vector iz standardne biblioteke STL,
   T je tip elemenata koji se cuvaju u agregatu
   create_iterator kreira iterator nad vektorom, tip je Iterator<T, Aggregate>
   pristup internoj strukturi je omogucen tako sto je Iterator napravljen prijateljem klase */
template <class T>
class Aggregate {
	friend class Iterator<T, Aggregate>;
public:
	void add(T a) {
		m_data.push_back(a);
	}
	Iterator<T, Aggregate> *create_iterator() {
		return new Iterator<T, Aggregate>(this);
	}
private:
	std::vector<T> m_data;
};
/* agregat nad uredjenim skupom, koristi klasu set iz standardne biblioteke STL kao podlogu za
   implementaciju kolekcije,
   T je klasa za tip elementa koji ce da cuva u kolekciji, a U je klasa sa metodom za uporedjivanje
   dva elementa u skupu
   metod create_iterator kreira iterator nad skupom, tip je SetIterator<T, U, AggregateSet>
   pristup internoj strukturi je omogucen tako sto je SetIterator napravljen prijateljem klase */
template <class T, class U>
class AggregateSet {
	friend class SetIterator<T, U, AggregateSet>;
public:
	void add(T a) {
		m_data.insert(a);
	}
	SetIterator<T, U, AggregateSet> *create_iterator() {
		return new SetIterator<T, U, AggregateSet>(this);
	}
	void Print() {
		copy(m_data.begin(), m_data.end(), std::ostream_iterator<T>(cout, "\n"));
	}
private:
	std::set<T, U> m_data;
};
/* tip koji mozemo da cuvamo u kolekciji, samo wrapper/omotac oko int tipa, m_data */
class Money {
public:
	Money(int a = 0): m_data(a) {}

	void SetMoney(int a) {
		m_data = a;
	}
	int GetMoney() {
		return m_data;
	}
private:
	int m_data;
};
/* tip koji cemo da cuvamo u nekoj od kolekcija, samo je wrapper nad string tipom, m_name */
class Name {
public:
	Name(string name): m_name(name) {}

	const string &GetName() const {
		return m_name;
	}
	friend ostream &operator<<(ostream& out, const Name& name) {
		out << name.GetName();
		return out;
	}
private:
	string m_name;
};
/* klasa za uporedjivanje dva objekta tipa Name, koristi operator uporedjivanja nad
   stringovima */
struct NameLess {
	bool operator()(const Name &lhs, const Name &rhs) const {
		return (lhs.GetName() < rhs.GetName());
	}
};

int main() {
	/* kreiramo Aggregate (wrapper za vector) da cuva int tip, dodamo nekoliko brojeva */
	cout << "________________Iterator with int______________________________________" << endl;
	Aggregate<int> agg;

	for (int i = 0; i < 10; i++)
		agg.add(i);
    /* kreiramo iterator nad Aggregate<int> i standardno ga koristimo u petlji for */
	Iterator<int, Aggregate<int> > *it = agg.create_iterator();
	for (it->first(); !it->isDone(); it->next())
		cout << *it->current() << endl;

	/* kreiramo Aggregate da cuva tip Money (wrapper za int), dodamo nekoliko elemenata */
	Aggregate<Money> agg2;
	Money a(100), b(1000), c(10000);
	agg2.add(a);
	agg2.add(b);
	agg2.add(c);

	cout << "________________Iterator with Class Money______________________________" << endl;
	/* kreiramo iterator nad Aggregate<Money> i opet ga klasicno koristimo */
	Iterator<Money, Aggregate<Money> > *it2 = agg2.create_iterator();
	for (it2->first(); !it2->isDone(); it2->next())
		cout << it2->current()->GetMoney() << endl;


	cout << "________________Set Iterator with Class Name______________________________" << endl;
    /* kreiramo AggregateSet (wrapper za set iz STL) da cuva tip Name, operator uporedjivanja je iz klase NameLess */
	AggregateSet<Name, NameLess> aset;
	/* dodamo nekoliko elemenata */
	aset.add(Name("Qmt"));
	aset.add(Name("Bmt"));
	aset.add(Name("Cmt"));
	aset.add(Name("Amt"));
    /* kreiramo iterator nad skupom, i koristimo ga na klasican nacin
       kada stampamo obidjene elemente vidimo da su uredjeni u rastucem redosledu */
	SetIterator<Name, NameLess, AggregateSet<Name, NameLess> > *it3 = aset.create_iterator();
	for (it3->first(); !it3->isDone(); it3->next())
		cout << (*it3->current()) << endl;

    return 0;
}
