/* primer iz knjige GoF Design Patterns */
class TCPOctetStream;
class TCPState;
class TCPClosed;
/* kontekst, TCP veza/konekcija
   koja interno ima instancu stanja TCPState */
class TCPConnection {
public:
    TCPConnection();
    void ActiveOpen();
    void PassiveOpen();
    void Close();
    void Send();
    void Acknowledge();
    void Synchronize();
    void ProcessOctet(TCPOctetStream*) {}
private:
    friend class TCPState;
    void ChangeState(TCPState*);
private:
    TCPState* _state;
};
/* apstraktno stanje / state
   ima razlicite metode koji imaju ulogu metoda Handle iz seme obrasca */
class TCPState {
public:
    virtual void Transmit(TCPConnection*, TCPOctetStream*);
    virtual void ActiveOpen(TCPConnection*);
    virtual void PassiveOpen(TCPConnection*);
    virtual void Close(TCPConnection*);
    virtual void Synchronize(TCPConnection*);
    virtual void Acknowledge(TCPConnection*) {}
    virtual void Send(TCPConnection*) {}
protected:
    void ChangeState(TCPConnection*, TCPState*);
};
/* konkretno stanje / concrete state
   predstavlja stanje kada je TCP veza ostvarena */
class TCPEstablished : public TCPState {
public:
    static TCPState* Instance() { static TCPEstablished state; return &state; }
    virtual void Transmit(TCPConnection*, TCPOctetStream*);
    virtual void Close(TCPConnection*);
};
/* konkretno stanje / concrete state
   kada se ocekuju nove konekcije */
class TCPListen : public TCPState {
public:
    static TCPState* Instance() { static TCPListen state; return &state; }
    virtual void Send(TCPConnection*);
};
/* konkretno stanje / concrete state
   zatvorena konekcija */
class TCPClosed : public TCPState {
public:
    static TCPState* Instance() { static TCPClosed state; return &state; }
    virtual void ActiveOpen(TCPConnection*);
    virtual void PassiveOpen(TCPConnection*);
};

TCPConnection::TCPConnection() { _state = TCPClosed::Instance(); }
void TCPConnection::ChangeState(TCPState *s) { _state = s; }
void TCPConnection::ActiveOpen() { _state->ActiveOpen(this); }
void TCPConnection::PassiveOpen() { _state->PassiveOpen(this); }
void TCPConnection::Close() { _state->Close(this); }
void TCPConnection::Acknowledge() { _state->Acknowledge(this); }
void TCPConnection::Synchronize() { _state->Synchronize(this); }

void TCPState::Transmit(TCPConnection*, TCPOctetStream*) {}
void TCPState::ActiveOpen(TCPConnection*) {}
void TCPState::PassiveOpen(TCPConnection*) {}
void TCPState::Close(TCPConnection*) {}
void TCPState::Synchronize(TCPConnection*) {}
void TCPState::ChangeState(TCPConnection *t, TCPState *s) { t->ChangeState(s); }

void TCPClosed::ActiveOpen(TCPConnection *t) { ChangeState(t, TCPEstablished::Instance()); }
void TCPClosed::PassiveOpen(TCPConnection *t) { ChangeState(t, TCPListen::Instance()); }

void TCPEstablished::Close(TCPConnection *t) { ChangeState(t, TCPListen::Instance()); }
void TCPEstablished::Transmit(TCPConnection *t, TCPOctetStream *o) { t->ProcessOctet(o); }

void TCPListen::Send(TCPConnection *t) { ChangeState(t, TCPEstablished::Instance()); }

int main() {
    TCPConnection connection;
    connection.ActiveOpen();

    return 0;
}
