#include "Context.h"
#include "ConcreteStrategyA.h"
#include "ConcreteStrategyB.h"
#include "ConcreteStrategyC.h"

/* kreiramo kontekst sa odredjenom konkretnom strategijom A
   zatim uputimo zahtev da nam razresi neki problem,
   zatim promenimo strategiju i opet uputimo zahtev
   tok izvrsavanja mozemo pratiti na ekranu */
int main() {
    Context context(new ConcreteStrategyA());
    context.ContextInterface();

    context.SetStrategy(new ConcreteStrategyB());
    context.ContextInterface();

    context.SetStrategy(new ConcreteStrategyC());
    context.ContextInterface();

    return 0;
}
