#include <vector>

#include "TerminalExpression.h"
#include "NonterminalExpression.h"

using namespace std;

/* kreiramo niz konkretnih izraza, niz neterminalnih i terminalnih izraza i nakon
   toga pozovemo metod Interpret da interpretira svaki od izraza koristeci globalni kontekst */
int main() {
    Context* context = new Context();
    vector<AbstractExpression*> expressions;

    expressions.push_back(new NonterminalExpression());
    expressions.push_back(new TerminalExpression());
    expressions.push_back(new TerminalExpression());
    expressions.push_back(new NonterminalExpression());
    expressions.push_back(new TerminalExpression());

    for (vector<AbstractExpression*>::iterator it = expressions.begin(); it != expressions.end(); ++it) {
        (*it)->Interpret(context);
    }

    for (vector<AbstractExpression*>::iterator it = expressions.begin(); it != expressions.end(); ++it) {
        delete *it;
    }


    return 0;
}
