#include <iostream>
#include <string>

using namespace std;

class Widget;
class IMediator;

/* uopstena komanda, koja specificira neku akciju koja moze da bude izvrsena,
   sledi Komanda obrazac */
class Command {
public:
    Command(Widget* target, void (*action)(Widget*)): m_target(target), m_action(action) {}
    virtual void Execute() { m_action(m_target); };
protected:
    void (*m_action)(Widget*);
    Widget* m_target;
};



class App {
};

/* kolege/ucesnici komunikacije,
   koriste medijatora da medjusobno saopstavaju promene koje su se desile na njima kako bi ostale komponente sistema
   mogle da se adaptiraju
   npr. aplikacija se sastoji od panela gde se prikazuje neki proizvod (automobil npr.) liste proizvoda koji mogu da se selektuju
   i dugmica kojima mozemo da radimo kupovinu/buy, pretragu proizvoda/find ili prikaz proizvoda/display
   ako kliknemo na kupovinu/buy dugme onda ostali dugmici treba da budu nedostupni, disabled
   ovu promenu stanja na komponentama aplikacije treba da komunicira posrednik, umesto da dugme kada bude kliknuto
   promeni stanja ostalih komponenti aplikacije
   Widget predstavlja opstu komponentu aplikacije, ima ime, dodeljenog posrednika i stanje (enabled/disabled - dostupna ili ne)
   i dodeljenu komandu koja se izvrsava prilikom odredjenog dogadjaja (metod Event startuje dogadjaj koji zatim poziva metod
   Execute na dodeljenoj komandi) pomocu SetEventHandler dodeljujemo komandu Widget-u */
class Widget {
public:
    Widget(const string& name, IMediator* const mediator = NULL): m_name(name), m_enabled(true), m_mediator(mediator) {}
    virtual void Enable() { m_enabled = true; cout << "Widget [" << m_name << "] enabled." << endl; }
    virtual void Disable() { m_enabled = false; cout << "Widget [" << m_name << "] disabled." << endl; }
    virtual void Show() { cout << "Showing widget [" << m_name << "]" << endl; }
    virtual void SetEventHandler(Command* command) { m_command = command; }
    virtual void Event(const string& event ) {
        m_command->Execute();
    }
    virtual void SetMediator(IMediator* mediator) { m_mediator = mediator; }
    virtual IMediator* GetMediator() { return m_mediator; }
    virtual string GetName() { return m_name; }
protected:
    bool        m_enabled;
    string      m_name;
    IMediator*  m_mediator;
    Command*    m_command;
};
/* konkretne kolege/komponente aplikacije */
class Button: public Widget {
public:
    Button(const string& name, IMediator* mediator = NULL): Widget(name, mediator) {}
};
/* konkretne kolege/komponente aplikacije */
class Display: public Widget {
public:
    Display(const string& name, IMediator* mediator = NULL): Widget(name, mediator) {}
    void Show(const string& txt) { cout << "Display [" << m_name << "] showing " << txt << endl; }
};
/* konkretne kolege/komponente aplikacije */
class List: public Widget {
public:
    List(const string& name, IMediator* mediator = NULL): Widget(name, mediator) {}
};
/* posrednik, ima metode za postavljanje ucesnika komunikacije/kolega, tj. komponenti aplikacije
   (SetDisplay, SetBtnDisplay, SetBtnFind...)
   i metode koji simboliziraju odredjene akcije u aplikaciji, Buy, Show, Find
   koje mogu da izmene stanja razlicitih delova aplikacije
   zadatak posrednika je da izvrsi ovu sinhronizaciju delova aplikacije na korektan nacin
   a ne da taj zadatak bude dodeljen samim komponentama koje bi time dovele do zagusenja komunikacije
   u samoj aplikaciji */
