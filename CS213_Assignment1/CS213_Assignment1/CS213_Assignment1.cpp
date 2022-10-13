#include "BigDecimalInt.h"

int main()
{
	BigDecimalInt first("+123456789090090");
	BigDecimalInt second("123456789003957634786928");
	if(first > second)
		cout << first.sign() << endl;
	cout << first;
	cout << first.size();
	return 0;
}
