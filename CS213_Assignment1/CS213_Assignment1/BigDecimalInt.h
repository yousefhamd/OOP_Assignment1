#pragma once
#pragma once
#include <iostream>
#include <regex>
#include<string>
#include<cstring>

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

	string get_big_decimal() 
	{
		return big_decimal;
	}

	friend ostream& operator << (ostream& out, BigDecimalInt b);

	int size();

	int sign();

	BigDecimalInt operator- (BigDecimalInt anotherDec);

	BigDecimalInt operator+ (BigDecimalInt anotherDec);

	bool operator< (BigDecimalInt anotherDec);

	bool operator== (BigDecimalInt anotherDec);

	bool operator> (BigDecimalInt anotherDec);

	BigDecimalInt operator= (BigDecimalInt anotherDec);

	
};
