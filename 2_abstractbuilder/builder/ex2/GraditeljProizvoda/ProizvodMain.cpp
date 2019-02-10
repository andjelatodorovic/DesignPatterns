#include "Proizvod.h"
#include "Graditelj.h"

/* koriscenje graditelja */
int main(){
    /* kombinovano koriscenje za postavljanje svojstava */
	Proizvod proizvod1 = Graditelj().postaviIntSvojstvo(2)
                             .postaviFloatSvojstvo(0.5f)
                             .postaviCharSvojstvo('x')
                             .napraviProizvod();
	proizvod1.prikazi();

    /* drugi vid koriscenja, napravimo jedan proizvod, posle napravimo izmene putem graditelja i vratimo
       drugi, izmenjeni proizvod */
	Graditelj graditelj;
	graditelj.postaviProizvod();
	Proizvod proizvod2 = graditelj.napraviProizvod();
	graditelj.postaviCharSvojstvo('*');
	Proizvod proizvod3 = graditelj.napraviProizvod();
	proizvod2.prikazi();
	proizvod3.prikazi();
}
