#include "BigDecimalInt.h"

BigDecimalInt::BigDecimalInt() {
	big_decimal = "";
}



BigDecimalInt::BigDecimalInt(string b_d) {
	regex r("[+-]*[0-9]+"); // regular exepression for validate the number 
	if (regex_match(b_d, r)) {
		big_decimal = b_d;
	}
	else
		cout << "Invalid decimal number" << endl;
}



char BigDecimalInt::attach_sign(string& number) {
	string temp = "";
	char sign = ' ';
	for (char digit : number) { // delete the sign from the number
		if (digit == '-' || digit == '+' || digit == ' ') {
			sign = digit;
			continue;
		}
		temp += digit;
	}
	number = temp;
	return sign;
}



void BigDecimalInt::equalize_size(string& second) {
	int n_zeroz = 0;
	if (big_decimal.length() > second.length()) {
		n_zeroz = big_decimal.length() - second.length();
		second = string(n_zeroz, '0') + second;
	}
	else if (big_decimal.length() < second.length())
	{
		n_zeroz = second.length() - big_decimal.length();
		big_decimal = string(n_zeroz, '0') + big_decimal;
	}
}



void BigDecimalInt::clear_zeros(string& number) {
	string temp = "";
	for (int i = 0; i <= number.length(); i++) {
		if (number[i] == '0' && temp.length() == 0)
			continue;
		temp += number[i];
	}
	number = temp;
}

string BigDecimalInt::addition(string anotherNumber) {
	int result = 0;
	string res = "";
	for (int i = anotherNumber.length() - 1; i >= 0; i--)
	{
		result = int(anotherNumber[i] - '0') + int(big_decimal[i] - '0') + result;    //adding the two integers 
		res = char((result % 10) + '0') + res;  //returning result to a string
		result /= 10;
	}
	if (result == 1)
	{
		res = '1' + res;
	}
	return res;
}

string BigDecimalInt::subtraction(string firstNumber, string anotherNumber) {
	int result = 0;
	string res = "", temp = firstNumber;
	int counter = 0;
	for (int i = anotherNumber.length() - 1; i >= 0; i--)
	{
		counter = i;
		while (anotherNumber[counter] > temp[counter])
		{
			temp[counter] = temp[counter] + 10;
			temp[counter - 1]--;
			counter--;
		}
		result = int(temp[i] - '0') - int(anotherNumber[i] - '0');   //subtracting the two integers 
		res = char(result + '0') + res;  //returning result to a string
	}
	return res;
}


int BigDecimalInt::size() {
	if (big_decimal[0] == '+' || big_decimal[0] == '-')
		return big_decimal.length() - 1;
	else
		return big_decimal.length();
}



int BigDecimalInt::sign() {
	return (big_decimal[0] == '+' || big_decimal[0] == ' ') ? 1 : 0;
}



ostream& operator << (ostream& out, BigDecimalInt b) {
	char sign = b.attach_sign(b.big_decimal);
	b.clear_zeros(b.big_decimal);
	b.big_decimal = sign + b.big_decimal;
	out << b.big_decimal;
	return out;
}



BigDecimalInt BigDecimalInt::operator- (BigDecimalInt anotherDec)
{
	char sign1 = attach_sign(big_decimal);
	char sign2 = attach_sign(anotherDec.big_decimal);
	equalize_size(anotherDec.big_decimal);

	BigDecimalInt result;

	//case 1: the subtracted number is negative,while the other is positive 
	if (sign2 != '-' && sign1 == '-')
	{
		result = BigDecimalInt('-' + addition(anotherDec.big_decimal));
	}

	//case 2: the subtracted number is positive,while the other is negative 
	if (sign2 == '-' && sign1 != '-')
	{
		result = BigDecimalInt('+' + addition(anotherDec.big_decimal));
	}

	//case 3: two numbers are ngative
	if (sign1 == '-' && sign2 == '-')
	{
		if (big_decimal > anotherDec.big_decimal)
			result = BigDecimalInt('-' + subtraction(big_decimal, anotherDec.big_decimal));
		else if (big_decimal < anotherDec.big_decimal)
			result = BigDecimalInt('+' + subtraction(anotherDec.big_decimal, big_decimal));
		else
			result = BigDecimalInt("0");
	}

	//case 3: numbers with positive signs
	if (sign1 != '-' && sign2 != '-')
	{
		if (big_decimal > anotherDec.big_decimal)
			result = BigDecimalInt('+' + subtraction(big_decimal, anotherDec.big_decimal));
		else if (big_decimal < anotherDec.big_decimal)
			result = BigDecimalInt('-' + subtraction(anotherDec.big_decimal, big_decimal));
		else
			result = BigDecimalInt("0");
	}

	sign2 = attach_sign(result.big_decimal);
	clear_zeros(result.big_decimal);
	big_decimal = sign1 + big_decimal;
	result.big_decimal = sign2 + result.big_decimal;
	return result;
}

