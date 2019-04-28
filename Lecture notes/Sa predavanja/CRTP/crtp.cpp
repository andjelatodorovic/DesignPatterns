//
// Created by Maverick on 4/20/2017.
//

#include <iostream>

template <typename Izvedena>
class IComparable {
private:
    friend bool operator >(const Izvedena& levi, const Izvedena& desni) {
        return desni < levi;
    }
    friend bool operator <=(const Izvedena& levi, const Izvedena& desni) {
        return !(desni < levi);
    }
    friend bool operator >=(const Izvedena& levi, const Izvedena& desni) {
        return !(desni < levi);
    }
};

template <typename T>
class Klasa : public IComparable< Klasa<T> > {
public:
    Klasa(T ini) : vred(ini) {}

private:
    friend bool operator <(const Klasa<T>& levi, const Klasa<T>& desni) { // Samo ovo i magija je tu
        return levi.vred < desni.vred;
    }
    T vred;
};

class Osoba : public IComparable<Osoba>{
public:
    Osoba(std::string ime, unsigned godine) : m_ime(ime), m_godine(godine){}
private:
    friend bool operator <(const Osoba& levi, const Osoba& desni) {
        return levi.m_godine < desni.m_godine;
    }
    std::string m_ime;
    unsigned m_godine;
};

int main() {
    if(Klasa<int>(3) < Klasa<int>(4)) {
        std::cout << "Manjee" << std::endl;
    }

    if(Klasa<int>(10) > Klasa<int>(4)) {
        std::cout << "Vece" << std::endl;
    }

    if(Osoba("Pera", 22) > Osoba("Mika", 18)) {
        std::cout << "Stariji" << std::endl;
    }
}