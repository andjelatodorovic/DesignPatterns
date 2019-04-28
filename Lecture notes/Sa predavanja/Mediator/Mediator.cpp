//
// Created by Maverick on 4/24/2017.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IPosrednik {
public:
    virtual void posalji(unsigned ID, const string& msg) = 0;
    virtual ~IPosrednik() {}
};

class User {
public:
    User(unsigned _id, string _ime) : ID(_id), ime(_ime) {}
    unsigned getID() const { return ID; }
    void udjiuSobu(IPosrednik* soba) { posrednik = soba; }

    void primiPoruku(const string& poruka) {
        //cout << "Poruku primio [" << ime << "]: " << poruka << endl;
        cout << "[" << ime << "] received" << endl;
    }

    void posaljiPoruku(unsigned id, const string& poruka) {
        cout << "[" << ime << "]: " << poruka << endl;
        posrednik->posalji(id, poruka);
    }
private:
    unsigned ID;
    string ime;
    IPosrednik* posrednik; // zna svog posrednika
};

class Chat : public IPosrednik {
public:
    void registrujKorisnika(User* korisnik) {
        korisnici.push_back(korisnik);
        korisnik->udjiuSobu(this);
    }

    void posalji(unsigned id, const string& poruka) {
        if (korisnici[id]) {
            korisnici[id]->primiPoruku(poruka);
        }
    }
    virtual ~Chat() {
        korisnici.clear();
    }
private:
    vector<User*> korisnici;
};

int main() {
    User* miki = new User(0, "kimi");
    User* marko = new User(1, "maverick");
    User* kaca = new User(2, "keti17");

    Chat* gamingRoom = new Chat();
    gamingRoom->registrujKorisnika(miki);
    gamingRoom->registrujKorisnika(marko);
    gamingRoom->registrujKorisnika(kaca);

    miki->posaljiPoruku(1, "Sta radis brate??");
    marko->posaljiPoruku(0, "Sta mislis?? Ucim OOP");
    kaca->posaljiPoruku(0, "Lazeee :D");

    return 0;
}