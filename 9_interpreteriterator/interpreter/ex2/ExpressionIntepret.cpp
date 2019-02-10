#include <map>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Expression;

/* kontekst, koji cuva mapiranje ime promenljive -> izraz koji se cuva u toj promenljivoj,
   poseduje i metod Evaluate da nam vrati izraz koji se cuva u promenljivoj sa datim imenom,
   kao i metod Put da se cuva pod imenom promenljive novi izraz */
class Context {
public:
    Context() {}
    virtual ~Context() { m_map.clear(); }
    virtual void Put(const string& name, Expression* expression);
    virtual Expression* Evaluate(string name);
private:
    map<string, Expression*>    m_map;
};
/* apstraktan izraz, sa metodom Interpret za interpretiranje */
class Expression {
public:
    virtual ~Expression() {}
    virtual int Interpret(Context& context) = 0;
};

void Context::Put(const string& name, Expression* expression) {
    if (m_map.find(name) != m_map.end()) delete m_map[name];
    m_map[name] = expression;
}
Expression* Context::Evaluate(string name) {
    if (m_map.find(name) == m_map.end()) return NULL;
    return m_map[name];
}
/* konkretan izraz koji predstavlja i terminalan izraz / izraz koji se vise ne izvodi,
   u ovom slucaju to je jednostavno izraz koji predstavlja brojevne konstante,
   putem konstruktora dodeljujemo konkretnu brojnu vrednost koju ovaj izraz predstavlja
   prilikom interpretacije jednostavno vratimo tu vrednost postavljenu prilikom kontruktcije izraza
   ovde moze da se koristi i muva obrazac za konstantne izraze
   u gramatici bi ovaj izraz obuhvatao izvodjenje
   E->broj */
class NumberExpression: public Expression {
public:
    NumberExpression(int number): m_number(number) {}
    virtual ~NumberExpression() {}
    virtual int Interpret(Context& context) {
        cout << "NumberExpression.Interpret()" << endl;
        return m_number;
    }
private:
    int     m_number;
};
/* neterminalan izraz koji predstavlja operaciju plus,
   u gramatici bi bio dat izvodjenjem
   E->E E +
   gde prvo imamo dva izraza a nakon toga operaciju koja se izvodi nad njima,
   u ovom slucaju +
   prilikom interpretacije prvo interpretiramo prvi izraz, zatim drugi a onda kao rezultat
   vratimo njihov zbir */
class PlusExpression: public Expression {
public:
    PlusExpression(Expression* leftExpression, Expression* rightExpression)
        : m_leftExpression(leftExpression), m_rightExpression(rightExpression) {}
    virtual ~PlusExpression() {
        if (m_leftExpression != NULL) delete m_leftExpression;
        if (m_rightExpression != NULL) delete m_rightExpression;
    }
    virtual int Interpret(Context& context) {
        cout << "PlusExpression.Interpret()" << endl;
        int result = 0;
        if (m_leftExpression != NULL) result = m_leftExpression->Interpret(context);
        if (m_rightExpression != NULL) result += m_rightExpression->Interpret(context);
        return result;
    }
private:
    Expression* m_leftExpression;
    Expression* m_rightExpression;
};
/* neterminalan izraz koji predstavlja operaciju minus,
   u gramatici bi bio dat izvodjenjem
   E->E E -
   gde prvo imamo dva izraza a nakon toga operaciju koja se izvodi nad njima,
   u ovom slucaju -
   prilikom interpretacije prvo interpretiramo prvi izraz, zatim drugi a onda kao rezultat
   vratimo njihovu razliku */
class MinusExpression: public Expression {
public:
    MinusExpression(Expression* leftExpression, Expression* rightExpression)
        : m_leftExpression(leftExpression), m_rightExpression(rightExpression) {}
    virtual ~MinusExpression() {
        if (m_leftExpression != NULL) delete m_leftExpression;
        if (m_rightExpression != NULL) delete m_rightExpression;
    }
    virtual int Interpret(Context& context) {
        cout << "MinusExpression.Interpret()" << endl;
        int result = 0;
        if (m_leftExpression != NULL) result = m_leftExpression->Interpret(context);
        if (m_rightExpression != NULL) result -= m_rightExpression->Interpret(context);
        return result;
    }
private:
    Expression* m_leftExpression;
    Expression* m_rightExpression;
};
/* neterminalan izraz koji predstavlja operaciju promenljivu,
   u gramatici bi bio dat izvodjenjem
   E->imePromenljive
   gde je imePromenljive definisano nekim regulanrim izrazom (npr. [a-zA-Z]+, izraz koji se
   sastoji od 1 i vise malih i velikih slova - neki vid pravila za nazive promenljivih)
   prilikom interpretacije koristimo kontekst kako bismo uzeli vrednost koju ta promenljiva ima
   posto to moze opet ta bude neki izraz, pozovemo metod Interpret nad tim izrazom koji se cuva u promenljivoj
   i vrednost interpretacije tog izraza vratimo kao rezultat interpretacije promenljive */
