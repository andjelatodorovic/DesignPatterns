#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

struct FileInfoReport {
    string      ext;
    __int64     count;
    __int64     size;
};

class FileStructure {
public:
    FileStructure(string name): m_name(name) {}
    virtual ~FileStructure() {}
    virtual bool add(string componentName, shared_ptr<FileStructure> structure) = 0;
    virtual bool remove(string componentName) = 0;
    virtual pair<int, int> count() = 0;
    virtual int size() = 0;
    virtual void print(string tab = "") = 0;
    virtual map<string, FileInfoReport> report() = 0;
    virtual string name() { return m_name; }
    virtual void printReport() {
        cout << "**** FILE REPORT FOR " << m_name << " ****" << endl;
        map<string, FileInfoReport> rep = report();
        for (auto val: rep) {
            cout << "[" << val.first << "] - " << val.second.count << " file(s), "
                        << val.second.size/1024 << " KB" << endl;
        }
        cout << "**** END OF REPORT ****" << endl;
    }
protected:
    string  m_name;
};

class File: public FileStructure  {
public:
    File(string name, int size): FileStructure(name), m_size(size) {
        m_type = "";
        size_t idx = m_name.find_last_of(".");
        if (idx != string::npos) m_type = m_name.substr(idx+1);
    }
    virtual ~File() { cout << "Brisem fajl <" << m_name << ">" << endl; }
    virtual bool add(string componentName, shared_ptr<FileStructure> structure) {
        return false;
    }
    virtual bool remove(string componentName) {
        return m_name == componentName;
    }
    virtual pair<int, int> count() { return {1, 0}; }
    virtual int size() { return m_size; }
    virtual void print(string tab = "") {
        cout << tab << "- " << m_name << " [" << m_type << ", " << m_size/1024 << "KB]" << endl;
    }
    virtual map<string, FileInfoReport> report() {
        return map<string, FileInfoReport> { {m_type, {m_type, 1, m_size}} };
    }
protected:
    int     m_size;
    string  m_type;
};

class Directory: public FileStructure {
public:
    Directory(string name): FileStructure(name) {}
    virtual ~Directory() { cout << "Brisem direktorijum [" << m_name << "]" << endl; }
    virtual bool add(string componentName, shared_ptr<FileStructure> structure) {
        if (componentName == m_name) {
            m_subcomponents.push_back(structure);
            return true;
        }
        for (shared_ptr<FileStructure> subs: m_subcomponents) {
            if (subs->add(componentName, structure)) return true;
        }
        return false;
    }
    virtual bool remove(string componentName) {
        for (vector<shared_ptr<FileStructure> >::iterator it = m_subcomponents.begin();
                it != m_subcomponents.end(); ++it) {
            if ((*it)->remove(componentName)) return true;
            if ((*it)->name() == componentName) {
                m_subcomponents.erase(it);
                return true;
            }
        }
        return false;
    }
    virtual pair<int, int> count() {
        pair<int, int> counter;
        counter.second++;
        for (shared_ptr<FileStructure> sub: m_subcomponents) {
            auto subCounter = sub->count();
            counter.first += subCounter.first;
            counter.second += subCounter.second;
        }
        return counter;
    }
    virtual int size() {
        int total = 0;
        for (shared_ptr<FileStructure> sub: m_subcomponents) {
            total += sub->size();
        }
        return total;
    }
    virtual void print(string tab = "") {
        cout << tab << "+ " << m_name << " [" << this->size()/1024 << "KB]" << endl;
        for (shared_ptr<FileStructure> sub: m_subcomponents) {
            sub->print(tab+"  ");
        }
    }
    virtual map<string, FileInfoReport> report() {
        map<string, FileInfoReport> rep;
        for (shared_ptr<FileStructure> sub: m_subcomponents) {
            auto subRep = sub->report();
            for (auto key: subRep) {
                if (rep.find(key.first) == rep.end()) {
                    rep[key.first] = key.second;
                } else {
                    rep[key.first].count += key.second.count;
                    rep[key.first].size += key.second.size;
                }
            }
        }
        return rep;
    }
protected:
    vector<shared_ptr<FileStructure> >  m_subcomponents;
};

int main() {
    shared_ptr<FileStructure> root = make_shared<Directory>("ROOT");

    root->add("ROOT", make_shared<Directory>("Docs"));
    root->add("ROOT", make_shared<Directory>("Downloads"));

    root->add("Docs", make_shared<File>("seminarski.doc", 12345));
    root->add("Docs", make_shared<File>("slika.jpg", 4345));
    root->add("Downloads", make_shared<File>("knjiga.pdf", 123455));
    root->add("Downloads", make_shared<File>("instalacija.exe", 43345));
    root->add("__system", make_shared<File>("virus.exe", 43345));

    auto counter = root->count();

    cout << "Broj fajlova: " << counter.first << endl << "Broj direktorijuma: " << counter.second << endl;
    cout << "Ukupna velicina: " << root->size() << endl;

    root->print();
    root->printReport();

    cout << "Brisem direktorijum [Downloads]..." << endl;

    root->remove("Downloads");

    root->print();
    root->printReport();

    return 0;
}
