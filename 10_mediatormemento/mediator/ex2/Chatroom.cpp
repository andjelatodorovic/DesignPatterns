#include <ctime>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class IUser;

/* apstraktni medijator/posrednik
   simulirace neku chat sobu, soba ima ucesnike u razgovoru tipa IUser,
   interfejs nudi metode EnterRoom - kada korisnik udje u sobu, tada se i registruje ovom posredniku
   da ucestvuje u komunikaciji, ExitRoom - da se odregistruje od posrednika/mediatora,
   SendMessage(posiljalac, primalac, poruka) za slanje poruke od posiljaoca ka primaocu,
   BroadcastMessage da prosledi poruku svim ucesnicima u chat sobi */
class IChatroom {
public:
    IChatroom() {}
    virtual ~IChatroom() {}
    virtual void EnterRoom(IUser* user) = 0;
    virtual void ExitRoom(IUser* user) = 0;
    virtual void SendMessage(const string& sender, const string& receiver, const string& message) = 0;
    virtual void BroadcastMessage(const string& sender, const string& message) = 0;
};
/* apstraktni kolega/ucesnik u komunikaciji */
class IUser {
public:
    IUser(const string& username): m_username(username) {}
    virtual ~IUser() {}
    virtual void SetChatroom(IChatroom* chatroom) { m_chatroom = chatroom; }
    virtual void Send(const string& receiver, const string& message) = 0;
    virtual void Broadcast(const string& message) = 0;
    virtual void Receive(const string& sender, const string& message) = 0;
    virtual string GetUsername() { return m_username; }
protected:
    string      m_username;
    IChatroom*  m_chatroom;
};
/* konkretan kolega/ucesnik  ConcreteColleague */
class CNormalUser: public IUser {
public:
    CNormalUser(const string& username): IUser(username) {}
    virtual ~CNormalUser() {}
    virtual void Send(const string& receiver, const string& message) {
        if (m_chatroom == NULL) throw("Invalid chatroom");
        m_chatroom->SendMessage(m_username, receiver, message);
    }
    virtual void Broadcast(const string& message) {
        if (m_chatroom == NULL) throw("Invalid chatroom");
        m_chatroom->BroadcastMessage(m_username, message);
    }
    virtual void Receive(const string& sender, const string& message) {
        cout << m_username << " received message: [" << sender << "] " << message << endl;
    }
};
/* konkretan kolega/ucesnik  ConcreteColleague */
class CAdminUser: public IUser {
public:
    CAdminUser(const string& username): IUser(username) {}
    virtual ~CAdminUser() {}
    virtual void Send(const string& receiver, const string& message) {
        if (m_chatroom == NULL) throw("Invalid chatroom");
        m_chatroom->SendMessage(m_username, receiver, "[from admin] " + message);
    }
    virtual void Broadcast(const string& message) {
        if (m_chatroom == NULL) throw("Invalid chatroom");
        m_chatroom->BroadcastMessage(m_username, "[from admin] " + message);
    }
    virtual void Receive(const string& sender, const string& message) {
        cout << m_username << " received message: [" << sender << "] " << message << endl;
    }
};
/* konkretan posrednik/medijator ConcreteMediator */
class CChatroom: public IChatroom {
public:
    CChatroom() {}
    virtual ~CChatroom() { }
    virtual void EnterRoom(IUser* user) {
        if (user == NULL) throw("Invalid user");
        user->SetChatroom(this);
        m_users[user->GetUsername()] = user;
        cout << "Chatroom > " + user->GetUsername() + " entered the chatroom." << endl;
        BroadcastMessage("Chatroom", user->GetUsername() + " entered the chatroom.");
    }
    virtual void ExitRoom(IUser* user) {
        if (user == NULL) throw("Invalid user");
        user->SetChatroom(NULL);
        m_users.erase(user->GetUsername());
        cout << "Chatroom > " + user->GetUsername() + " left the chatroom." << endl;
        BroadcastMessage("Chatroom", user->GetUsername() + " left the chatroom.");
    }
    virtual void SendMessage(const string& sender, const string& receiver, const string& message) {
        if (m_users.find(receiver) == m_users.end()) throw("Receiver doesn't exist.");
        IUser *recepient = m_users[receiver];
        recepient->Receive(sender, message);
    }
    virtual void BroadcastMessage(const string& sender, const string& message) {
        for (map<string, IUser*>::iterator it = m_users.begin(); it != m_users.end(); ++it) {
            if (it->second->GetUsername() != sender) {
                it->second->Receive(sender, message);
            }
        }
    }
protected:
    map<string, IUser*>   m_users;
};

/* kreiramo nekoliko konkretnih korisnika razlicitog tipa (admin, normal)
   zatim kreiramo chat sobu, udjemo sa korisnicima u sobu i nakon toga
   razliciti korisnici salju razlicite poruke
   na ekranu mozemo da vidimo kako tece komunikacija, ko salje koju poruku
   a ko prima kakvu poruku */
int main() {
    IUser* aca = new CAdminUser("Aca");
    IUser* braca = new CNormalUser("Braca");
    IUser* caca = new CNormalUser("Caca");
    IUser* daca = new CNormalUser("Daca");
    IUser* faca = new CNormalUser("Faca");

    IChatroom* chatroom = new CChatroom();
    try {
        chatroom->EnterRoom(aca);
        chatroom->EnterRoom(braca);
        chatroom->EnterRoom(caca);
        chatroom->EnterRoom(daca);
        chatroom->EnterRoom(faca);

        aca->Send("Braca", "Zdravo, Braco! Nemoj mnogo da spamujes inace ide kick.");
        braca->Send("Aca", "Nema problema, smiricu se");
        caca->Broadcast("Hajde svi kod mene na zurku!!");
        daca->Send("Caca", "E ne mogu treba tetki lek da odnesem");
        faca->Send("Caca", "Ja cu da idem samo ako ima besplatno da se jede i pije :)");
        aca->Broadcast("Zabranjeno je reklamiranje na chatu");
        chatroom->ExitRoom(aca);
        braca->Send("Aca", "Admine, daj mi dozvolu");
    } catch (const char* e) {
        cout << "ERROR: " << e << endl;
    }
    delete aca;
    delete braca;
    delete caca;
    delete daca;
    delete faca;
    delete chatroom;

    return 0;
}
