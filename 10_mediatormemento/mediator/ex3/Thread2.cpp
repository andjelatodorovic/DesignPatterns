/* NAPOMENA: ovaj kod moguce je kompajlirati pod Windowsom koristeci Microsoft-ov C++ kompajler */
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <random>

using namespace std;

mutex mutexMediator;
mutex mutexCout;
condition_variable condVar;

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution(0, 100);

/* u ovom slucaju posrednika/mediatora koristimo da komunicira izmedju dve grupe paralelnih procesa,
   jedna grupa su producers/proizvodjaci koji kreiraju neke podatke, u ovom slucaju slucajne brojeve
   koje zele da proslede drugoj grupi proces consumers/potrosaci
   za komunikaciju izmedju proizvodjaca i potrosaca koristimo posrednika/mediatora
   proizvodjaci koriste metod SendMessage da posalju poruku
   a potrosaci ReceiveMessage da uzmu neku od poruka koju treba da obrade
   mediator interno ima red/queue u koji se po principu FIFO prosledjuj poruke
   SendMessage i ReceiveMessage ne smeju biti korisceni u isto vreme od vise od jednog procesa
   kako bi se osiguralo korektno funkcionisanje mehanizma
   za to koristimo mutex */
template<typename T>
class Mediator {
public:
    /* deo koda u kojem se vrsi manipulacija nad redom/queue (dodavanje elementa, izbacivanje)
       mora da bude medjusobno iskljucivo /mutual exclusive, tj. da u jednom trenutku najvise
       jedan procesor moze da izvrsava taj deo koda
       kako bismo osigurali iskljucivost koriscenja tog dela koda koristimo mutex koji zakljucamo
       pre nego sto udjemo u kritican deo koda a kada zavrsimo sa tim delom koda otkljucamo ga
       kako bi drugi procesi koji cekaju na mutex mogli da nastave svoje izvrsavanje */
    void SendMessage(const T& message) {
        while (true) {
            unique_lock<mutex> lock(mutexMediator);
            condVar.wait(lock, [this]() {
                return NotFull();
            });
            m_messages.push(message);
            lock.unlock();
            condVar.notify_all();
            break;
        }
    }
    T ReceiveMessage() {
        while (true) {
            unique_lock<mutex> lock(mutexMediator);
            condVar.wait(lock, [this]() {
                return NotEmpty();
            });
            T message = m_messages.front();
            m_messages.pop();
            lock.unlock();
            condVar.notify_all();
            return message;
        }
    }
    bool NotFull() {
        return m_messages.size() < MESSAGE_CAPACITY;
    }
    bool NotEmpty() {
        return m_messages.size() > 0;
    }
    Mediator() {}
private:
    static const unsigned int MESSAGE_CAPACITY = 8;
    queue<T>  m_messages;
};
/* proizvodjac, izvrsava petlju u kojoj kreira slucajan broj i prosledjuje ga posredniku/mediatoru */
template<typename T>
class Producer {
public:
    Producer(Mediator<T>* mediator, const string& name) {
        m_mediator = mediator;
        m_name = name;
    }
    void run() {
        while (true) {
            T message = distribution(generator);
            m_mediator->SendMessage(message);
            mutexCout.lock();
            cout << "[" << m_name << "] produced: " << message << endl;
            mutexCout.unlock();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
private:
    Mediator<T>*    m_mediator;
    string          m_name;
};
/* potrosac, izvrsava petlju u kojoj pokusava da uzme novu poruku/broj od posrednika */
template<typename T>
class Consumer {
public:
    Consumer(Mediator<T>* mediator, const string& name) {
        m_mediator = mediator;
        m_name = name;
    }
    void run() {
        while (true) {
            T message = m_mediator->ReceiveMessage();
            mutexCout.lock();
            cout << "[" << m_name << "] consumed: " << message << endl;
            mutexCout.unlock();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }
private:
    Mediator<T>*    m_mediator;
    string          m_name;
};
/* kreiramo posrednika/mediatora kojeg cemo da koristimo za komunikaciju
   kreiramo po dve niti/procesa/thread-a za proizvodjaca i potrosaca i startujemo ih kojima dodelimo i posrednika
   i startujemo ih da se paralelno izvrsavaju */
int main() {
    srand(time(NULL));
    Mediator<int> mediator;
    Producer<int> p1(&mediator, "Producer 1");
    Producer<int> p2(&mediator, "Producer 2");
    Consumer<int> c1(&mediator, "Consumer 1");
    Consumer<int> c2(&mediator, "Consumer 2");

    thread producer_thread1(&Producer<int>::run, &p1);
    thread producer_thread2(&Producer<int>::run, &p2);
    thread consumer_thread1(&Consumer<int>::run, &c1);
    thread consumer_thread2(&Consumer<int>::run, &c2);

    producer_thread1.join();
    producer_thread2.join();
    consumer_thread1.join();
    consumer_thread2.join();

    return 0;
}
