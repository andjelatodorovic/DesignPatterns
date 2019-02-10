#ifndef __STATE_H
#define __STATE_H

/* apstraktno stanje / state
   poseduje metod Handle koji kontekst zove da bi
   razresio neki zahtev konteksta,
   moguce je preko metoda Handle da prosledimo i referencu
   na kontekst koji je zatrazio razresenje nekog zahteva
   i da na taj nacin konkretno stanje moze da izvrsi
   odgovarajuce modifikacije pristupajuci konktekstu */
class State {
public:
    State() {}
    virtual ~State() { }
    virtual void Handle() = 0;
};

#endif // __STATE_H