class VariableExpression: public Expression {
public:
    VariableExpression(const string& variableName): m_variableName(variableName) {}
    virtual int Interpret(Context& context) {
        cout << "VariableExpression.Interpret() " << endl;
        return context.Evaluate(m_variableName)->Interpret(context);
    }
private:
    string  m_variableName;
};
/* mozemo da kreiramo i drugacije konkretne izraze npr. za predstavljanje kvadrata izraza
   u gramatici bi bio dat sa izvodjenjem npr.
   E->E sq
   nije trenutno koriscen u programu */
class SquareFunctionExpression: public Expression {
public:
    SquareFunctionExpression(Expression* expression): m_expression(expression) {}
    virtual ~SquareFunctionExpression() { if (m_expression != NULL) delete m_expression; }
    virtual int Interpret(Context& context) {
        if (m_expression == NULL) return 0;
        int result = m_expression->Interpret(context);
        return result * result;
    }
private:
    Expression* m_expression;
};
/* parser, u nasem slucaju klijent ce da se bavi zadatkom parsiranja: tj. transformacijom
   izraza iz nekog jezika u stablo izvodjenja u gramatici
   parsiranje moze da bude relativno jednostavno za jednostavne gramatike koje mozemo da kreiramo
   ad hok, ali u slucaju komplikovanijih gramatika parsiranje moze da bude veoma komplikovan i zahtevan
   posao
   u nasem slucaju parsiraju se "post-fix" izrazi, gde imamo dva izraza a nakon toga operaciju
   sto nije toliko zahtevan posao, dovoljno je da imamo stek i onda kad naidjemo na neku operaciju +-
   skinemo dva poslednja izraza sa vrha steka kreiramo novi izraz PlusExpression ili MinusExpression
   napravljen od ta dva izraza i taj novokreirani dodamo na vrh steka */
class ExpressionParser {
public:
    static Expression* Parse(const string& content) {
        vector<Expression*> expressions;
        istringstream in(content);
        string token;
        while (!in.eof()) {
            in >> token;
            if (token == "+") {
                if (expressions.size() < 2) {
                    Retract(expressions);
                    throw("Error while parsing plus expression.");
                }
                Expression* right = expressions.back(); expressions.pop_back();
                Expression* left = expressions.back(); expressions.pop_back();
                expressions.push_back(new PlusExpression(left, right));
            } else if (token == "-") {
                if (expressions.size() < 2) {
                    Retract(expressions);
                    throw("Error while parsing minus expression.");
                }
                Expression* right = expressions.back(); expressions.pop_back();
                Expression* left = expressions.back(); expressions.pop_back();
                expressions.push_back(new MinusExpression(left, right));
            } else {
                expressions.push_back(new VariableExpression(token));
            }
        }
        if (expressions.size() != 1) {
            Retract(expressions);
            throw("Error parsing expression. Can't reduce to one element.");
        }
        Expression* result = expressions.back();
        return result;
    }
private:
    static void Retract(vector<Expression*> &expressions) {
        for (vector<Expression*>::iterator it = expressions.begin(); it != expressions.end(); ++it) {
            delete *it;
        }
    }
};
/* kreiramo neki izraz koji je ispravan u nasoj gramatici sa pravilima izvodjenja
   E->E E +
   E->E E -
   E->ime_promenjljive
   postavimo neke pocetne vrednosti promenljivih u kontekst i nakon toga pozovemo
   ExpressionParse::Parse da nam parsira izraz i nakon toga interpretiramo izraz
   u nasem slucaju p = 10, q = 5, a = (p+q)-(b+q), b = 2, c = 3,
   znaci a = 8, a izraz koji interpretiramo je ((a+b)-c)+b = 9*/
int main() {
    string expression = "a b + c - b +";
    Context* context = new Context();
    try {
        context->Put("p", new NumberExpression(10));
        context->Put("q", new NumberExpression(5));
        context->Put("a", ExpressionParser::Parse("p q + b q + -"));
        context->Put("b", new NumberExpression(2));
        context->Put("c", new NumberExpression(3));

        Expression* tree = ExpressionParser::Parse(expression);
        int result = tree->Interpret(*context);
        cout << result << endl;

        delete tree;
    } catch (const char* e) { cout << "ERROR: " << e << endl; }
    delete context;


    return 0;
}
