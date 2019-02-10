#include <iostream>
#include <cstring>

using namespace std;

/* singleton sablon, jedinstven primerak kreiramo putem loklane staticke promenljive unutar
    funkcije getInstance, kontruktori su privatni */
class FileSystem {
public:
    static FileSystem& getInstance() {
        static FileSystem s_fileSystem;
        return s_fileSystem;
    }
    void writeFile(string file) {
        cout << "Pisem file: '" << file << "'" << endl;
    }
    string readFile() {
        return "Procitani file";
    }
private:
    FileSystem() { }
    FileSystem(const FileSystem& fileSystem) { }
    FileSystem& operator=(const FileSystem& fileSystem) { }
};

int main() {
    FileSystem &fileSystem = FileSystem::getInstance();
    fileSystem.writeFile("test file");
    cout << FileSystem::getInstance().readFile() << endl;

    return 0;
}
