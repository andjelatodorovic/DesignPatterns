#ifndef __COMPONENT_H
#define __COMPONENT_H

/* apstraktna komponenta, napravicemo nekoliko izvedenih
   komponenti ali odredjena svojstva cemo da izdvojimo
   u zasebne klase - dekoratere/dopune koje mozemo
   po potrebi (i tokom izvrsavanja/runtime) da dodamo
   na nase konkretne komponente bez da pravimo instance
   neke druge potklase
   u ovom slucaju komponenta ima samo jednu operaciju
   koja moze da se ostvari na vise nacina
   svaki od tih nacina sa svojom nekom posebnom karakteristikom
   mozemo da imamo u nekoj od dopuna/dekoratera */
class Component {
public:
    virtual void operation() = 0;
    virtual ~Component() { }
};
#endif // __COMPONENT_H
