#pragma once

class Singleton {
public:
	static Singleton& Instance();
	virtual void Operation();
protected:
	Singleton() {}
	~Singleton() {}
private:
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&) = default;
};

class LosSingleton {
public:
	static LosSingleton& Instance();
	virtual void Operation();
protected:
	LosSingleton() {}
	~LosSingleton() {}
private:
	LosSingleton(const LosSingleton&);
	LosSingleton& operator=(const LosSingleton&) = default;
	static LosSingleton* ptr;
};

void singleton_test();
