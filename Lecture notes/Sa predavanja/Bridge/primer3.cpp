//
// Created by Maverick on 4/18/2017.
//
#include <iostream>
using namespace std;

template <typename T>
struct Cvor {
    T info;
    Cvor<T>* sled;
    Cvor(T n_info, Cvor<T>* n_sled = 0) : info(n_info), sled(n_sled){}
};

/*
 * Implementacija (I)
 * U onom primeru `Slikar`.
 */

template <typename T>
class Imemorija {
public:
    virtual void dodaj(T) = 0;
    virtual T uzmi() = 0;
};

/*
 * Implementator (K)
 * Konkretni implementator `Pikaso, DaVinci`.
 */

template <typename T>
class LancanaLista : public Imemorija<T> {
public:
    bool jePrazna() { return glava == 0; }
    LancanaLista() : glava(0) {}

    void dodaj(T info) {
        glava = new Cvor<T>(info, glava);
    }

    T uzmi() {
        T tmp = glava->info;
        Cvor<T>* p = glava;
        glava = glava->sled;
        delete p;
        return tmp;
    }

    ~LancanaLista() {
        while(glava) {
            Cvor<T>* p = glava;
            glava = glava->sled;
            delete p;
        }
    }

private:
    Cvor<T>* glava;
};

/*
 * Implementator (K)
 * Konkretni implementator `Pikaso, DaVinci`.
 */

template <typename T>
class Niz : public Imemorija<T> {
public:
    Niz() : ptr(new T[10]), topInd(0), trenVel(10){}
    void dodaj(T info) {
        if(topInd == trenVel) realociraj();
        ptr[topInd++] = info;
    }
    T uzmi(){ return ptr[--topInd]; }
    ~Niz() { delete [] ptr; }
private:
    T* ptr;
    int topInd;
    int trenVel;

    void realociraj() {
        T* p = new T[trenVel << 1];
        for(int i = 0; i<trenVel; ++i) p[i] = ptr[i];
        trenVel <<=1;
        delete [] ptr;
        ptr = p;
    }
};


/*
 * Agregacija (I)
 * U primeru `Slika`.
 */

template <typename T>
class MemorijaAgr {
public:
    virtual void push(T) = 0;
    virtual T pop() = 0;
};

/*
 * Agregacija (K)
 * Konkretna agrekacija `Portret`.
 */

template <typename T, template <typename> class Memorija>
class StekAgr : public MemorijaAgr<T> {
public:
    void push(T info){ mem.dodaj(info); }
    T pop() { return mem.uzmi(); }

private:
    Memorija<T> mem;
};

// ALTERNATIVA:
// template <typename T, template <typename> class Memorija>
// class StekAgr : public MemorijaAgr<T>, private Memorija<T> {
// public:
//    void push(T info){ Memorija<T>::dodaj(info); }
//    T pop() { return Memorija<T>::uzmi(); }
//
// };

int main() {
    StekAgr<int, Niz> n;
    StekAgr<int, LancanaLista> ll;
    for (int i = 1; i <= 10; ++i) {
        n.push(i);
        ll.push(i);
    }
    for (int i = 1; i <= 10; ++i) {
        cout << "Niz: " << n.pop() << " | LL: " << ll.pop() << endl;
    }
}
