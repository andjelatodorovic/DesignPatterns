#pragma once

/* Prepisao Banetov primer */

#include <map>
using namespace std;

class VariableExp;

class VarValueTable {
public:
	VarValueTable() { m_Table.clear(); }
	bool GetVal(char);
	void SetVal(VariableExp*, bool);
private:
	/* Implementirana kao balansirano binarno stablo */
	map<char, bool> m_Table;
};

/* Apstraktna klasa gramatickog pravila */
class BooleanExp {
public:
	BooleanExp() {};
	virtual ~BooleanExp() {};
	virtual bool Evaluate(VarValueTable&) = 0;
};

/*VariableExp :: = 'A' | 'B' | ... | 'X' | 'Y' | 'Z' */
class VariableExp : public BooleanExp {
public:
	VariableExp(char varName) : m_VarName(varName) {}
	virtual ~VariableExp() {};
	virtual bool Evaluate(VarValueTable &varTable);
	virtual char GetName() { return m_VarName; };
private:
	char m_VarName;
};

/* AndExp :: = BooleanExp 'and' BooleanExp */
class AndExp : public BooleanExp {
public:
	AndExp(BooleanExp *ptrOp1, BooleanExp *ptrOp2) : m_pOp1(ptrOp1), m_pOp2(ptrOp2) {}
	virtual ~AndExp() {};
	virtual bool Evaluate(VarValueTable& varTable);
private:
	BooleanExp *m_pOp1, *m_pOp2;
};

/* OrExp :: = BooleanExp 'or' BooleanExp */
class OrExp : public BooleanExp {
public:
	OrExp(BooleanExp* ptrOp1, BooleanExp* ptrOp2) : m_pOp1(ptrOp1), m_pOp2(ptrOp2) {}
	virtual ~OrExp() {};
	virtual bool Evaluate(VarValueTable &varTable);
private:
	BooleanExp* m_pOp1, *m_pOp2;
};

/* NotExp :: = 'not' BooleanExp */
class NotExp : public BooleanExp {
public:
	NotExp(BooleanExp *ptrOp) : m_Op(ptrOp) {}
	virtual ~NotExp() {};
	virtual bool Evaluate(VarValueTable& varTable);
private:
	BooleanExp * m_Op;
};

/* Constant :: = 'true' | 'false‘ */
class Constant : public BooleanExp {
public:
	Constant(bool val) : m_val(val) {}
	virtual bool Evaluate(VarValueTable &varTable);
private:
	bool m_val;
};

void interpreter_test();

