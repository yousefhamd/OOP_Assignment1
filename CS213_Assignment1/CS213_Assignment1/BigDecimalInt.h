#pragma once
#include <iostream>
#include <regex>
using namespace std;
class BigDecimalInt
{
	string big_decimal;

	char attach_sign(string& number);

	void equalize_size(string& second);

	void clear_zeros(string& number);
public:
	BigDecimalInt();

	BigDecimalInt(string b_d);

	string get_big_decimal();

	friend ostream& operator << (ostream& out, BigDecimalInt b);

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

	bool operator> (BigDecimalInt anotherDec) {
		char sign_first = attach_sign(big_decimal);
		char sign_second = attach_sign(anotherDec.big_decimal);
		equalize_size(anotherDec.big_decimal);
		if ((sign_first == '+' || sign_first == ' ') && sign_second == '-') {
			goto rebuild_yes;
		}
		else if (sign_first == '-' && (sign_second == '+' || sign_second == ' ')) {
			goto rebuild_no;
		}
		else if ((sign_first == '+' || sign_first == ' ') && (sign_second == '+' || sign_second == ' '))
		{
			for (int i = 0; i < anotherDec.big_decimal.length(); i++)
			{
				if (big_decimal[i] > anotherDec.big_decimal[i]) {
					goto rebuild_yes;
				}
				else if (big_decimal[i] < anotherDec.big_decimal[i]) {
					goto rebuild_no;
				}
			}
		}
		else if (sign_first == '-' && sign_second == '-')
		{
			for (int i = 0; i < anotherDec.big_decimal.length(); i++)
			{
				if (big_decimal[i] < anotherDec.big_decimal[i]) {
					goto rebuild_yes;
				}
				else if (big_decimal[i] > anotherDec.big_decimal[i]) {
					goto rebuild_no;
				}
			}
		}
		return false;
	rebuild_yes:
		clear_zeros(big_decimal);
		clear_zeros(anotherDec.big_decimal);
		big_decimal = sign_first + big_decimal;
		anotherDec.big_decimal = sign_second + anotherDec.big_decimal;
		return true;
	rebuild_no:
		clear_zeros(big_decimal);
		clear_zeros(anotherDec.big_decimal);
		big_decimal = sign_first + big_decimal;
		anotherDec.big_decimal = sign_second + anotherDec.big_decimal;
		return false;
	}

	bool operator== (BigDecimalInt anotherDec) {
		char sign_first = attach_sign(big_decimal);
		char sign_second = attach_sign(anotherDec.big_decimal);
		if (((sign_first == ' ' || sign_first == '+') && sign_second == '-') || (sign_first == '-' && (sign_second == ' ' || sign_second == '+')))
			goto no;
		else {
			if (big_decimal == anotherDec.big_decimal)
				goto yes;
			else
				goto no;
		}
	yes:
		clear_zeros(big_decimal);
		clear_zeros(anotherDec.big_decimal);
		big_decimal = sign_first + big_decimal;
		anotherDec.big_decimal = sign_second + anotherDec.big_decimal;
		return true;
	no:
		clear_zeros(big_decimal);
		clear_zeros(anotherDec.big_decimal);
		big_decimal = sign_first + big_decimal;
		anotherDec.big_decimal = sign_second + anotherDec.big_decimal;
		return false;
	}

	BigDecimalInt operator= (BigDecimalInt anotherDec) {
		big_decimal = anotherDec.big_decimal;
		return *this;
	}

	int size();

	int sign();
};