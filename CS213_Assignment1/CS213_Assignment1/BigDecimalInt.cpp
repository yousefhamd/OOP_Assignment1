#include "BigDecimalInt.h"

BigDecimalInt :: BigDecimalInt() {
	big_decimal = "";
}

BigDecimalInt :: BigDecimalInt(string b_d) {
	regex r("[+-]*[0-9]+"); // regular exepression for validate the number 
	if (regex_match(b_d, r)) {
		big_decimal = b_d;
	}
	else
		cout << "Invalid decimal number" << endl;
}

string BigDecimalInt :: get_big_decimal() {
	return big_decimal;
}

char BigDecimalInt :: attach_sign(string& number) {
	string temp = "";
	char sign = ' ';
	for (char digit : number) { // delete the sign from the number
		if (digit == '-' || digit == '+') {
			sign = digit;
			continue;
		}
		temp += digit;
	}
	number = temp;
	return sign;
}

void BigDecimalInt :: equalize_size(string& second) {
	int n_first_zeros = 0, n_second_zeros = 0;

	if (big_decimal.length() > second.length()) {
		n_first_zeros += big_decimal.length() - second.length();
		second = string(n_first_zeros, '0') + second;
	}
	else if (big_decimal.length() < second.length())
	{
		n_second_zeros += second.length() - big_decimal.length();
		big_decimal = string(n_second_zeros, '0') + big_decimal;
	}
}

void BigDecimalInt :: clear_zeros(string& number) {
	string temp = "";
	for (int i = 0; i <= number.length(); i++) {
		if (number[i] == '0' && temp.length() == 0)
			continue;
		temp += number[i];
	}
	number = temp;
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
	out << b.big_decimal;
	return out;
}