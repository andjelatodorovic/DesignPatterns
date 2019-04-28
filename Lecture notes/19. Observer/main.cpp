/*
	Ideja ovog uzorka je da za jedan objekat vezemo vise, kad se promeni stanje subjekta
	objekti koji su vezani (obzerveri) bivaju obavesteni.

	@Subject  			Cuva observere u listi i kad treba obavestva sve pozivom f-je iz Observer
	@Observer			Ima funkciju za obavestavanje koja se poziva od strane subjekta
	@ConcreteObserver	Redefinise funkciju za obavestavanje

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // remove();
#include <ctime>

using namespace std;

// Cisto radi primera

#define URL "https://share-videos/?v="
#define URL_LENGHT 12
const string URL_CHARS = "abcdefghijklmnopqrstuvwxyz0123456789";

// - Cisto radi primera

class Channel;

// Interfejs obzervera
class iUser {
public:
	iUser() {}
	virtual ~iUser() {}
	virtual void Notify(Channel*, const string&, const string&) = 0;
private:
	Channel* channel;
};

// Subjekat
class Channel {
private:
	string name;
	vector<iUser*> users; // SUBJEKAT ZNA SVOJE POSMATRACE
public:
	Channel(const string& _name) : name(_name) {}

	virtual void Subscribe(iUser* user) {
		users.push_back(user);
	}
	virtual void UnSubscribe(iUser* user) {
		users.erase(remove(users.begin(), users.end(), user)); //http://en.cppreference.com/w/cpp/algorithm/remove
	}

	virtual string ChannelName() { return name; }

	// Kad se on updatuje, obavesti sve.
	virtual void Upload(const string& title) {
		typedef vector<iUser*>::iterator iter;
		for (iter i = users.begin(); i != users.end(); i++) {
			(*i)->Notify(this, title, UrlGenerator());
		}
	}

	// RADI PRIMERA!!!
	const string UrlGenerator() {
		string url;
		for (int i = 0; i <= URL_LENGHT; i++) {
			int random = rand() % URL_CHARS.length();
			char c = URL_CHARS[random];
			if (random % 2) c = toupper(c);
			url += c;
		}
		return url;
	}
};

// Konkretan posmatrac
class User : public iUser {
public:
	User() {}
	virtual ~User() {}

	// Kad se subjekat promeni pozove ovu funkciju u svakom posmatracu
	void Notify(Channel* channel, const string& title, const string& url) {
		cout << channel->ChannelName() << " just uploaded a video: " << title << endl << URL << url << endl << endl;
	}
};

int main() {
	Channel* serb_craft = new Channel("Serb Craft");

	User* user1 = new User();
	User* user2 = new User();
	User* user3 = new User();
	User* user4 = new User();

	serb_craft->Subscribe(user1);
	serb_craft->Subscribe(user2);
	serb_craft->Subscribe(user3);
	serb_craft->Subscribe(user4);

	serb_craft->Upload("Kako manic12 pije vodu");
}
