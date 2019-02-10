#include <iostream>

using namespace std;

/* receiver / primaoc akcije, nudi metode za izmenu internog stanja,
   kao sto su RemoveChar da ukloni poslednji znak iz sadrzaja dokumenta,
   kao i InsertChar da doda znak na kraj dokumenta,
   InsertChar i RemoveChar su Action() */
class CDocument {
public:
    CDocument(): m_content("") {}
    virtual ~CDocument() {}
    virtual void InsertChar(char ch) {
        m_content += string(1, ch);
    }
    virtual void RemoveChar() {
        if (m_content.size() > 0) {
            m_content.erase(m_content.size() - 1);
        }
    }
    friend ostream& operator<<(ostream& out, const CDocument& doc) {
        out << doc.m_content;
        return out;
    }
protected:
    string  m_content;
};
/* interfejs Komande, nudi metode za izvrsenje akcije Execute i postavljanje
   primaoca akcije/Receiver-a putem metoda SetDocument */
class ICommand {
public:
    ICommand() {}
    virtual ~ICommand() {}
    virtual void Execute() = 0;
    virtual void SetDocument(CDocument* document) = 0;
};
/* konkretna komanda, implementira metod Execute tako sto zahteva od korisnika
   da unese neki karakter i onda taj karakter dodaje u dokument pozivajuci metod InsertChar */
class CInsertCommand: public ICommand {
public:
    CInsertCommand(CDocument *document = NULL): m_document(document) {}
    virtual ~CInsertCommand() {}
    virtual void Execute() {
        if (m_document != NULL) {
            char ch;
            cout << "Enter char to insert: ";
            cin >> ch;
            m_document->InsertChar(ch);
        }
    }
    virtual void SetDocument(CDocument* document) {
        m_document = document;
    }
protected:
    CDocument*   m_document;
};
/* konkretna komanda / implementira Execute tako sto uklanja poslednji znak iz dokumenta */
class CRemoveCommand: public ICommand {
public:
    CRemoveCommand(CDocument* document = NULL): m_document(document) {}
    virtual ~CRemoveCommand() {}
    virtual void Execute() {
        if (m_document != NULL) {
            m_document->RemoveChar();
        }
    }
    virtual void SetDocument(CDocument* document) {
        m_document = document;
    }
protected:
    CDocument*   m_document;
};
/* pokretac akcije / invoker
   implementira metod Click (koji je Invoke iz naseg obrasca) koji poziva metod
   Execute na dodeljenoj komandi, vidimo da ne postoji referenca na dokument/receiver
   unutar pokretaca/invoker-a vec je taj kontakt ostvaren preko komande koja ima referencu
   na primaoca akcije */
class Button {
public:
    Button(): m_command(NULL) {}
    virtual void SetOnClickCommand(ICommand* command) {
        m_command = command;
    }
    virtual void Click() {
        if (m_command != NULL) {
            m_command->Execute();
        }
    }
protected:
    ICommand*    m_command;
};
/* kreiramo primaoca akcije/receiver to je dokument, kreiramo
   dve komande insert i remove, napravimo dva pokretaca akcije/invokera
   dugmice insertButton i removeButton i dodelimo im konkretne komande,
   nakon toga radimo malu interakciju sa klijentom da bira koje dugme ce da
   klikne
   nakon svakog klika dugmeta prikazemo trenutni sadrzaj dokumenta */
int main() {
    CDocument* doc = new CDocument();
    ICommand* insertCommand = new CInsertCommand(doc);
    //insertCommand->SetDocument(doc);
    ICommand* removeCommand = new CRemoveCommand();
    removeCommand->SetDocument(doc);

    Button* insertButton = new Button();
    insertButton->SetOnClickCommand(insertCommand);

    Button* removeButton = new Button();
    removeButton->SetOnClickCommand(removeCommand);

    int choice;
    do {
       cout << "Choose the button: 1-insert char button   2-remove last char button   0-exit: ";
       cin >> choice;
       if (choice == 1) insertButton->Click();
       if (choice == 2) removeButton->Click();
       cout << *doc << endl;
    } while (choice != 0);

    delete removeButton;
    delete insertButton;
    delete removeCommand;
    delete insertCommand;
    delete doc;

    return 0;
}
