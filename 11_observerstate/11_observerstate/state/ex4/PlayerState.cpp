#include <string>
#include <iostream>

using namespace std;
/* dogadjaj na tastaturi, npr. igrac pomera igraca i pritiska odredjene tastere da bi pomerao igraca na odredjeni nacin */
class KeyboardEvent {
public:
    KeyboardEvent(const string& code) {
        if (code == "A" || code == "a") m_code = "LEFT_ARROW";
        else if (code == "D" || code == "d") m_code = "RIGHT_ARROW";
        else if (code == "W" || code == "w") m_code = "UP_ARROW";
        else if (code == "S" || code == "s") m_code = "DOWN_ARROW";
        else m_code = "UNKNOWN";
    }
    string GetCode() { return m_code; }
protected:
    string  m_code;
};

class PlayerState;
class PlayerStandingState;
class PlayerSittingState;
class PlayerJumpingState;
class PlayerMovingRightState;
class PlayerMovingLeftState;
/* kontekst,
   igrac u igri, koji tokom igre moze da se nadje u razlicitim stanjima,
   u zavisnosti od trenutnog stanja i nacin kretanja igraca na komandu onog ko igra bice razlicita */
class Player {
public:
    Player();
    virtual ~Player() {}
    virtual void HandleInput(KeyboardEvent &event);
    virtual void SetState(PlayerState* state) { m_state = state; }
    virtual void Show();
protected:
    PlayerState*    m_state;
};
/* apstraktno stanje,
   ima metod da razresi trenutni dogadjaj na tastaturi, prosledjuje se i referenca na igraca na kom
   se desio dogadjaj */
class PlayerState {
public:
    PlayerState() {}
    virtual ~PlayerState() {}
    virtual void HandleInput(Player& player, KeyboardEvent& event) = 0;
    virtual void Show() = 0;
};
/* konkretno stanje,
   predstavlja stanje kada igrac stoji */
class PlayerStandingState: public PlayerState {
public:
    PlayerStandingState() {}
    virtual ~PlayerStandingState() {}
    virtual void HandleInput(Player& player, KeyboardEvent& event);
    virtual void Show() {
        cout << "Player is standing" << endl;
    }
};
/* konkretno stanje,
   predstavlja stanje kada se igrac krece na levo */
class PlayerMovingLeftState: public PlayerState {
public:
    PlayerMovingLeftState() {}
    virtual ~PlayerMovingLeftState() {}
    virtual void HandleInput(Player& player, KeyboardEvent& event);
    virtual void Show() {
        cout << "Player is moving left" << endl;
    }
};
/* konkretno stanje,
   predstavlja stanje kada se igrac krece na desno */
class PlayerMovingRightState: public PlayerState {
public:
    PlayerMovingRightState() {}
    virtual ~PlayerMovingRightState() {}
    virtual void HandleInput(Player& player, KeyboardEvent& event);
    virtual void Show() {
        cout << "Player is moving right" << endl;
    }
};
/* konkretno stanje,
   predstavlja stanje kada igrac sedi */
class PlayerSittingState: public PlayerState {
public:
    PlayerSittingState() {}
    virtual ~PlayerSittingState() {}
    virtual void HandleInput(Player& player, KeyboardEvent& event);
    virtual void Show() {
        cout << "Player is sitting" << endl;
    }
};
/* konkretno stanje,
   predstavlja stanje kada igrac skace */
class PlayerJumpingState: public PlayerState {
public:
    PlayerJumpingState() {}
    virtual ~PlayerJumpingState() {}
    virtual void HandleInput(Player& player, KeyboardEvent& event);
    virtual void Show() {
        cout << "Player is jumping" << endl;
    }
};

Player::Player() { m_state = new PlayerStandingState(); }
void Player::Show() { cout << "[Player] "; m_state->Show(); }
void Player::HandleInput(KeyboardEvent &event) {
    m_state->HandleInput(*this, event);
}

/*
class PlayerStandingState;
class PlayerSittingState;
class PlayerJumpingState;
class PlayerMovingRightState;
class PlayerMovingLeftState;
*/

