#include <map>
#include <iostream>

using namespace std;

typedef map<string, int> MojaMapa;
typedef MojaMapa::iterator MapaIter;

void prikazi(map<string, int> mapa) {
    for (MapaIter it = mapa.begin(); it != mapa.end(); ++it) {
        cout << "(" << it->first << "," << it->second << ") ";
    }
    cout << endl;
}

int main() {
    map<string, int> so;
    so["Pera"] = 5;
    so["Zika"] = 4;
    so["Mika"] = 2;
    so["Aca"] = 4;
    prikazi(so);
    /*
    so.erase("Mika");
    prikazi(so);
    so.erase(so.begin(), ++(++so.begin()));
    prikazi(so);
    */
    MapaIter it = so.lower_bound("Aca");
    cout << it->first << "," << it->second << endl;

    if (so.find("Aca") != so.end()) {
        cout << so["Aca"] << endl;
    } else {
        cout << "Nema Ace u mapi" << endl;
    }
    so.clear();
    cout << so.size() << endl;

    cout << so.empty() << endl;

    return 0;
}
