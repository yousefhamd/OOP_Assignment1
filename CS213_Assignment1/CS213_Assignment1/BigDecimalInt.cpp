#include "BigDecimalInt.h"

BigDecimalInt :: BigDecimalInt() {
	big_decimal = "";
}

BigDecimalInt :: BigDecimalInt(string b_d) {
	regex r("[+-]*[0-9]+");
	if (regex_match(b_d, r)) {
		big_decimal = b_d;
	}
	else
		cout << "Invalid decimal number" << endl;
}

ostream& operator << (ostream& out, BigDecimalInt b) {
	out << b.big_decimal;
	return out;
}