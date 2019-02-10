#include <iostream>
#include <cstring>
#include <string>
#include <map>

using namespace std;
/* strategija, predstavlja vestacku inteligenciju za odredjenog igraca */
class IPlayerAI {
public:
    virtual void Move() = 0;
};
/* konkretna strategija za igraca koji ima mnogo energije */
class CMainPlayerStrongAI: public IPlayerAI {
public:
    virtual void Move() {
        cout << "Glavni igrac sa mnogo energije ide da napada neprijatelje!! I skupi dijamante!!" << endl;
    }
};
/* konkretna strategija za igraca koji ima malo energije */
class CMainPlayerWeakAI: public IPlayerAI {
public:
    virtual void Move() {
        cout << "Glavni igrac ima mnogo malo energije, sakrice se od neprijatelja i traziti hranu da obnovi energiju!" << endl;
    }
};
/* konkretna strategija za protivnike koji su laksi za savladavanje */
class CEnemyStupidAI: public IPlayerAI {
public:
    virtual void Move() {
        cout << "Slucajno tragam za glavnim igracem, mozda ga i uhvatim ..." << endl;
    }
};
/* konkretna strategija za protivnike koji su tezi za savladavanje */
class CEnemySmartAI: public IPlayerAI {
public:
    virtual void Move() {
        cout << "Krecem se najkracim putem ka mestu gde je zadnji put neprijatelj bio..." << endl;
    }
};
/* igrac / kontekst
   ima dodeljenu strategiju/vestacku inteligenciju koja ce njime da upravlja */
class CPlayer {
public:
    CPlayer(const string& name, IPlayerAI* ai): m_name(name), m_energy(100), m_ai(ai) { }
    virtual void SetAI(IPlayerAI* ai) { m_ai = ai; }
    virtual void Play() {
        cout << "Igrac [" << m_name << "] na potezu. " << endl;
        m_ai->Move();
    }
    virtual int GetEnergy() { return m_energy; }
    virtual void AddEnergy(int energy) { m_energy += energy; }
    virtual void LoseEnergy(int energy) { m_energy -= energy; }
protected:
    string      m_name;
    int         m_energy;
    IPlayerAI*  m_ai;

};

/* u ovom slucaju kreiranje strategija cemo uraditi koristeci muva/flyweight obrazac */
class AIFactory {
public:
    enum AI_TYPE {
        MAIN_PLAYER_STRONG,
        MAIN_PLAYER_WEAK,
        ENEMY_STUPID,
        ENEMY_SMART
    };
    AIFactory() {}
    virtual ~AIFactory() {
        for (map<AI_TYPE, IPlayerAI*>::iterator it = m_aiCollection.begin(); it != m_aiCollection.end(); ++it) {
            delete it->second;
        }
        m_aiCollection.clear();
    }
    static AIFactory& Instance() {
        static AIFactory factory;
        return factory;
    }
    IPlayerAI* GetAI(AI_TYPE type) {
        if (m_aiCollection.find(type) == m_aiCollection.end()) {
            switch (type) {
                case MAIN_PLAYER_STRONG: m_aiCollection[type] = new CMainPlayerStrongAI(); break;
                case MAIN_PLAYER_WEAK: m_aiCollection[type] = new CMainPlayerWeakAI(); break;
                case ENEMY_STUPID: m_aiCollection[type] = new CEnemyStupidAI(); break;
                case ENEMY_SMART: m_aiCollection[type] = new CEnemySmartAI(); break;
                default: m_aiCollection[type] = new CEnemyStupidAI(); break;
            }
        }
        return m_aiCollection[type];
    }
protected:
    map<AI_TYPE, IPlayerAI*>  m_aiCollection;
};
/* kreiramo nekoliko igraca/konkteksta sa dodeljenim strategijama, napravimo simulaciju igre
   i promenimo glavnom igracu strategiju kada mu energija padne ispod nekog nivoa */
int main() {
    CPlayer mainPlayer("Aca", AIFactory::Instance().GetAI(AIFactory::MAIN_PLAYER_STRONG));
    CPlayer enemyStupid1("Monster 1 Stupid", AIFactory::Instance().GetAI(AIFactory::ENEMY_STUPID));
    CPlayer enemyStupid2("Monster 2 Stupid", AIFactory::Instance().GetAI(AIFactory::ENEMY_STUPID));
    CPlayer enemySmart("Monster 1 Smart", AIFactory::Instance().GetAI(AIFactory::ENEMY_SMART));

    mainPlayer.Play();
    enemyStupid1.Play();
    enemyStupid2.Play();
    enemySmart.Play();

    mainPlayer.LoseEnergy(80);
    if (mainPlayer.GetEnergy() < 40) {
        mainPlayer.SetAI(AIFactory::Instance().GetAI(AIFactory::MAIN_PLAYER_WEAK));
    }
    mainPlayer.Play();

    return 0;
}
