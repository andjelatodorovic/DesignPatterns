#include <map>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Player;
/* posmatrac / observer, graficki element u igrici, npr. ikonica koja prikazuje preostalu energiju igraca
   zeli da prati promenen na subjektu, u ovom slucaju igraci u igrici
   i da na osnovu njihovih internih stanja/energije prikaze na odgovarajuci nacin to stanje graficki */
class Widget {
public:
    Widget(const string& name = ""): m_name(name), m_content("") {}
    virtual ~Widget() {}
    virtual void Notify(Player& player) = 0;
    virtual void Display() { cout << "[" << m_name << "] > " << m_content << endl; }
protected:
    string  m_name;
    string  m_content;
};
/* subjekt, igrac u igrici
  ima metode za promenu internog stanja/energije, pomocu Eat povecava energiju kada jede hranu
  i Hit kada je pogodjen i izgubi deo energije
  u oba slucaja interno se zove metod za obavestavanje svih registrovanih posmatraca */
class Player {
public:
    typedef map<Widget* const, Widget* const> WidgetMap;

    Player(const string& name = ""): m_name(name), m_energy(100) {}
    virtual void Register(Widget& widget) {
        m_widgets.insert(WidgetMap::value_type(&widget, &widget));
    }
    virtual void UnRegister(Widget& widget) {
        m_widgets.erase(&widget);
    }
    virtual void Eat(int food) {
        if (m_energy <= 0) return;
        m_energy += food;
        if (m_energy > 100) m_energy = 100;
        NotifyAll();
    }
    virtual void Hit(int damage) {
        if (m_energy <= 0) return;
        m_energy -= damage;
        if (m_energy < 0) m_energy = 0;
        NotifyAll();
    }
    virtual int GetEnergy() { return m_energy; }
protected:
    virtual void NotifyAll() {
        for (WidgetMap::iterator it = m_widgets.begin(); it != m_widgets.end(); ++it) {
            it->second->Notify(*this);
        }
    }
    WidgetMap   m_widgets;
    string      m_name;
    int         m_energy;
};

string toString(int num) { ostringstream out; out << num; return out.str(); }
/* konkretni posmatrac, ikonica energije */
class IconWidget: public Widget {
public:
    IconWidget(const string& name = ""): Widget(name) {}
    virtual ~IconWidget() {}
    virtual void Display() {
        cout << "Icon [" << m_name << "] showing " << m_content << "% energy" << endl;
    }
    virtual void Notify(Player& player) {
        m_content = toString(player.GetEnergy());
        Display();
    }
};
/* kreiramo sva subjekta, 'prikacimo' im posmatrace koje su ikonice za prikaze preostale energije,
   simuliramo gubljenje/obnavljanje energije i pratimo tok izvrsavanja */
int main() {
    Player aca("Aca");
    Player braca("Braca");

    IconWidget heartAca("Heart image Player A");
    IconWidget heartBraca("Heart image Player B");

    aca.Register(heartAca);
    braca.Register(heartBraca);

    aca.Hit(50);
    braca.Eat(70);
    aca.Hit(20);
    braca.Hit(80);
    aca.Eat(30);
    braca.Hit(10);

    aca.UnRegister(heartAca);
    braca.Register(heartAca);
    braca.Eat(50);
    braca.UnRegister(heartBraca);
    braca.Hit(20);

    return 0;
}
