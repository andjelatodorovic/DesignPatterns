#ifndef __SUBJECT_H
#define __SUBJECT_H

#include <vector>
#include <algorithm>

#include "Observer.h"

using namespace std;

/* apstraktni subjekat / subject
   nad subjektom mogu da se izvrsavaju neke operacije, subjekat moze da menja svoje interno stanje
   postoje objekti koji su mozda zaintersovani da znaju kada je subjekat promenio svoje interno stanje
   umesto da ti objekti neprestano (nakon nekog vremenskog intervala) pitaju subjekt da li je promenio stanje
   koriscenjem obrasca posmatrac, ti objekti/posmatraci/observers se registruju kod subjekta kako
   zele da prate njegove promene
   subjekat nudi metod Attach/register/prikaci se koji omogucava posmatracu/observer da bude registrovan
   kod subjekta da ga subjekt obavesti kada su se desile neke promene od interesa
   metod Detach sluzi posmatracu da se odregistruje od subjekta da vise ne zeli da prima obavestenja o
   promenama na subjektu
   metod Notify na subjektu se poziva kada se desila neka promena na subjektu takva da posmatraci
   subjekta trebaju da budu obavesteni o toj promeni
   metod Notify jednostavno prodje kroz listu registrovanih posmatraca i na njima pozove neki metod
   u ovom slucaju Update(this) sa prosledjenim subjektom na kom se desila promena od interesa */
class Subject {
public:
    Subject() {}
    virtual ~Subject() {}
    virtual void Attach(Observer* observer) {
        m_observers.push_back(observer);
    }
    virtual void Detach(Observer* observer) {
        vector<Observer*>::iterator it = find(m_observers.begin(), m_observers.end(), observer);
        if (it != m_observers.end()) {
            m_observers.erase(it);
        }
    }
    virtual void Notify() {
        for (vector<Observer*>::iterator it = m_observers.begin(); it != m_observers.end(); ++it) {
            (*it)->Update(this);
        }
    }
    virtual string GetState() = 0;
    virtual void SetState(const string& state) = 0;
protected:
    vector<Observer*>   m_observers;
};

#endif // __SUBJECT_H
