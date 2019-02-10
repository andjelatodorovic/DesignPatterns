#include <iostream>
#include <vector>

using namespace std;

/* podsetnik/memento
   cuva stanje subjekta/originator-a number a to je samo broj kao rezultat nekih operacija */
class Memento {
public:
    Memento(int state) { m_state = state; }
    int GetState() { return m_state; }
protected:
    int     m_state;
};

/* subjekt/originator
   ima interno stanje koje je trenutna vrednost rezultata,
   nudi metod za izmenu internog stanja, Operation kojim se vrsi neka operacija nad trenutnim rezultatom
   i nudi metode za uzimanje podsetnika sa sacuvanim trenutnim stanjem,
   kao i metod za povracaj stanja koriscenjem prosledjenog podsetnika */
class Number {
public:
    Number(int value) { m_state = value; }
    void Operation(char op, int value) {
        switch (op) {
            case '+': Add(value); break;
            case '-': Sub(value); break;
            case '*': Mul(value); break;
            case '/': Div(value); break;
        }
    }
    void Display() { cout << m_state << endl; }
    void Restore(Memento* memento) { m_state = memento->GetState(); }
    Memento* CreateMemento() { return new Memento(m_state); }
protected:
    void Add(int value) { m_state += value; }
    void Sub(int value) { m_state -= value; }
    void Mul(int value) { m_state *= value; }
    void Div(int value) { m_state /= value; }
    int     m_state;
};
/* cuvar podsetnika/caretaker
   ima listu sacuvanih podsetnika/memento-a
   i omogucava operaicju undo nad subjektom */
class Caretaker {
public:
    ~Caretaker() {
        for (vector<Memento*>::iterator it = m_memento.begin(); it != m_memento.end(); ++it) {
            delete *it;
        }
    }
    Memento* GetLastMemento() {
        if (m_memento.size() == 0) throw("No more mementos");
        Memento* memento = m_memento.back();
        m_memento.pop_back();
        return memento;
    }
    void AddMemento(Memento* memento) {
        m_memento.push_back(memento);
    }
protected:
    vector<Memento*>   m_memento;
};
/* simulacija gde mozemo da vrsimo razlicite aritmeticke operacije nad subjektom Number
   imamo i operaciju undo */
int main() {
    cout << "Startna vrednost: ";
    int value;
    cin >> value;
    Number number(value);
    Caretaker caretaker;
    char op;
    do {
        cout << "Operation [+-*/ value], [u] undo, [q] quit >";
        cin >> op;
        try {
            if (op == 'u' || op == 'U') {
                number.Restore(caretaker.GetLastMemento());
                number.Display();
            } else if (op == 'q' || op == 'Q') {
                break;
            } else {
                cin >> value;
                caretaker.AddMemento(number.CreateMemento());
                number.Operation(op, value);
                number.Display();
            }
        } catch (const char* e) {
            cout << "ERROR: " << e << endl;
        }
    } while (true);

    return 0;
}