BigDecimalInt BigDecimalInt::operator+ (BigDecimalInt anotherDec)
{
	char sign1 = attach_sign(big_decimal);
	char sign2 = attach_sign(anotherDec.big_decimal);
	equalize_size(anotherDec.big_decimal);

	BigDecimalInt result;

	//positive numbers only
	if (sign1 != '-' && sign2 != '-')
	{
		string res = addition(anotherDec.big_decimal);
		result = BigDecimalInt('+' + res);
	}

	//negative numbers only
	if (sign1 == '-' && sign2 == '-')
	{
		result = BigDecimalInt('-' + addition(anotherDec.big_decimal));
	}

	if (sign1 != '-' && sign2 == '-') {
		if (big_decimal > anotherDec.big_decimal)
			result = BigDecimalInt('+' + subtraction(big_decimal, anotherDec.big_decimal));
		else if (big_decimal < anotherDec.big_decimal)
			result = BigDecimalInt('-' + subtraction(anotherDec.big_decimal, big_decimal));
		else
			result = BigDecimalInt("0");
	}

	if (sign1 == '-' && sign2 != '-') {
		if (big_decimal > anotherDec.big_decimal)
			result = BigDecimalInt('-' + subtraction(big_decimal, anotherDec.big_decimal));
		else if (big_decimal < anotherDec.big_decimal)
			result = BigDecimalInt('+' + subtraction(anotherDec.big_decimal, big_decimal));
		else
			result = BigDecimalInt("0");
	}

	sign2 = attach_sign(result.big_decimal);
	clear_zeros(result.big_decimal);
	big_decimal = sign1 + big_decimal;
	result.big_decimal = sign2 + result.big_decimal;
	return result;
}

bool  BigDecimalInt::operator< (BigDecimalInt anotherDec)
{
	//checking the negative and the positive number return true if the right hand side is the positive side
	equalize_size(anotherDec.big_decimal);

	if ((big_decimal[0] == '-') && (anotherDec.big_decimal[0] != '-'))
	{
		return true;
	}

	else if ((big_decimal[0] != '-') && (anotherDec.big_decimal[0] == '-'))
	{
		return false;
	}

	//checking the bigger number by its digits 
	else if (big_decimal.length() == anotherDec.big_decimal.length())
	{
		for (int i = 0; i < big_decimal.length(); i++) {
			if ((int(big_decimal[i] - '0') < int(anotherDec.big_decimal[i])) && ((big_decimal[i] && anotherDec.big_decimal[i]) != '-'))
			{
				return true;
			}

			else if ((int(big_decimal[i] - '0') < int(anotherDec.big_decimal[i])) && ((big_decimal[i] && anotherDec.big_decimal[i]) == '-'))
			{
				return false;
			}
		}
	}

	else
	{
		return false;
	}

}


bool BigDecimalInt::operator> (BigDecimalInt anotherDec)
{
	char sign_first = attach_sign(big_decimal);
	char sign_second = attach_sign(anotherDec.big_decimal);
	equalize_size(anotherDec.big_decimal);

	if (sign_first != '-' && sign_second == '-') {
		goto rebuild_yes;
	}
	else if (sign_first == '-' && sign_second != '-') {
		goto rebuild_no;
	}
	else if (sign_first != '-' && sign_second != '-')
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
	big_decimal = sign_first + big_decimal;
	return true;
rebuild_no:
	big_decimal = sign_first + big_decimal;
	return false;
}



bool BigDecimalInt::operator== (BigDecimalInt anotherDec) {
	char sign_first = attach_sign(big_decimal);
	char sign_second = attach_sign(anotherDec.big_decimal);
	if ((sign_first != '-' && sign_second == '-') || (sign_first == '-' && sign_second != '-'))
		goto no;
	else {
		if (big_decimal == anotherDec.big_decimal)
			goto yes;
		else
			goto no;
	}
yes:
	big_decimal = sign_first + big_decimal;
	return true;
no:
	big_decimal = sign_first + big_decimal;
	return false;
}



BigDecimalInt BigDecimalInt::operator= (BigDecimalInt anotherDec) {
	big_decimal = anotherDec.big_decimal;
	return *this;
}
