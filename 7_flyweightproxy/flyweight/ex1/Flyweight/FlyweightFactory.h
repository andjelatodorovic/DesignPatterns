#ifndef __FLYWEIGHTFACTORY_H
#define __FLYWEIGHTFACTORY_H

#include <map>

using namespace std;

#include "ConcreteFlyweight.h"
/* flyweight / fabrika muva
   klijent koristi fabriku da dobije objekte tipa ConcreteFlyweight (konkretne muve)*/
class FlyweightFactory {
public:
    FlyweightFactory() {}
    ~FlyweightFactory() {
        while (m_keyToFlyweight.begin() != m_keyToFlyweight.end()) {
            if (m_keyToFlyweight.begin()->second != NULL) {
                delete m_keyToFlyweight.begin()->second;
            }
            m_keyToFlyweight.erase(m_keyToFlyweight.begin());
        }
    }
    /* metod za dobijanje konkretne muve koju moze da deli vise klijenata */
    Flyweight* GetFlyweight(string key) {
        if (m_keyToFlyweight.find(key) == m_keyToFlyweight.end()) {
            m_keyToFlyweight[key] = new ConcreteFlyweight(key);
        }
        return m_keyToFlyweight[key];
    }
private:
    map<string, Flyweight*> m_keyToFlyweight;
};

#endif // __FLYWEIGHTFACTORY_H
