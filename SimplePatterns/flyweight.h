#pragma once

#include <string>
#include <iostream>
#include <map>
using namespace std;

/* Tiny string handle - only 1 byte */

struct StringFlyweight {
	uint8_t id;
	operator string& () const;
};

class FlyweightFactory {
	static string strs[256];
	static uint8_t cnt;
public:
	static StringFlyweight add(const string& str);
	friend struct StringFlyweight;
};

void flyweight_test();