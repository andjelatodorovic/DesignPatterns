#include <iostream>

using namespace std;

/* apstraktna komponenta, ime metode za citanje/pisanje po stream-u i prikaz sadrzaja streama */
class IStream {
public:
    virtual char read() = 0;
    virtual void write(char ch) = 0;
    virtual string content() = 0;
};
/* konkretna komponenta - nasledjuje IStream i implementira stream da radi na string-u kao podlozi */
class CStringStream: public IStream {
public:
    CStringStream() { m_content = ""; iRead = 0; }
    virtual char read() {
        cout << "citam " << iRead << endl;
        if (iRead == m_content.size()) return 0;
        return m_content[iRead++];
    }
    virtual void write(char ch) {
        cout << "pisem " << ch << endl;
        m_content += string(1, ch);
    }
    virtual string content() { cout << "Sadrzaj streama: '" << m_content << "'" << endl; return m_content; }
protected:
    string  m_content;
    int     iRead;
};
/* apstraktna dopuna / dekorater - nasledjuje komponentu */
class IStreamDecorator: public IStream {
public:
    IStreamDecorator(IStream *stream): m_stream(stream) {}
    virtual ~IStreamDecorator() { if (m_stream != NULL) delete m_stream; }
    virtual char read() = 0;
    virtual void write(char ch) = 0;
    virtual string content() = 0;
protected:
    IStream*    m_stream;
};
/* konkretna dopuna - dodaje svojstvo da upisuje i iscitaje mala slova kao velika */
class CLargeCaseStreamDecorator: public IStreamDecorator {
public:
    CLargeCaseStreamDecorator(IStream *stream): IStreamDecorator(stream) {}
    virtual char read() {
        char ch = m_stream->read();
        if (ch != 0 && ch >= 'a' && ch <= 'z') ch = 'A' + ch - 'a';
        return ch;
    }
    virtual void write(char ch) {
        if (ch >= 'a' && ch <= 'z') {
            m_stream->write('A' + ch - 'a');
        } else {
            m_stream->write(ch);
        }
    }
    virtual string content() {
        return m_stream->content();
    }
};
/* konkretna dopuna - dodaje svojstvo da korisnik mora da bude identifikovan/autentikovan
   prilikom poziva read/write/content metoda na streamu */
class CAuthenticationStreamDecorator: public IStreamDecorator {
public:
    CAuthenticationStreamDecorator(IStream *stream, string password): m_password(password), IStreamDecorator(stream) {}
    virtual char read() {
        if (authenticate()) {
            return m_stream->read();
        } else {
            cout << "ERROR: password incorrect\n";
            return 0;
        }
    }
    virtual void write(char ch) {
        if (authenticate()) {
            return m_stream->write(ch);
        } else {
            cout << "ERROR: password incorrect\n";
        }
    }
    virtual string content() {
        if (authenticate()) {
            return m_stream->content();
        } else {
            cout << "ERROR: password incorrect\n";
            return "";
        }
    }
protected:
    string  m_password;
private:
    bool authenticate() {
        string password;
        cout << "PASSWORD: ";
        cin >> password;
        return (m_password == password);
    }
};
/* konkretna dopuna - dodaje svojstvo sifrovanja prilikom poziva read/write/content metoda na streamu */
class CEncodeStreamDecorator: public IStreamDecorator {
public:
    CEncodeStreamDecorator(IStream *stream, char shift): m_shift(shift), IStreamDecorator(stream) {}
    virtual char read() {
        char ch = m_stream->read();
        if (ch != 0) return ch - m_shift;
        return 0;
    }
    virtual void write(char ch) {
        return m_stream->write(ch + m_shift);
    }
    virtual string content() {
        string result = m_stream->content();
        for (int iResult = 0; iResult < result.size(); iResult++) {
            result[iResult] -= m_shift;
        }
        return result;
    }
protected:
    char    m_shift;
};

/* kreiramo instancu konkretne komponente CStringStream i obogatimo je novim svojstvima
   putem dopuna CAuthenticationStreamDecorator i CEncodeStreamDecorator
   cesto je veoma bitan redosled dodavanja dopuna i zadatak je onog ko projektuje sistem
   koji stepen slobode ce da omoguci klijentima kao i koji su sporedni efekti razlicitog
   kombinovanja dekoratera */
int main() {
    IStream *stream = new CStringStream();
    IStreamDecorator *authEncStream =
        new CAuthenticationStreamDecorator(
        new CEncodeStreamDecorator(stream, 1), "p");

    authEncStream->write('D');
    authEncStream->write('e');
    authEncStream->write('j');
    authEncStream->write('a');
    authEncStream->write('n');

    cout << "Citam sadrzaj stream-a: ";
    cout << "'" << authEncStream->content() << "'" << endl;

    delete authEncStream;
    delete stream;
}
