#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T> class TreeIterator;

/* kreiracemo agregat drvo koje moze da cuva vrednosti tipa T,
   drvo ima decu koja su podstabla, metod za dodavanje deteta sa parametrima id i drvo koje se ubacuje,
   to drvo se doda kao dete na cvor sa identifikatorom id,
   svaki cvor ima i pokazivac na oca/parent kako bi mogli da obilazimo drvo */
template <class T>
class Tree {
public:
    typedef typename vector<Tree<T>* >::iterator TreeVectorIter;
    friend class TreeIterator<T>;
    Tree(T value, const string& id, Tree<T>* parent = NULL): m_value(value), m_id(id), m_parent(parent) { }
    ~Tree() {
        for (TreeVectorIter it = m_children.begin(); it != m_children.end(); ++it) {
            delete *it;
        }
    }
    bool AddChild(const string& id, Tree<T>* tree) {
        if (m_id == id) {
            m_children.push_back(tree);
            tree->m_parent = this;
            return true;
        }
        for (TreeVectorIter it = m_children.begin(); it != m_children.end(); ++it) {
            if ((*it)->AddChild(id, tree)) return true;
        }
        return false;
    }
    string Print() { return m_id; }
    /* metod za kreiranje iteratora */
    TreeIterator<T>* CreateIterator() {
        return new TreeIterator<T>(this);
    }
protected:
    T                   m_value;
    string              m_id;
    vector<Tree<T>* >   m_children;
    Tree<T>*            m_parent;
    /* metod koji vraca naredno dete u listi dece koje je nakon deteta child u listi */
    Tree<T>* NextChild(Tree<T>* child) {
        for (unsigned int idx = 0; idx < m_children.size() - 1; ++idx) {
            if (m_children[idx] == child) return m_children[idx + 1];
        }
        return NULL;
    }
};
/* iterator kroz drvo, obilazi ga po metodu post-fix / prvo se obilaze deca a na kraju se obilazi koren drveta/stabla */
template <class T>
class TreeIterator {
public:
    /* kada se kreira iterator postavimo ga na prvi element, a to je cvor na 'dnu' stabla, tj. rekurzivno cemo da se spustamo
       uz prvo dete dok ne dodjemo do kraja stabla */
    TreeIterator(Tree<T>* root) { m_root = root; First(); }
    /* postavlja iterator na prvi element stabla a to je cvor koji dobijemo kada se neprekidno spustamo uz prvo dete sve dok
       cvor ima dece */
    void First() {
        m_current = m_root;
        while (m_current->m_children.size() > 0) m_current = m_current->m_children[0];
    }
    /* sledeci cvor racunamo na sledeci nacin:
       ako je trenutni cvor NULL bacamo izuzetak
       ako je trenutni cvor koren stabla koje obilazimo naredni je NULL
       ako ne postoji naredno dete od oca cvora m_current onda je naredni cvor otac od m_current
          (obisli smo celo podstablo od oca od m_current, sada je red na koren podstabla)
       ako postoji naredno dete next od oca m_current->m_parrent onda je naredni cvor najnize dete od tog cvora next
       (silazimo po prvom detetu sve dok ne dodjemo do cvora bez naslednika) */
    void Next() {
        if (m_current == NULL) throw("End of the tree");
        if (m_current == m_root) {
            m_current = NULL;
        } else {
            Tree<T>* next = m_current->m_parent->NextChild(m_current);
            if (next == NULL) {
                m_current = m_current->m_parent;
            } else {
                m_current = next;
                while (m_current->m_children.size() > 0) m_current = m_current->m_children[0];
            }
        }
    }
    bool IsDone() {
        return m_current == NULL;
    }
    T& Current() { return m_current->m_value; }
protected:
    Tree<T>*    m_root;
    Tree<T>*    m_current;
};

/* drvo koje cemo da kreiramo je:
        0
    /--------\
    1         9
 /--|--\        \
 2  3   4         10
      /---|---\
      5   6    7
          |
          8
 pa kad obilazimo drvo post-fix strategijom (koren stabla se obilazi nakon obilaska dece) dobijamo:
 2 3 5 8 6 7 4 1 10 9 0
 */
int main() {
    Tree<int>* root = new Tree<int>(0, "0");
    root->AddChild("0", new Tree<int>(1, "1"));
    root->AddChild("1", new Tree<int>(2, "2"));
    root->AddChild("1", new Tree<int>(3, "3"));
    root->AddChild("1", new Tree<int>(4, "4"));
    root->AddChild("4", new Tree<int>(5, "5"));
    root->AddChild("4", new Tree<int>(6, "6"));
    root->AddChild("4", new Tree<int>(7, "7"));
    root->AddChild("6", new Tree<int>(8, "8"));
    root->AddChild("0", new Tree<int>(9, "9"));
    root->AddChild("9", new Tree<int>(10, "10"));

    for (TreeIterator<int>* it = root->CreateIterator(); !it->IsDone(); it->Next()) {
        cout << it->Current() << endl;
    }
    delete root;
    return 0;
}
