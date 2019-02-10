#include <map>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Expression;
/* slican primer kao i aritmeticki izrazi samo sto sad imamo logicke operacije AND, OR, NOT */

/* kontekst gde cuvamo vrednosti promenljivih */
class Context {
public:
    Context() {}
    virtual ~Context() { m_map.clear(); }
    virtual void Put(const string& name, Expression* expression);
    virtual Expression* Evaluate(string name);
private:
    map<string, Expression*>    m_map;
};
/* apstraktan izraz */
class Expression {
public:
    virtual ~Expression() {}
    virtual bool Interpret(Context& context) = 0;
};

void Context::Put(const string& name, Expression* expression) {
    if (m_map.find(name) != m_map.end()) delete m_map[name];
    m_map[name] = expression;
}
Expression* Context::Evaluate(string name) {
    if (m_map.find(name) == m_map.end()) return NULL;
    return m_map[name];
}
/* konstante true/false, terminalni izrazi za izvodjenja u gramatici
   E->true
   E->false */
class TruthExpression: public Expression {
public:
    TruthExpression(bool truth): m_truth(truth) {}
    virtual ~TruthExpression() {}
    virtual bool Interpret(Context& context) {
        cout << "TruthExpression.Interpret()" << endl;
        return m_truth;
    }
private:
    bool     m_truth;
};
/* neterminalni izrazi za operaciju or/ili, za izvodjenja u gramatici:
   E->E E OR */
class OrExpression: public Expression {
public:
    OrExpression(Expression* leftExpression, Expression* rightExpression)
        : m_leftExpression(leftExpression), m_rightExpression(rightExpression) {}
    virtual ~OrExpression() {
        if (m_leftExpression != NULL) delete m_leftExpression;
        if (m_rightExpression != NULL) delete m_rightExpression;
    }
    virtual bool Interpret(Context& context) {
        cout << "OrExpression.Interpret()" << endl;
        bool result = 0;
        if (m_leftExpression != NULL) result |= m_leftExpression->Interpret(context);
        if (m_rightExpression != NULL) result |= m_rightExpression->Interpret(context);
        return result;
    }
private:
    Expression* m_leftExpression;
    Expression* m_rightExpression;
};
/* neterminalni izrazi za operaciju and/i, za izvodjenja u gramatici:
   E->E E AND */
class AndExpression: public Expression {
public:
    AndExpression(Expression* leftExpression, Expression* rightExpression)
        : m_leftExpression(leftExpression), m_rightExpression(rightExpression) {}
    virtual ~AndExpression() {
        if (m_leftExpression != NULL) delete m_leftExpression;
        if (m_rightExpression != NULL) delete m_rightExpression;
    }
    virtual bool Interpret(Context& context) {
        cout << "AndExpression.Interpret()" << endl;
        bool result = 1;
        if (m_leftExpression != NULL) result &= m_leftExpression->Interpret(context);
        if (m_rightExpression != NULL) result &= m_rightExpression->Interpret(context);
        return result;
    }
private:
    Expression* m_leftExpression;
    Expression* m_rightExpression;
};
/* terminalan izraz za promenljive
   E->ime_promenljive */
class VariableExpression: public Expression {
public:
    VariableExpression(const string& variableName): m_variableName(variableName) {}
    virtual bool Interpret(Context& context) {
        cout << "VariableExpression.Interpret() " << endl;
        return context.Evaluate(m_variableName)->Interpret(context);
    }
private:
    string  m_variableName;
};
/* neterminalni izrazi za operaciju not/ne, za izvodjenja u gramatici:
   E->E NOT */
class NotExpression: public Expression {
public:
    NotExpression(Expression* expression): m_expression(expression) {}
    virtual ~NotExpression() { if (m_expression != NULL) delete m_expression; }
    virtual bool Interpret(Context& context) {
        cout << "NotExpression.Interpret() " << endl;
        if (m_expression == NULL) return false;
        bool result = m_expression->Interpret(context);
        return !result;
    }
private:
    Expression* m_expression;
};
/* parser koji rec transformise u drvo izvodjenja u datoj gramatici */
class ExpressionParser {
public:
    static Expression* Parse(const string& content) {
        vector<Expression*> expressions;
        istringstream in(content);
        string token;
        while (!in.eof()) {
            in >> token;
            if (token == "OR") {
                if (expressions.size() < 2) {
                    Retract(expressions);
                    throw("Error while parsing OR expression.");
                }
                Expression* right = expressions.back(); expressions.pop_back();
                Expression* left = expressions.back(); expressions.pop_back();
                expressions.push_back(new OrExpression(left, right));
            } else if (token == "AND") {
                if (expressions.size() < 2) {
                    Retract(expressions);
                    throw("Error while parsing AND expression.");
                }
                Expression* right = expressions.back(); expressions.pop_back();
                Expression* left = expressions.back(); expressions.pop_back();
                expressions.push_back(new AndExpression(left, right));
            } else if (token == "NOT") {
                if (expressions.size() < 1) {
                    Retract(expressions);
                    throw("Error while parsing NOT expression.");
                }
                Expression* right = expressions.back(); expressions.pop_back();
                expressions.push_back(new NotExpression(right));
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
/* kreiramo logicki izraz i interpretiramo ga, gramatika je data sa:
   E->E E AND
   E->E E OR
   E->E NOT
   E->ime promenljive
   u nasem slucaju:
   p = true, q = true, r = false, A = NOT ((p AND NOT q) OR r) = true,
   B = NOT((p OR NOT q) OR NOT A) = false,
   C = NOT ((p AND r) AND (q OR NOT A)) = true
   a izraz koji interpretiramo je (A AND NOT B) OR NOT C = true */
int main() {
    string expression = "A B NOT AND C NOT OR";
    Context* context = new Context();
    try {
        context->Put("p", new TruthExpression(true));
        context->Put("q", new TruthExpression(true));
        context->Put("r", new TruthExpression(false));
        context->Put("A", ExpressionParser::Parse("p q NOT AND r OR NOT"));
        context->Put("B", ExpressionParser::Parse("p NOT q OR A NOT OR NOT"));
        context->Put("C", ExpressionParser::Parse("p r AND q A NOT OR AND NOT"));
        Expression* tree = ExpressionParser::Parse(expression);
        bool result = tree->Interpret(*context);
        cout << result << endl;

        delete tree;
    } catch (const char* e) { cout << "ERROR: " << e << endl; }
    delete context;


    return 0;
}
