#include <string>
#include <iostream>
#include <map>

using namespace std;

class IYouTubeUser;
/* apstraktan subjekt
   ima metode sa preplatu/subscribe/registrovanje posmatraca kao i za odregistrovanje
   kada se objavi novi video na kanalu metodom PublishVideo svi posmatraci koju su pretplaceni
   na kanal ce biti obavesteni o promeni
   pokazacemu dva primera - pull kod koga su posmatraci obavesteni kratko o nastupaloj promeni
   i budu obavesteni samo delimicno o novoj informaciji (npr. dobiju link za novi video a ne i
   ceo sadrzaj videa) pa imaju posle zadatak da koristeci taj link po zelji uzmu i ceo sadrzaj
   i drugi push - kod koga se prilikom obavestavanja pretplatnika prosledi i ceo sadrzaj */
class IYouTubeChannel {
public:
    typedef map<IYouTubeUser* const, IYouTubeUser* const> YouTubeUsersMap;
    typedef map<string, string> ContentMap;

    IYouTubeChannel(const string& channelName = ""): m_channelName(channelName) {}
    virtual ~IYouTubeChannel() {}
    virtual void Subscribe(IYouTubeUser& user) {
        m_users.insert(YouTubeUsersMap::value_type(&user, &user));
    }
    virtual void UnSubscribe(IYouTubeUser& user) {
        m_users.erase(&user);
    }
    virtual void PublishVideo(const string& url, const string& content) {
        m_content[url] = content;
        NotifyUsers(url, content);
    }
    virtual string& GetVideo(const string& url) {
        return m_content[url];
    }
    virtual const string& GetChannelName() const { return m_channelName; }
    virtual string& LoadVideo(const string& url) { return m_content[url]; }
protected:
    virtual void NotifyUsers(const string& url, const string& content) = 0;
    ContentMap      m_content;
    YouTubeUsersMap m_users;
    string          m_channelName;

};
/* apstraktan posmatrac, ima metod Notify preko koga kanal
   obavestava posmatraca da je postavljen novi video */
class IYouTubeUser {
public:
    IYouTubeUser() {}
    virtual ~IYouTubeUser() {}
    virtual void Notify(IYouTubeChannel& youTubeChannel, const string& content) = 0;
};
/* konkretan subjekt, obavestava subjekte metodom push - prosledjuje im ceo video, ne samo link za novi video */
class CYouTubeChannelPush: public IYouTubeChannel {
public:
    CYouTubeChannelPush(const string& channelName = ""): IYouTubeChannel(channelName) {}
protected:
    virtual void NotifyUsers(const string& url, const string& content) {
        for (YouTubeUsersMap::iterator it = m_users.begin(); it != m_users.end(); ++it) {
            it->second->Notify(*this, "<URL>\n\t" + url + "\n</URL>\n<VIDEO>\n\t" + content + "\n</VIDEO>\n");
        }
    }
};
/* konkretan subjekt, obavestava subjekte metodom pull - prosledjuje im samo delimicnu informaciju - u ovom slucaju
   link ka postavljenom videu, a posmatrac sada ima mogucnost da skine ceo sadrzaj ako mu je interesantan, koristeci
   prosledjeni link, ili da ignorise, i time ustedi resurse, i ne skine ceo sadrzaj videa */
class CYouTubeChannelPull: public IYouTubeChannel {
public:
    CYouTubeChannelPull(const string& channelName = ""): IYouTubeChannel(channelName) {}
protected:
    virtual void NotifyUsers(const string& url, const string& content) {
        for (YouTubeUsersMap::iterator it = m_users.begin(); it != m_users.end(); ++it) {
            it->second->Notify(*this, "<URL>\n\t" + url + "\n</URL>\n");
        }
    }
};

/* konkretan posmatrac */
class CYouTubeUser: public IYouTubeUser {
public:
    CYouTubeUser() {}
    virtual ~CYouTubeUser() {}
    virtual void Notify(IYouTubeChannel& youTubeChannel, const string& content) {
        cout << "YouTube user notified about video from the channel " << youTubeChannel.GetChannelName() << endl << content << endl;
        if (content.find("<VIDEO>") == string::npos) {
            string url = content.substr(content.find("<URL>") + 7, content.find("</URL>") - content.find("<URL>") - 8);
            cout << "User loading video from: " << url << "..." << endl;
            cout << "Video loaded: " << youTubeChannel.LoadVideo(url) << endl;
        }
    }
};
/* kreiramo dva razlicita konkretna kanala, jedan push, jedan pull
   kreiramo konkretne posmatrace,registrujemo ih na odgovarajuce kanale,
   a zatim na kanalima objavimo neki video i posmatramo tok izvrsavanja programa */
int main() {
    IYouTubeChannel* channel1 = new CYouTubeChannelPull("Smesni Video");
    IYouTubeChannel* channel2 = new CYouTubeChannelPush("Dokumentarni filmovi");

    IYouTubeUser* user1 = new CYouTubeUser();
    IYouTubeUser* user2 = new CYouTubeUser();
    IYouTubeUser* user3 = new CYouTubeUser();

    channel1->Subscribe(*user1);
    channel1->Subscribe(*user2);
    channel1->Subscribe(*user3);

    channel2->Subscribe(*user2);
    channel2->Subscribe(*user3);

    channel1->PublishVideo("http://youtube.com/?v=0A45bd23", "Skrivena kamera, ljudi uhvaceni u nezgodnim situacijama");

    channel2->PublishVideo("http://youtube.com/?v=0B5e331a", "Prvi Srpski ustanak, zbor u Orascu");

    delete channel1;
    delete channel2;

    delete user1;
    delete user2;
    delete user3;

    return 0;
}
