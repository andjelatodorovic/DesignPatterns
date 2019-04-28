//
// Created by Maverick on 5/4/2017.
//

#include <iostream>

using namespace std;

template <typename T>
class Array {
public:

    template <class U, typename SIZE>
    class iter {
        friend class Array;

    protected:
        U* array;
        SIZE position;
        iter(U* a, SIZE p = 0) : array(a), position(p) {}

    public:
        iter(const iter& other) : array(other.array), position(other.position) {}

        iter& operator= (const iter& other) {
            if (this != &other) {
                array = other.array;
                position = other.position;
            }
            return *this;
        }

        T* operator-> () const { return (array + position); }
        T& operator* () const { return array[position]; }
        T& operator[] (int n) { return array[position + n]; }

        iter& operator++() { position++; return *this; }
        iter& operator--() { position--; return *this; }

        const iter& operator++(int) { return iter(array, position++); }
        const iter& operator--(int) { return iter(array, position--); }

        const iter operator+ (int n) const { return iter(array, position + n); }
        const iter operator- (int n) const { return iter(array, position - n); }
        int operator-(const iter& other) { return position - other.position; }
        friend iter operator+ (int n, const iter& other) { return iter(other.array, other.position + n); }

        iter& operator+= (int n) { position += n; return *this; }
        iter& operator-= (int n) { position -= n; return *this; }

        bool operator== (const iter& other) { return (array + position) == (other.array + other.position); }
        bool operator!= (const iter& other) { return !(*this == other); }
        bool operator< (const iter& other) { return position < other.position; }

        bool operator<= (const iter& other) { return !(other.position < position); }
        bool operator> (const iter& other) { return other.position < position; }
        bool operator>= (const iter& other) { return !(position < other.position); }

    };
    typedef T value_type;
    typedef unsigned size_type;
    typedef iter<T, size_type> iterator;
    typedef iter<const T, size_type> const_iterator;


    Array(size_type _size) : size(_size), pArray(new value_type[size]) {}
    ~Array() { delete[] pArray; };

    iterator begin() { return iterator(pArray); }
    iterator end() { return iterator(pArray, size); }

    const_iterator begin() const { return const_iterator(pArray); }
    const_iterator end() const { return const_iterator(pArray, size); }

    void Ispisi() {
        for (int i = 0; i < size; i++)
            cout << pArray[i] << " ";
        cout << endl;
    }

protected:
    size_type size;
    value_type *pArray;
};


int main() {
    Array<int> a(10);
    //NEINICIJALIZOVAN
    a.Ispisi();

    for (Array<int>::iterator it = a.begin(); it != a.end(); ++it)
        *it = 3;

    a.Ispisi();

    for (Array<int>::iterator it = a.begin(); it < a.end(); it += 2)
        *it = 4;

    Array<int>::iterator it1 = a.begin();
    it1 += 5;
    --it1;
    // Kako ovo ocekujes da radi bez jednog friend operatora ? :((((
    it1 = 2 + it1;

    Array<int>::iterator it2 = a.begin();

    cout << "it1 - it2 = " << it1 - it2 << endl;

    a.Ispisi();
}