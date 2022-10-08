#pragma once
#include <iostream>
#include <regex>
using namespace std;
class BigDecimalInt
{
	string big_decimal;
public:
	BigDecimalInt();

	BigDecimalInt(string b_d);

	friend ostream& operator << (ostream& out, BigDecimalInt b);

	void equalize_size(string& first, string& second) {
		string s;
		if (first.length() > second.length()) {
			s = string('0', first.length() - second.length());
			second = s + second;
		}
		else
		{
			s = string('0', second.length() - first.length());
			first = s + first;
		}
	}

	BigDecimalInt operator+ (BigDecimalInt anotherDec) {
		BigDecimalInt resultDec;
		int res_digit = 0;
		for (int i = big_decimal.length() - 1; i >= 0; i--) {
			res_digit = int(anotherDec.big_decimal[i] - '0') + int(big_decimal[i] - '0');
			if (int(anotherDec.big_decimal[i] - '0') + int(big_decimal[i] - '0') >= 10)
				resultDec.big_decimal += to_string(int(anotherDec.big_decimal[i] - '0') + int(big_decimal[i] - '0'));
		}
		return resultDec;
	}
};

