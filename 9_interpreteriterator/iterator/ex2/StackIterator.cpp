#include <iostream>
using namespace std;

template<class T>
class StackIterator;

/* konkretan agregat,
   neka verzija steka, koristimo obican niz za implementaciju kolekcije,
   ima metod CreateIterator za kreiranje iteratora nad kolekcijom
   T je za tip podataka koje cemo da cuvamo u steku
   StackIterator je napravljen prijateljem kako bi pristupao zasticenom polju m_data */
template<class T>
class Stack {
public:
    friend class StackIterator<T>;
    Stack() { m_last = -1; }
    void Push(const T &item) { m_data[++m_last] = item; }
    T& Pop() { return m_data[m_last--]; }
    bool IsEmpty() { return (m_last == -1); }
    StackIterator<T> *CreateIterator() const;
protected:
    static const int    STACK_CAPACITY = 1000;
    T                   m_data[STACK_CAPACITY];
    int                 m_last;
};

/* konkretan iterator nad stekom,
   ima sve klasicne metode za iterator
   metodi su odradjeni na klasican nacin, drugi primer prikazuje kako da se urade koriscenjem operatora */
template<class T>
class StackIterator {
public:
    StackIterator(const Stack<T> *s) { m_stack = s; }
    void First() { m_current = 0; }
    void Next() { m_current++; }
    bool IsDone() { return m_current == m_stack->m_last + 1; }
    const T& CurrentItem() {
        if (m_current <= m_stack->m_last) {
            return m_stack->m_data[m_current];
        } else {
            throw("Current Item out of bounds");
        }
    }
protected:
    const Stack<T>*     m_stack;
    int                 m_current;
};

template<class T>
StackIterator<T> *Stack<T>::CreateIterator() const {
    return new StackIterator<T>(this);
}

/* uporedicemo dva steka koristeci iteratore jednog i drugog da prodjemo element po element
   i ako su svi jednaki i istog broja stekovi su jednaki */
template<class T>
bool operator==(const Stack<T> &l, const Stack<T> &r) {
    StackIterator<T> *itl = l.CreateIterator();
    StackIterator<T> *itr = r.CreateIterator();
    for (itl->First(), itr->First();
        !itl->IsDone() && !itr->IsDone();
        itl->Next(), itr->Next())
        if (itl->CurrentItem() != itr->CurrentItem())
        break;
    bool ret = itl->IsDone() && itr->IsDone();
    delete itl;
    delete itr;
    return ret;
}
/* kreiramo stek, zatim ga iskopiramo u nekoliko stekova, neke od njih izmenimo (izbacimo ili dodamo element)
   i nakon toga prikazemo rezultat uporedjivanja stekova */
int main() {
    Stack<int> stack1;
    for (int i = 1; i < 8; i++)
        stack1.Push(i);
    Stack<int> stack2(stack1), stack3(stack1), stack4(stack1);
    stack3.Pop();
    stack4.Push(5);
    cout << "stack 1 == stack 2 -> result: " << (stack1 == stack2) << endl;
    cout << "stack 1 == stack 3 -> result: " << (stack1 == stack3) << endl;
    cout << "stack 1 == stack 4 -> result: " << (stack1 == stack4) << endl;

    return 0;
}
