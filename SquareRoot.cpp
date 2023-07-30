#include "LongNumber.h"
#include <iostream>
#include <string>
#include <chrono>
#include <limits>

using namespace std;

// Below is an implementation of the so-called 'digit by digit' algorithm to compute the square root
// of any positive integer. This is not the fastest algorithm to do that, but its main advantage is 
// simlicity. Also, every digit found in the square root decimal expansion is correct and it's not going
// to change afterwards. The algorithm terminates if the square root in question has a finite decimal
// expansion.
// The algorithm is described in detail here: 
// https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation

void DigitByDigitSqRt(int num, int precision = 0)
{
	if (num == 0) {
		cout << 0 << endl;
		return;
	}

	string num_str = to_string(num);
	
	int digits_processed, c_int;

	if (num_str.length() % 2) {
    	digits_processed = 1;
		c_int = int(num_str[0]) - 48;
	} else {
		digits_processed = 2;
		c_int = (int(num_str[0]) - 48)*10 + (int(num_str[1]) - 48);
	}

    LongNumber c(c_int);
    LongNumber p(0);
    
    bool dot = false;

	int max_step;
	if (precision == 0)
		max_step = numeric_limits<int>::max();
	else
		max_step = precision;
    
	int step {0};

    while (step <= max_step) {
        int left {0};
        int right {9};
        int x {0};

        while (left <= right) {
            int mid = (right + left) / 2;
            if (((p*2)*10 + mid)*mid <= c) {
                left = mid + 1;
                x = mid;
			} else
                right = mid - 1;
		}

        LongNumber y(((p*2)*10 + x)*x);

        p = p*10 + x;
        c = c - y;
        
        if (c.length() == 0 && digits_processed == num_str.length()) {
            cout << x << endl;
            return;
		}
        else if (c.length() == 0 && digits_processed < num_str.length()) {
            cout << x;

            if (num_str[digits_processed] != '0')
				c = LongNumber((int(num_str[digits_processed]) - 48)*10 + (int(num_str[digits_processed + 1]) - 48));
            else
                c = LongNumber((int(num_str[digits_processed + 1]) - 48));
            
			digits_processed += 2;
		} else if (c.length() > 0 && digits_processed < num_str.length()) {
        	cout << x;
            c = (c*10) + (int(num_str[digits_processed]) - 48);
            c = (c*10) + (int(num_str[digits_processed + 1]) - 48);
            digits_processed += 2;
		} else if (c.length() > 0 && digits_processed == num_str.length()) {
			cout << x;

            if (dot == false) {
				cout << ".";
                dot  = true;
			}

            c = (c*10)*10;
            step += 1;
		}
	}

	cout << endl;
    return;
}

int main() 
{	
	int n;
	int precision;

	cout << "Enter a non-negative integer: ";
	cin >> n;
	cout << "Enter precision: ";
	cin >> precision;
	cout << "The square root of " << n << " with up to " << precision << " digits after the decimal point is: " << endl;

	auto start = chrono::high_resolution_clock::now();
	DigitByDigitSqRt(n, precision);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
 
	cout << "Duration: " << duration.count() << " microseconds" << endl;
}