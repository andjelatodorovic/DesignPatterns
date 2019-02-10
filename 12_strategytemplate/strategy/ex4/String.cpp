#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/* ovde navodimo primer koriscenja obrasca usadjenog vec u klasu basic_string iz standardne
   biblioteke stl
   klasa string je samo tip basic_string<char, char_traits<char> >
   klasa char_traits je u stvari strategija nacina na koji cemo da tretiramo karaktere/char ili neki
   drugi tip sadrzan u basic_string
   metodi koji treba da se implementiraju su lt (jedan strogo manji od drugog, less then),
   ne (kada su razliciti, not equal), eq (kada su jednaki, equal), compare za uporedjivanje dva
   niza karaktera i find za nalazenje jednog karaktera u stringu

   mi zelimo da implementiramo konkretnu strategiju koja nece da razlikuje mala i velika slova
   u stringu, tj. da aAbB bude jednako AaBb */
class mychar_traits : public char_traits<char> {
public:
    static bool lt(char c1, char c2) { return toupper(c1) <  toupper(c2); }
    static bool ne(char c1, char c2) { return toupper(c1) != toupper(c2); }
    static bool eq(char c1, char c2) { return toupper(c1) == toupper(c2); }
    static int compare(const char* s1, const char* s2, size_t n) {
        while (n != 0 ) {
            if (toupper(*s1) < toupper(*s2)) return -1;
            if (toupper(*s1) > toupper(*s2)) return 1;
            ++s1;
            ++s2;
            --n;
        }
        return 0;
    }
    static const char* find(const char* s, int n, char a) {
        while (n > 0 && toupper(*s) != toupper(a)) {
            ++s;
            --n;
        }
        return s;
    }
};
/* sada je nas novi tip stringova koji nisu case sensitive (ne vode racuna o velicini slova)
   basic_string<char, mychar_traits> sa nasom novom konkretnom strategijom */
typedef basic_string<char, mychar_traits> string_caseins;
/* kreiramo dva stringa naseg novog tipa dodelimo im vrednosti i uporedimo, pozovemo i metod find */
int main() {
    string_caseins s1, s2;
    basic_string<char, mychar_traits> s;
    s1 = "test";
    s2 = "TEST";
    cout << (s1 == s2) << endl;
    cout << s1.find("ST") << endl;

    return 0;
}
