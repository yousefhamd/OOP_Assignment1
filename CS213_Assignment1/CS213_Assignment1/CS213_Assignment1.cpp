#include "BigDecimalInt.h"

int main()
{
	BigDecimalInt num1("100910000000");
	BigDecimalInt num2("00100091000000");
	cout << (num1 == num2) << endl;

	if (num2 < num1)
		cout << " true" << endl;
	else
		cout << " false" << endl;

	cout << " num2 - num1 = " << (num1 + num2) << endl;
	return 0;
}
