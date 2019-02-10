#include <iostream>
#include <string>
#include <cstring>

using namespace std;
/* kontekst za interpretiranje izraza koji predstavlja broj zapisan rimskim ciframa,
   u nasem slucaju sadrzi samo broj zapisan rimskim ciframa, kao i pokazivac (indeks karaktera)
   na podstring koji jos treba da interpretiramo */
class Context {
public:
    Context(const string& content): m_content(content), m_value(0), m_index(0) {}
    void Restart() { m_value = 0; m_index = 0; }
    void SetContent(const string& content) {
        m_content = content;
        m_value = 0;
        m_index = 0;
    }
    void SetValue(int value) { m_value = value; }
    int GetValue() { return m_value; }
    bool StartsWith(const string& prefix, int index = -1) {
        if (index == -1) index = m_index;
        return m_content.find(prefix, index) == index;
    }
    void Shift(const string& prefix) {
        m_index += prefix.size();
    }
    string GetContent() { return m_content.substr(m_index); }
    bool IsEmpty() { return m_index == m_content.size(); }
private:
    string  m_content;
    int     m_value;
    int     m_index;
};
/* intepretator izraza za rimske brojeve, glavni javni kontruktor kreira interno
   konkretne interpretatore za terminalne izraze - za rimske cifre jedinice, desetice, stotine i hiljadarke
   a prilikom interpetiranja pozove prvo interpretator za hiljadarke, pa za stotine onda za desetice i na kraju za jedinice
   ako smo stigli do kraja stringa onda je broj ispravno zapisan u formatu za rimske brojeve, u suprotnom ako je ostao deo
   neinterpretiran onda je pogresan format broja,
   zasticeni konstruktor je za konkretne interpretere za osnovne izraze, svaki od njih ima prosledjen izraz koji
   predstavlja neku od karakteristicnih vrednost, npr. za jedinice to su I-1, II-2, III-3, IV-4, V-5, IX-9 a osnovna vrednost
   koju taj interpreter predstavlja je 1
   gramatika za rimske brojeve u ovom slucaju nije data formalno vec je neophodno poznavati pravila za interpretiranje
   rimskih brojeva kako bi se razumelo kako radi interpreter */
class RomanNumbersInterpreter {
public:
    RomanNumbersInterpreter() {
        m_onesInterpreter = new RomanNumbersInterpreter("I", "II", "III", "IV", "V", "IX", 1);
        m_tensInterpreter = new RomanNumbersInterpreter("X", "XX", "XXX", "XL", "L", "XC", 10);
        m_hundredsInterpreter = new RomanNumbersInterpreter("C", "CC", "CCC", "CD", "D", "CM", 100);
        m_thousandsInterpreter = new RomanNumbersInterpreter("M", "MM", "MMM", "", "", "", 1000);
    }
    virtual int Interpret(string content) {
        Context context(content);
        m_thousandsInterpreter->Interpret(context);
        m_hundredsInterpreter->Interpret(context);
        m_tensInterpreter->Interpret(context);
        m_onesInterpreter->Interpret(context);

        if (context.IsEmpty()) return context.GetValue();
        throw("Uneseni broj nije ispravan rimski broj.");
    }
protected:
    RomanNumbersInterpreter(const char* one, const char* two, const char* three, const char* four, const char* five, const char* nine, int baseValue):
         m_one(one), m_two(two), m_three(three), m_four(four), m_five(five), m_nine(nine), m_baseValue(baseValue),
         m_onesInterpreter(NULL), m_tensInterpreter(NULL), m_hundredsInterpreter(NULL), m_thousandsInterpreter(NULL) {}
    int     m_baseValue;
    string  m_one;
    string  m_two;
    string  m_three;
    string  m_four;
    string  m_five;
    string  m_nine;
    RomanNumbersInterpreter*    m_onesInterpreter;
    RomanNumbersInterpreter*    m_tensInterpreter;
    RomanNumbersInterpreter*    m_hundredsInterpreter;
    RomanNumbersInterpreter*    m_thousandsInterpreter;

    virtual void Interpret(Context& context) {
        if (m_nine != "" && context.StartsWith(m_nine)) {
            context.SetValue(context.GetValue() + 9 * m_baseValue);
            context.Shift(m_nine);
        } else if (m_four != "" && context.StartsWith(m_four)) {
            context.SetValue(context.GetValue() + 4 * m_baseValue);
            context.Shift(m_four);
        } else {
            if (m_five != "" && context.StartsWith(m_five)) {
                context.SetValue(context.GetValue() + 5 * m_baseValue);
                context.Shift(m_five);
            }
            if (m_three != "" && context.StartsWith(m_three)) {
                context.SetValue(context.GetValue() + 3 * m_baseValue);
                context.Shift(m_three);
            } else if (m_two != "" && context.StartsWith(m_two)) {
                context.SetValue(context.GetValue() + 2 * m_baseValue);
                context.Shift(m_two);
            } else if (m_one != "" && context.StartsWith(m_one)) {
                context.SetValue(context.GetValue() + 1 * m_baseValue);
                context.Shift(m_one);
            }
        }
    }
};
/* u ovom slucaju nema parsiranja, neki vid parsiranja se odvija unutar konkretnih interpretera
   ne generise se stablo izvodjenja */
int main() {
    RomanNumbersInterpreter intepreter;
    string romanNumber;
    while (true) {
        cout << "Unesi rimski broj (q-za kraj):";
        cin >> romanNumber;
        if (romanNumber == "q" || romanNumber == "Q") break;
        try {
            cout << intepreter.Interpret(romanNumber) << endl;
        } catch (const char* e) {
            cout << "GRESKA: " << e << endl;
        }
    }
    return 0;
}
