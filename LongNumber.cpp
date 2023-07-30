#include "LongNumber.h"
#include <iostream>
#include <vector>

using namespace std;

LongNumber::LongNumber(long num)
{
	if (num < 0) {
		cout << "Wrong number used";
		exit(0);
	} else {
		int x = num;
		while(x > 0)
		{
   			vect.push_back(x % 10);
   			x /= 10;
		}
		reverse(vect.begin(), vect.end());
	}
}

LongNumber::LongNumber(LongNumber& num)
{
	if (num.length() > 0) {
		for (int i = 0; i < num.length(); i++)
        	vect.push_back(num[i]);
	}
}

LongNumber::LongNumber(vector<short>& v)
{
	if (v.size() > 0) {
		for (int i = 0; i < v.size(); i++)
        	vect.push_back(v[i]);
	}
}

int LongNumber::length() const
{
	return vect.size();
}

short& LongNumber::operator[](int index)
{
	if (index >= length() || index < 0) {
		cout << "Index out of range";
		exit(0);
	} else
		return vect[index];
}

void LongNumber::append_right(short digit)
{
	if (digit >= 10 || digit < 0) {
		cout << "Not a digit";
		exit(0);
	} else
		vect.push_back(digit);
}

void LongNumber::append_left(short digit)
{
	if (digit >= 10 || digit < 0) {
		cout << "Not a digit";
		exit(0);
	} else
		vect.insert(vect.begin(), digit);
}

void LongNumber::pop_right()
{
	if (length() > 0)
		vect.pop_back();
	else {
		cout << "Nothing to pop";
		exit(0);
	}
}

void LongNumber::pop_left()
{
	if (length() > 0)
		vect.erase(vect.begin());
	else {
		cout << "Nothing to pop";
		exit(0);
	}

}

LongNumber LongNumber::operator+(short digit)
{
	LongNumber new_number(*this);
	int len = new_number.length();

	if (digit < 0 || digit >= 10) {
		cout << "Not a digit is being added";
		exit(0);
	}
	
	if (digit == 0)
		return new_number;

	if (len == 0) {
		new_number.append_right(digit);
		return new_number;
	} else {
		short transfer = 0;
		for (int i = 0; i < len; i++) {
			short d = digit;
            if (i == 0) 
				digit = 0;
            if (new_number[len - 1 - i] + d + transfer <= 9) {
                new_number[len - 1 - i] += d + transfer;
                transfer = 0;
                break;
			} else {
                new_number[len - 1 - i] = (new_number[len - 1 - i] + d + transfer) % 10;
                transfer = 1;
			}
		}

		if (transfer > 0)
            new_number.append_left(transfer);
        
		return new_number;
	}
}

LongNumber LongNumber::operator*(short digit)
{
	LongNumber new_number(*this);
	int len = new_number.length();

	if (len == 0)
		return new_number;

	if (digit < 0 || digit > 10) {
		cout << "Wrong multiplier";
		exit(0);
	}

	if (digit == 0)
		return LongNumber(0);
	
	if (digit == 10) {
		new_number.append_right(0);
		return new_number;
	}

	short transfer = 0;
	for (int i = 0; i < len; i++) {
		int prod = new_number[len - 1 - i] * digit + transfer;
        new_number[len - 1 - i] = prod % 10;
        transfer = prod / 10;
	}

	if (transfer > 0)
        new_number.append_left(transfer);
        
	return new_number;
}

LongNumber LongNumber::operator-(LongNumber& num)
{
	LongNumber new_number(*this);
	int len = new_number.length();
	int num_len = num.length();

	if (len == 0 || num_len == 0)
		return new_number;
	
	short transfer = 0;
	int diff;
	for (int i = 0; i < num_len; i++) {
		diff = new_number[len - 1 - i] + transfer - num[num_len - 1 - i];
        if (diff >= 0) {
            new_number[len - 1 - i] = diff;
            transfer = 0;
		} else {
            new_number[len - 1 - i] = diff + 10;
            transfer = -1;
		}
	}

	int j{num_len};
	while (transfer < 0 && j < len) {
        diff = new_number[len - 1 - j] + transfer;
        if (diff >= 0) {
            new_number[len - 1 - j] = diff;
            transfer = 0;
		} else {
            new_number[len - 1 - j] = diff + 10;
            transfer = -1;
		}
        j += 1;
	}
        
    while (new_number.length() > 0 && new_number[0] == 0)
		new_number.pop_left();
            
    return new_number;

}

bool LongNumber::operator<=(LongNumber& num)
{	
	int num_len = num.length();

	if (length() < num_len)
		return true;
	
	if (length() > num_len)
		return false;
	
	for (int i = 0; i < num_len; i++) {
		if (vect[i] < num[i])
            return true;
        else if (vect[i] > num[i])
            return false;
        else
        	continue;
	}

	return true;
}

ostream& operator<<(ostream& os, LongNumber& num)
{
    if (num.length() == 0)
		os << 0;
	else {
		for (auto element : num.vect)
        	os << element;
	}
    
    return os;
}