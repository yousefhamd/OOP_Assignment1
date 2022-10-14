#include "BigDecimalInt.h"

int main()
{
	BigDecimalInt num1("123456789012345678901234567890");
	BigDecimalInt num2("-113456789011345678901134567890");
	cout << (num1 == num2);
	num1 = num2;
	cout << num1;
	return 0;
}
