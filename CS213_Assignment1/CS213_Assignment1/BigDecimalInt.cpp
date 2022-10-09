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

char BigDecimalInt :: attach_sign() {
	string temp = "";
	char sign = ' ';
	for (char digit : big_decimal) { // delete the sign from the number
		if (digit == '-' || digit == '+') {
			sign = digit;
			continue;
		}
		temp += digit;
	}
	big_decimal = "";
	for (char digit : temp) { // refill the number
		big_decimal += digit;
	}
	return sign;
}

void BigDecimalInt :: equalize_size(string& second) {
	int n_first_zeros = 0, n_second_zeros = 0;
	if (big_decimal[0] == '+' || big_decimal[1] == '-') {
		n_first_zeros--;
		n_second_zeros++;
	}
	if (second[0] == '+' || second[0] == '-') {
		n_second_zeros--;
		n_first_zeros++;
	}
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

ostream& operator << (ostream& out, BigDecimalInt b) {
	out << b.big_decimal;
	return out;
}