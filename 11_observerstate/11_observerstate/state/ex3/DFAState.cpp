#include <string>
#include <iostream>

using namespace std;
/* implementiracemo automat koji prihvata sekvence koje imaju paran broj jedinica i paran broj nula,
   sekvenca 01010011 je prihvacena (paran broj i 0 i 1)
   sekvenca 011 nije prihvacena (neparan broj 0) */

/* apstraktno stanje automata,
   poseduje metod Move kojim se izvrsava akcija na automatu,
   cita se trenutni karakter sa ulaza i na osnovu tog karaktera automat prelazi u naredno stanje
   metod Move vraca naredno stanje automata
   isAccepted je true ako je stanje finalno (automat prihvata rec), ili false ako automat ne prihvata rec
   stanja su uradjena sledeci singleton obrazac */
class DFAState {
public:
    DFAState() {}
    virtual ~DFAState() {}
    virtual DFAState* Move(char input) = 0;
    virtual bool IsAccepted() = 0;
};
/* konkretno stanje, predstavlja stanje kad imamo i paran broj 0 i 1, to je ujedno i stanje prihvatanja sekvence */
class DFAState_0: public DFAState {
public:
    static DFAState* Instance() { static DFAState_0 state; return &state; }
    virtual bool IsAccepted() { return true; }
    virtual DFAState* Move(char input);
};
/* konkretno stanje, predstavlja stanje kad imamo neparan broj 0 i paran broj 1, nije stanje prihvatanja sekvence  */
class DFAState_1: public DFAState {
public:
    static DFAState* Instance() { static DFAState_1 state; return &state; }
    virtual bool IsAccepted() { return false; }
    virtual DFAState* Move(char input);
};
/* konkretno stanje, predstavlja stanje kad imamo paran broj 0 i neparan broj 1, nije stanje prihvatanja sekvence  */
class DFAState_2: public DFAState {
public:
    static DFAState* Instance() { static DFAState_2 state; return &state; }
    virtual bool IsAccepted() { return false; }
    virtual DFAState* Move(char input);
};
/* konkretno stanje, predstavlja stanje kad imamo neparan broj i 0 i 1, nije stanje prihvatanja sekvence  */
class DFAState_3: public DFAState {
public:
    static DFAState* Instance() { static DFAState_3 state; return &state; }
    virtual bool IsAccepted() { return false; }
    virtual DFAState* Move(char input);
};
/* konkretno stanje, predstavlja stanje kada na ulazu imamo neocekivani karakter, tj. razlicit od 0 ili 1 */
class DFAState_Fail: public DFAState {
public:
    static DFAState* Instance() { static DFAState_Fail state; return &state; }
    virtual bool IsAccepted() { return false; }
    virtual DFAState* Move(char input) { return DFAState_Fail::Instance(); }
};

/* funkcije Handle, predstavljaju i funkcije prelaska iz jednog stanja automata u drugi */
DFAState* DFAState_0::Move(char input) {
    if (input == '0') return DFAState_1::Instance();
    else if (input == '1') return DFAState_2::Instance();
    return DFAState_Fail::Instance();
}
DFAState* DFAState_1::Move(char input) {
    if (input == '0') return DFAState_0::Instance();
    else if (input == '1') return DFAState_3::Instance();
    return DFAState_Fail::Instance();
}
DFAState* DFAState_2::Move(char input) {
    if (input == '0') return DFAState_3::Instance();
    else if (input == '1') return DFAState_0::Instance();
    return DFAState_Fail::Instance();
}
DFAState* DFAState_3::Move(char input) {
    if (input == '0') return DFAState_2::Instance();
    else if (input == '1') return DFAState_1::Instance();
    return DFAState_Fail::Instance();
}
/* kontekst, u nasem slucaju automat,
   ima metod Accept koji igra ulogu metoda Request sa seme obrasca,
   jednostavno se prodje ceo string sequence sa ulaza, pocevsi od stanja DFAState_0 i zatim se
   iscitava sequence karakter po karakter i poziva metod Move na instanci konkretnog stanja
   na kraju vratimo rezultat da li je to konacno stanje prihvatljivo ili ne */
class DFA_01 {
public:
    static bool Accept(const string& sequence) {
        DFAState* state = DFAState_0::Instance();
        for (int i = 0; i < sequence.size(); i ++) {
            char input = sequence[i];
            state = state->Move(input);
        }
        return state->IsAccepted();
    }
};

/* pozovemo da automat ispita da li su razne ulazne sekvence prihvacene od automata ili ne */
int main() {
    cout << "11010001 -> " << DFA_01::Accept("11010001") << endl;
    cout << "110010 -> " << DFA_01::Accept("110010") << endl;
    cout << "01001101001 -> " << DFA_01::Accept("01001101001") << endl;
    cout << "000001101001 -> " << DFA_01::Accept("000001101001") << endl;
    cout << "0011 -> " << DFA_01::Accept("0011") << endl;
    cout << "00a11 -> " << DFA_01::Accept("00a11") << endl;

    return 0;
}