/* implementacije metoda HandleInput (Handle sa seme) za razlicita konkretna stanja */
void PlayerStandingState::HandleInput(Player& player, KeyboardEvent& event) {
    if (event.GetCode() == "LEFT_ARROW") {
        player.SetState(new PlayerMovingLeftState());
    } else if (event.GetCode() == "RIGHT_ARROW") {
        player.SetState(new PlayerMovingRightState());
    } else if (event.GetCode() == "DOWN_ARROW") {
        player.SetState(new PlayerSittingState());
    } else if (event.GetCode() == "UP_ARROW") {
        player.SetState(new PlayerJumpingState());
    } else {
        cout << "ERROR: Can't do " << event.GetCode() << " while standing." << endl;
    }
}

void PlayerSittingState::HandleInput(Player& player, KeyboardEvent& event) {
    if (event.GetCode() == "LEFT_ARROW") {
        cout << "ERROR: Can't do " << event.GetCode() << " while sitting." << endl;
    } else if (event.GetCode() == "RIGHT_ARROW") {
        cout << "ERROR: Can't do " << event.GetCode() << " while sitting." << endl;
    } else if (event.GetCode() == "DOWN_ARROW") {
        cout << "ERROR: I'm already sitting" << endl;
    } else if (event.GetCode() == "UP_ARROW") {
        player.SetState(new PlayerStandingState());
    } else {
        cout << "ERROR: Can't do " << event.GetCode() << " while sitting." << endl;
    }
}

void PlayerJumpingState::HandleInput(Player& player, KeyboardEvent& event) {
    if (event.GetCode() == "LEFT_ARROW") {
        player.SetState(new PlayerMovingLeftState());
    } else if (event.GetCode() == "RIGHT_ARROW") {
        player.SetState(new PlayerMovingRightState());
    } else if (event.GetCode() == "DOWN_ARROW") {
        player.SetState(new PlayerSittingState());
    } else if (event.GetCode() == "UP_ARROW") {
        player.SetState(new PlayerJumpingState());
    } else {
        cout << "ERROR: Can't do " << event.GetCode() << " while standing." << endl;
    }
}

void PlayerMovingRightState::HandleInput(Player& player, KeyboardEvent& event) {
    if (event.GetCode() == "LEFT_ARROW") {
        player.SetState(new PlayerStandingState());
    } else if (event.GetCode() == "RIGHT_ARROW") {
        player.SetState(new PlayerMovingRightState());
    } else if (event.GetCode() == "DOWN_ARROW") {
        player.SetState(new PlayerSittingState());
    } else if (event.GetCode() == "UP_ARROW") {
        player.SetState(new PlayerJumpingState());
    } else {
        cout << "ERROR: Can't do " << event.GetCode() << " while standing." << endl;
    }
}

void PlayerMovingLeftState::HandleInput(Player& player, KeyboardEvent& event) {
    if (event.GetCode() == "LEFT_ARROW") {
        player.SetState(new PlayerMovingLeftState());
    } else if (event.GetCode() == "RIGHT_ARROW") {
        player.SetState(new PlayerStandingState());
    } else if (event.GetCode() == "DOWN_ARROW") {
        player.SetState(new PlayerSittingState());
    } else if (event.GetCode() == "UP_ARROW") {
        player.SetState(new PlayerJumpingState());
    } else {
        cout << "ERROR: Can't do " << event.GetCode() << " while standing." << endl;
    }
}
/* kreiramo igraca, zatim pitamo korisnika sta zeli da radi sa igracem,
   nakon toga se prikaze trenutno stanje igraca */
int main() {
    Player player;
    string comm;
    do {
        cout << "What to do: [A] Move left, [D] Move right, [S] Sit down, [W] Jump, [Q] Quit: ";
        cin >> comm;
        KeyboardEvent event(comm);
        player.HandleInput(event);
        player.Show();
    } while (comm != "Q" && comm != "q");
    return 0;
}