class IMediator {
public:
    IMediator() {}
    virtual ~IMediator() {}
    virtual void SetDisplay(Display* display) = 0;
    virtual void SetBtnDisplay(Button* btnDisplay) = 0;
    virtual void SetBtnFind(Button* btnFind) = 0;
    virtual void SetBtnBuy(Button* btnBuy) = 0;
    virtual void SetList(List* list) = 0;
    virtual void Buy() = 0;
    virtual void Show() = 0;
    virtual void Find() = 0;
protected:
    Display*    m_display;
    Button*     m_btnDisplay;
    Button*     m_btnFind;
    Button*     m_btnBuy;
    List*       m_list;
};
/* konkretan posrednik, implementira cisto virtuelne nasledjene metode */
class CMediator: public IMediator {
public:
    virtual void SetDisplay(Display* display) { m_display = display; m_display->SetMediator(this); }
    virtual void SetBtnDisplay(Button* btnDisplay) { m_btnDisplay = btnDisplay; m_btnDisplay->SetMediator(this); }
    virtual void SetBtnFind(Button* btnFind) { m_btnFind = btnFind; m_btnFind->SetMediator(this); }
    virtual void SetBtnBuy(Button* btnBuy) { m_btnBuy = btnBuy; m_btnBuy->SetMediator(this); }
    virtual void SetList(List* list) { m_list = list; m_list->SetMediator(this); }
    /* npr. metod Buy simbolizira operaciju kupovine
       kada se izvrsi operacija kupovine, pozove metod Buy, onda se menja simultano stanje raznih delova aplikacije
       ne treba da bude zadatak onog ko je pozvao metod da menja stanja ostalih delova aplikacije, vec se ovako
       ima na jednom mestu, u posredniku/mediatoru, kod/deo programa koji ce da vodi racuna o izmenama na razlicitim
       delovima aplikacije,
       pa tako ovde ce na displayu da se pokaze odgovarajuca poruka, dugme za kupovinu ce biti neomoguceno/disabled,
       dugme find i lista ce biti omoguceni za koriscenje /enabled */
    virtual void Buy() {
        cout << "buy()" << endl;
        m_display->Show("Buying car...");
        m_btnBuy->Disable();
        m_btnFind->Enable();
        m_list->Enable();
    }

    virtual void Show() {
        cout << "show()" << endl;
        m_display->Show("Showing car...");
        m_btnDisplay->Disable();
        m_btnFind->Enable();
        m_list->Enable();
    }

    virtual void Find() {
        cout << "find()" << endl;
        m_display->Show("Searching car...");
        m_btnFind->Disable();
        m_list->Enable();
        m_btnDisplay->Enable();

    }
};
/* akcije koje cemo da dodelimo komandama */
void viewClick(Widget* widget) {
    cout << "widget [" << widget->GetName() << "] clicked" << endl;
    widget->GetMediator()->Show();
}

void searchClick(Widget* widget) {
    cout << "widget [" << widget->GetName() << "] clicked" << endl;
    widget->GetMediator()->Find();
}

void buyClick(Widget* widget) {
    cout << "widget [" << widget->GetName() << "] clicked" << endl;
    widget->GetMediator()->Buy();
}
/* aplikacija, sastoji se od nekoliko komponenti,
   dugme za prikaz btnView, dugme za pretragu btnSearch, displey display, listu list
   zadatak promene stanja razlicitih delova aplikacija prilikom izvrsavanja odredjenih akcija
   ostavili smo posredniku/medijatoru koji je zaduzen za medjusobnu komunikaciju */
class CarApp: public App {
public:
    CarApp() {
        m_mediator = new CMediator();
        m_btnView = new Button("Show car");
        m_mediator->SetBtnDisplay(m_btnView);
        m_btnSearch = new Button("Search car");
        m_mediator->SetBtnFind(m_btnSearch);
        m_btnBuy = new Button("Buy car");
        m_mediator->SetBtnBuy(m_btnBuy);
        m_display = new Display("Car display");
        m_mediator->SetDisplay(m_display);
        m_list = new List("Car list");
        m_mediator->SetList(m_list);

        m_btnView->SetEventHandler(new Command(m_btnView, viewClick));
        m_btnSearch->SetEventHandler(new Command(m_btnSearch, searchClick));
        m_btnBuy->SetEventHandler(new Command(m_btnBuy, buyClick));

    }
    ~CarApp() {
        delete m_mediator;
        delete m_btnView;
        delete m_btnSearch;
        delete m_btnBuy;
        delete m_display;
        delete m_list;
    }
    /* napravimo simulaciju tako sto kliknemo na svako od dugmica, i na ekranu cemo da imamo tok izvrsavanja */
    void run() {
        m_btnView->Event("click");
        m_btnSearch->Event("click");
        m_btnBuy->Event("click");
    }
protected:
    IMediator*  m_mediator;
    Button*     m_btnView;
    Button*     m_btnSearch;
    Button*     m_btnBuy;
    Display*    m_display;
    List*       m_list;
};
/* kreiramo aplikaciju i startujemo je */
int main() {
    CarApp app;
    app.run();

    return 0;
}
