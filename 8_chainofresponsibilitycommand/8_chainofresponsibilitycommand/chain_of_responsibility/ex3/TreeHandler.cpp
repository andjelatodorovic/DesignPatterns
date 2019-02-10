#include <cstdio>
#include <iostream>

using namespace std;

/* zahtev / request */
class Request {
public:
    Request(): m_type(0) {}
    Request(int type): m_type(type) {}
    ~Request() {}
    void SetType(int type) {
        m_type = type;
    }
    int GetType() const {
        return m_type;
    }
protected:
    int     m_type;
};
/* Handler / razresavac
   efikasan je jer uvek na prvo mesto u lancu odgovornosti stavi onaj handler koji je poslednji
   odgovorio na zahtev */
class EfficientHandler {
public:
    static EfficientHandler*    s_rootHandler;
    static void setRootHandler(EfficientHandler *rootHandler) {
        EfficientHandler::s_rootHandler = rootHandler;
    }
    static void handle(const Request& request) {
        if (EfficientHandler::s_rootHandler != NULL) {
            EfficientHandler::s_rootHandler->handle(NULL, request);
        }
    }

    EfficientHandler(): m_nextHandler(NULL) {}
    virtual void handle(EfficientHandler *prevHandler, const Request& request) {
        if (m_nextHandler != NULL) {
            m_nextHandler->handle(prevHandler, request);
        } else {
            // proverili smo sve razresavac zahteva
            // mozemo da ne radimo nista
            // mozemo da damo exception
            // mozemo da vratimo neki uopsten rezultat kao odgovor
            // ..
            cout << "Request can't be handled." << endl;
        }
    }
    void setNextHandler(EfficientHandler *nextHandler) {
        m_nextHandler = nextHandler;
    }
    void updateHandler(EfficientHandler *prevHandler) {
        if (prevHandler != NULL) {
            prevHandler->m_nextHandler = m_nextHandler;
        }
        m_nextHandler = s_rootHandler;
        s_rootHandler = this;
    }
protected:
    EfficientHandler*   m_nextHandler;
};

EfficientHandler *EfficientHandler::s_rootHandler = NULL;

class EfficientHandlerOne: public EfficientHandler {
public:
    void handle(EfficientHandler *prevHandler, const Request& request) {
        cout << "EfficientHandlerOne::handle()" << endl;
        if (canHandle(request)) {
            cout << "HandlerOne handled the request." << endl;
            EfficientHandler::updateHandler(prevHandler);
        } else {
            EfficientHandler::handle(this, request);
        }
    }
    bool canHandle(const Request& request) {
        // uslovi da ovaj handler moze da razresi
        // trenutni zahtev
        // npr. return request->getType() == 1;
        return request.GetType() == 1;
    }
};

class EfficientHandlerTwo: public EfficientHandler {
public:
    void handle(EfficientHandler *prevHandler, const Request& request) {
        cout << "EfficientHandlerTwo::handle()" << endl;
        if (canHandle(request)) {
            cout << "HandlerTwo handled the request." << endl;
            EfficientHandler::updateHandler(prevHandler);
        } else {
            EfficientHandler::handle(this, request);
        }
    }
    bool canHandle(const Request& request) {
        // uslovi da ovaj handler moze da razresi
        // trenutni zahtev
        // npr. return request->getType() == 2;
        return request.GetType() == 2;
    }
};

class EfficientHandlerThree: public EfficientHandler {
public:
    void handle(EfficientHandler *prevHandler, const Request& request) {
        cout << "EfficientHandlerThree::handle()" << endl;
        if (canHandle(request)) {
            cout << "HandlerThree handled the request." << endl;
            EfficientHandler::updateHandler(prevHandler);
        } else {
            EfficientHandler::handle(this, request);
        }
    }
    bool canHandle(const Request& request) {
        // uslovi da ovaj handler moze da razresi
        // trenutni zahtev
        // npr. return request->getType() == 2;
        return request.GetType() == 3;
    }
};

int main() {
    EfficientHandler *rootHandler = new EfficientHandlerOne();
    EfficientHandler *handler2 = new EfficientHandlerTwo();
    EfficientHandler *handler3 = new EfficientHandlerThree();
    rootHandler->setNextHandler(handler2);
    handler2->setNextHandler(handler3);

    EfficientHandler::setRootHandler(rootHandler);

    EfficientHandler::handle(Request(2));
    EfficientHandler::handle(Request(3));
    EfficientHandler::handle(Request(1));
    EfficientHandler::handle(Request(4));

    delete rootHandler;
    delete handler3;
    delete handler2;

    return 0;
}
