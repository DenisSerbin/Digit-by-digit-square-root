#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// LongNumber represents an integer as a vector of digits. Essentially, the LongNumber class is a wrapper
// for vector<short> with overloaded access [] and append/pop on both sides, plus operations on integers 
// (+, *, -, <=) implemented only to the extent needed by the algorithm. For example, the algorithm only
// requres multiplication and addition of a long integer by an integer between 0 and 10. Similary, subtraction 
// "n - m" is defined for the case when n is greater or equal to m.

class LongNumber
{
	vector<short> vect;

public:

	LongNumber(long num);

	LongNumber(LongNumber& num);

	LongNumber(vector<short>& v);

	int length() const;

	short& operator[](int index);

	void append_right(short digit);

	void append_left(short digit);

	void pop_right();

	void pop_left();

	LongNumber operator+(short digit);

	LongNumber operator*(short digit);

	LongNumber operator-(LongNumber& num);

	bool operator<=(LongNumber& num);

	friend ostream& operator<<(ostream& os, LongNumber& num);
};

ostream& operator<<(ostream& os, LongNumber& num);