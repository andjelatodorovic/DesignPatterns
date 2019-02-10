#include <iostream>
#include <memory>

using namespace std;

/* kompleksan podsistem - CPU */
class CPU {
public:
    void ukljuci() {
        cout << "CPU ukljucen" << endl;
    }
    void iskljuci() {
        cout << "CPU iskljucen" << endl;
    }
};
/* kompleksan podsistem - Memorija */
class Memorija {
public:
    void ukljuci() {
        cout << "Memorija ukljucena" << endl;
    }
    void iskljuci() {
        cout << "Memorija iskljucena" << endl;
    }
};
/* kompleksan podsistem - hard disk */
class Disk {
public:
    void ukljuci() {
        cout << "Disk ukljucen" << endl;
    }
    void iskljuci() {
        cout << "Disk iskljucen" << endl;
    }
};
/* fasada - ona komunicira sa podsistemima */
class Kompjuter {
public:
    Kompjuter() {
        m_cpu = new CPU();
        m_memorija = new Memorija();
        m_disk = new Disk();
    }
    ~Kompjuter() {
        delete m_cpu;
        delete m_memorija;
        delete m_disk;
    }
    void ukljuci() {
        cout << "Ukljucujem kompjuter ..." << endl;
        m_cpu->ukljuci();
        m_memorija->ukljuci();
        m_disk->ukljuci();
        cout << "Kompjuter ukljucen." << endl;
    }
    void iskljuci() {
        cout << "Iskljucujem kompjuter ..." << endl;
        m_disk->iskljuci();
        m_memorija->iskljuci();
        m_cpu->iskljuci();
        cout << "Kompjuter iskljucen." << endl;
    }
private:
    CPU*        m_cpu;
    Memorija*   m_memorija;
    Disk*       m_disk;
};

int main() {
    unique_ptr<Kompjuter> kompjuter(new Kompjuter());
    kompjuter->ukljuci();
    cout << endl << endl;
    kompjuter->iskljuci();

    return 0;
}
