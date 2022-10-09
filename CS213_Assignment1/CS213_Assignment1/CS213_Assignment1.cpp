#include "BigDecimalInt.h"

int main()
{
	BigDecimalInt first("+123456789090090");
	BigDecimalInt second("-123456789003957634786928");
	string s = second.get_big_decimal();
	first.attach_sign();
	first.equalize_size(s);
	cout << first;
	return 0;
}
