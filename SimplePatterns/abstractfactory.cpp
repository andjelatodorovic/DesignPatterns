#include "abstractfactory.h"

template<class T>
inline void Factory<T>::Register(int id, Creator<T>* ptrToCreator) {
	auto it = creatorRegister.find(id);
	if (it != creatorRegister.end()) {
		delete it->second;
		it->second = ptrToCreator;
	} else {
		creatorRegister[id] = ptrToCreator;
	}
}

template<class T>
inline T * Factory<T>::Create(int id) { return creatorRegister[id]->Create(); }

template<class T>
inline Factory<T>::~Factory() {
	for (auto& it : creatorRegister) {
		delete it.second;
	}
}

void abstractfactory_test() {
	Factory<AbsProduct> temp;
	temp.Register(0, new DerivedCreator<Product_A, AbsProduct>);
	temp.Register(1, new DerivedCreator<Product_B, AbsProduct>);

	AbsProduct* product = 0;

	product = temp.Create(0);
	cout << "Product_A: " << product->Get() << endl;
	delete product;

	product = temp.Create(1);
	cout << "Product_B: " << product->Get() << endl;
	delete product;
}