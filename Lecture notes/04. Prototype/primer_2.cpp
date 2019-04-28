#include <iostream>
#include <string>
#include <map>

using namespace std;

// Apstraktni Prototip
class Cell {
protected:
	string type;
	static map<string, Cell*> cells;
public:
	virtual Cell* clone() = 0;
	string getType() { return type; }

	static Cell* get(string key) {
		if (cells.find(key) != cells.end()) {
			return cells[key];
		}
		return nullptr; // U G++ mozda error zbog scope-a
	}
	
	static void addCell(string key, Cell* p) {
		cells[key] = p;
	}
	static void clearCells() {
		cells.clear();
	}
	virtual void print() = 0;
};

// Konkretan prototip
class RedCell : public Cell {
public:
	RedCell(const string _type) {
		type = _type;
	}

	Cell* clone() {
		return new RedCell(*this);
	}

	void print() { cout << "Ja sam crveno krvno zrnce: " << type << endl; }
};

// Konkretan prototip
class WhiteCell : public Cell {
public:
	WhiteCell(const string _type) {
		type = _type;
	}

	Cell* clone() {
		return new WhiteCell(*this);
	}

	void print() { cout << "Ja sam crveno krvno zrnce: " << type << endl; }
};

map<string, Cell*> Cell::cells; // Mora da se definise kako bi kompajler odvoji prostor

int main() {
	Cell::addCell("crvena_virus", new RedCell("crvena_virus"));
	Cell::addCell("crvena_grip", new RedCell("crvena_grip"));
	Cell::addCell("bela_grip", new WhiteCell("bela_grip"));
	Cell::addCell("bela_posekotina", new WhiteCell("bela_posekotina"));

	Cell* celija = Cell::get("crvena_virus");
	celija->print();

	celija = Cell::get("bela_grip");
	celija->print();

	delete celija;
	Cell::clearCells();

}
