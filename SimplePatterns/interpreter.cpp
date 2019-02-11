#include "interpreter.h"

#include <iostream>
using namespace std;

bool VariableExp::Evaluate(VarValueTable & varTable) {
	return varTable.GetVal(m_VarName);
}

/* Funkcije klase VarValueTable */
bool VarValueTable::GetVal(char varName) {
	return m_Table[varName];
}

void VarValueTable::SetVal(VariableExp *ptrVarExp, bool bl) {
	m_Table[(ptrVarExp->GetName())] = bl;
	return;
}

bool AndExp::Evaluate(VarValueTable & varTable) {
	return m_pOp1->Evaluate(varTable) && m_pOp2->Evaluate(varTable);
}

void interpreter_test() {
	BooleanExp* expression;
	VarValueTable varTable;
	VariableExp* x = new VariableExp('X');
	VariableExp* y = new VariableExp('Y');

	/* (TRUE and x) or (y and (not x)) */
	expression = new OrExp (
		new AndExp(
			new Constant(true),
			x
		),
		new AndExp(
			y,
			new NotExp(x)
		)
	);

	varTable.SetVal(x, false);
	varTable.SetVal(y, true);

	bool res = expression->Evaluate(varTable);

	cout << " Rezulat (TRUE and x) or (y and (not x)) za x = "
		<< (varTable.GetVal(x->GetName()) ? "TRUE" : "FALSE")
		<< " i y = " << (varTable.GetVal(y->GetName()) ? "TRUE" : "FALSE")
		<< " je " << (res ? "TRUE" : "FALSE") << endl;


}

bool OrExp::Evaluate(VarValueTable & varTable) {
	return m_pOp1->Evaluate(varTable) || m_pOp2->Evaluate(varTable);
}

bool NotExp::Evaluate(VarValueTable & varTable) {
	return !m_Op->Evaluate(varTable);
}

bool Constant::Evaluate(VarValueTable & varTable) {
	return m_val;
}
