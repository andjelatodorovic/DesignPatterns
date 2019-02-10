#include <iostream>
#include <sstream>
#include <memory>

using namespace std;

/* sablon metod se cesto koristi u realizaciji okruzenja/framework za razlicite svrhe
   ovde cemo da ponudimo okruzenje za razvoj igara na tabli
   sablon metod/template method je Run
   koji je implementiran pozivajuci virtuelne metode klase Init, Draw, IsEnd...
   koji ce biti realizovani u konkretnim klasama koje nasledjuju IBoardGameFramework
   ali koraci rati u sablon metodu Run nece biti menjani */
class IBoardGameFramework {
public:
    virtual void Init() = 0;
    virtual void Draw() = 0;
    virtual bool IsEnd() = 0;
    virtual void Move(int idPlayer) = 0;
    virtual int NextPlayer(int currentPlayer) = 0;
    virtual void Close() = 0;
    void Run() {
        Init();
        while (!IsEnd()) {
            Draw();
            Move(m_currentPlayer);
            m_currentPlayer = NextPlayer(m_currentPlayer);
        }
        Close();
    }
protected:
    int m_currentPlayer;
};
/* konkretna klasa koja realizuje metode koriscene u sablon metodu */
class CChess: public IBoardGameFramework {
public:
    virtual void Init() {
        m_numPlayers = 2;
        m_currentPlayer = 0;
        m_table << "Chess table" << endl;
    }
    virtual void Draw() {
        cout << "Drawing chess table [" << endl << m_table.str() << "]" << endl;
    }
    virtual bool IsEnd() {
        if (m_numMoves >= 5) return true;
        return false;
    }
    virtual void Move(int idPlayer) {
        cout << "Igrac [" << idPlayer << "] koji potez ces da povuces > ";
        string potez;
        cin >> potez;
        m_table << " POTEZ [" << idPlayer << "] " << potez << endl;
        m_numMoves++;
    }
    virtual int NextPlayer(int currentPlayer) {
        return (currentPlayer + 1) % 2;
    }
    virtual void Close() {
        cout << "Zavrsena partija saha. Krajnje stanje " << m_table.str() << endl;
    }
protected:
    int             m_numPlayers;
    int             m_numMoves;
    ostringstream   m_table;
};
/* kreiramo instancu igre i pozovemo sablon metod run */
int main() {
    unique_ptr<IBoardGameFramework> game(new CChess());
    game->Run();

    return 0;
}
