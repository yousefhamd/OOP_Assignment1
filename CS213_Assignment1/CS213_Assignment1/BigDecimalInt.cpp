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
		if (digit == '-' || digit == '+') {
			sign = digit;
			continue;
		}
		temp += digit;
	}
	number = temp;
	return sign;
}



void BigDecimalInt::equalize_size(string& second) {
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



void BigDecimalInt::clear_zeros(string& number) {
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



BigDecimalInt BigDecimalInt::operator- (BigDecimalInt anotherDec)
{
	int result = 0;
	string res = "";
	string sign = "";
	BigDecimalInt result1;
	
	//case 1: the subtracted number is negative,while the other is positive 
	if ((anotherDec.big_decimal[0] != '-') && big_decimal[0] == '-')
	{
		char sign1 = big_decimal[0];
		
		attach_sign(big_decimal);
		attach_sign(anotherDec.big_decimal);
		
		equalize_size(anotherDec.big_decimal);

		sign += sign1;

		for (int i = anotherDec.big_decimal.length() - 1; i >= 0; i--)
		{
			result = int(anotherDec.big_decimal[i] - '0') + int(big_decimal[i] - '0') + result;    //adding the two integers 
			res = char((result%10) + '0') + res;  //returning result to a string
			result /= 10;
		}
		if (result == 1)
		{
			res = '1' + res;
		}

		return res;	
	}
	
	//case 2: second number is negative,while the other is positive 
	if ((big_decimal[0] != '-') && anotherDec.big_decimal[0] == '-')
	{
		char sign1 = big_decimal[0];

		attach_sign(big_decimal);
		attach_sign(anotherDec.big_decimal);

		equalize_size(anotherDec.big_decimal);
		
		for (int i = anotherDec.big_decimal.length() - 1; i >= 0; i--)
		{
			result = int(anotherDec.big_decimal[i] - '0') + int(big_decimal[i] - '0') + result;    //adding the two integers 
			res = char((result % 10) + '0') + res;  //returning result to a string
			result = result /10;
		}
		if (result == 1)
		{
			res = '1' + res;
		}

		if ( sign1 == '+')
		{
			return sign1 + res;
		}
		else
		{
			return sign + res;
		}
		
	}

	//case 3: numbers with positive signs
	if ((big_decimal[0] == '+') && (anotherDec.big_decimal[0] == '+'))
	{
		sign = '+';
		attach_sign(big_decimal);
		attach_sign(anotherDec.big_decimal);
	}


	if (big_decimal < anotherDec.big_decimal)
	{
		equalize_size(anotherDec.big_decimal);
		
		for (int i = anotherDec.big_decimal.length() - 1; i >= 0; i--)
		{
			//checking if the number needs to borrow from the next number 

			if (i == 0)  
			{
				//the first digit in the number is smaller than the other one
				if (anotherDec.big_decimal[0] < big_decimal[0])
				{
					result =  int(big_decimal[i] - '0') - int(anotherDec.big_decimal[i] - '0');   //subtracting the two integers 
					res = char(result + '0') + res;  //returning result to a string
					return '-' + res;
				}
			}

			int counter = 0;

			
			while ((anotherDec.big_decimal[i] < big_decimal[i] )&& i!=0)
			{
				//checking the occurance of zeros in the number
				if (anotherDec.big_decimal[i - 1] == '0')
				{
					counter += 1;
					i--;
					if (anotherDec.big_decimal[i - 1] != '0')
					{
						anotherDec.big_decimal[i - 1] -= 1;
					}
					continue;
				}
				
				if (counter != 0)
				{
					//replacing zeros with the bored number from the perivous digit
					for (int j = 0; j < counter; j++)
					{
						
						if (anotherDec.big_decimal[i] == '0')
						{
							anotherDec.big_decimal[i] = '9';
						}
						i++;
					}
					anotherDec.big_decimal[i] = anotherDec.big_decimal[i] + 10;

					break;
				}
				//borowing from the pervious digit 
				else
				{
					anotherDec.big_decimal[i] = anotherDec.big_decimal[i] + 10;
					anotherDec.big_decimal[i - 1] = anotherDec.big_decimal[i - 1] - 1;
				}

			}
			result = int(anotherDec.big_decimal[i] - '0') - int(big_decimal[i] - '0');   //subtracting the two integers 
			res = char(result + '0') + res;  //returning result to a string
		}
		sign = '-';

		return sign + res;
	}


	//calculating the numbers without signs 
	 else if((big_decimal > anotherDec.big_decimal) && (big_decimal[0] != ('+' || '-')) && (anotherDec.big_decimal[0] != ('+' || '-')))
	 {

		equalize_size(anotherDec.big_decimal);
		
		for (int i = anotherDec.big_decimal.length() - 1 ; i >= 0; i--)
		{
			//checking if the number needs to borrow from the next number 
			if (i == 0)
			{
				//the first digit in the number is smaller than the other one
				if (big_decimal[0] < anotherDec.big_decimal[0])
				{
					result = int(anotherDec.big_decimal[i] - '0') - int(big_decimal[i] - '0') ;   //subtracting the two integers 
					res = char(result + '0') + res;  //returning result to a string
					return '-' + res;
				}

			}

			int counter = 0;
	
			while ((big_decimal[i] < anotherDec.big_decimal[i] && i!=0))
			{
				//checking the occurance of zeros in the number
				if (big_decimal[i - 1] == '0')
				{
					counter += 1;
					i--;
					if (big_decimal[i - 1] != '0') 
					{
						big_decimal[i - 1] -= 1;
					}
					continue;
				}

				if (counter != 0)
				{
					//replacing zeros with the bored number from the perivous digit
					for (int j = 0; j < counter ; j++) 
					{
						if (big_decimal[i] == '0')
						{
							big_decimal[i] = '9';
						} 
						i++;
					}
					big_decimal[i] = big_decimal[i] + 10;

					break;
				}

				else
				{
					//borowing from the pervious digit 
					big_decimal[i] = big_decimal[i] + 10;
					big_decimal[i - 1] = big_decimal[i - 1] - 1;
				}
				
			}
			result = int(big_decimal[i]-'0') - int(anotherDec.big_decimal[i]-'0');   //subtracting the two integers 
			res = char(result + '0') + res;  //returning result to a string
		}
		return  sign + res;
     }
}


 bool  BigDecimalInt::operator< (BigDecimalInt anotherDec)
 {
	 string dec2 = anotherDec.get_big_decimal();

	 //checking the negative and the positive number return true if the right hand side is the positive side
	 if ((big_decimal[0] == '-') && (dec2[0] != '-'))
	 {
		 return true;
	 }
	 else if ((big_decimal[0] != '-') && (dec2[0] == '-'))
	 {
		 return false;
	 }

	 else
	 {
		 //checking the bigger number by its length and positivity 
		 if ((big_decimal.length() < dec2.length()) && (big_decimal[0] && dec2[0] != '-'))
		 {
			 return true;
		 }

		 //checking the bigger number by its length and negativity
		 else if ((big_decimal.length() < dec2.length()) && (big_decimal[0] && dec2[0] == '-'))
		 {
			 return false;
		 }

		 //checking the bigger number by its digits 
		 else if (big_decimal.length() == dec2.length())
		 {
			 if ((int(big_decimal[0] - '0') < int(dec2[0])) && ((big_decimal[0] && dec2[0] != '-')))
				return true;
			 if ((int(big_decimal[0] - '0') < int(dec2[0])) && ((big_decimal[0] && dec2[0] == '-')))
				return false;
		 }

		 else
		 {
			 return false;
		 }
	 }
 }
 


 BigDecimalInt BigDecimalInt::operator+ (BigDecimalInt anotherDec)
 {
	 //BigDecimalInt
	 string resultDec;
	 int res_digit = 0;

	 

	 //case 1: without a sign
	 if (big_decimal[0] && anotherDec.big_decimal[0] != ('+' || '-'))
	 {
		 equalize_size(anotherDec.big_decimal);
		 for (int i = big_decimal.length() - 1; i >= 0; i--)
		 {
			 res_digit = int(anotherDec.big_decimal[i] - '0') + int(big_decimal[i] - '0') + res_digit;
			 resultDec = char((res_digit % 10) + '0') + resultDec;
			 res_digit = res_digit / 10;
		 }
		 if (res_digit == 1)
		 {
			 resultDec = '1' + resultDec;
		 }
		 return resultDec;
	 }
		 //case 2:both positive or both negative
	 if (big_decimal[0] && anotherDec.big_decimal[0] == ('+' || '-'))
	 {
		
		 if (big_decimal[0] && anotherDec.big_decimal[0] == '+')
		 {
			 string sign1 = "+";
		 }

		 else if (big_decimal[0] && anotherDec.big_decimal[0] == '-')
		 {
			 string sign2 = "-";
		 }

		 attach_sign(big_decimal);
		 attach_sign(anotherDec.big_decimal);

		 equalize_size(anotherDec.big_decimal);

		for (int i = big_decimal.length() - 1; i > 0; i--)
		{
			res_digit = int(anotherDec.big_decimal[i] - '0') + int(big_decimal[i] - '0') + res_digit;
			resultDec = char((res_digit % 10) + '0') + resultDec;
			res_digit = res_digit / 10;
		}
		if (res_digit == 1)
		{
			resultDec = '1' + resultDec;
		}
			 
	 }
	 else
	 {
		 if (big_decimal < anotherDec.big_decimal)
		 {
			 char sign = anotherDec.big_decimal[0];

			 attach_sign(big_decimal);
			 attach_sign(anotherDec.big_decimal);

			 equalize_size(anotherDec.big_decimal);

			 for (int i = anotherDec.big_decimal.length() - 1; i >= 0; i--)
			 {
				 //checking if the number needs to borrow from the next number 
				 while (big_decimal[i] > anotherDec.big_decimal[i])
				 {
					 anotherDec.big_decimal[i] = anotherDec.big_decimal[i] + 10;
					 anotherDec.big_decimal[i - 1] = anotherDec.big_decimal[i - 1] - 1;
				 }
				 cout << big_decimal << " " << anotherDec.big_decimal << endl;
				 res_digit = int(anotherDec.big_decimal[i] - '0') - int(big_decimal[i] - '0');   //subtracting the two integers 
				 resultDec = char(res_digit + '0') + resultDec;  //returning result to a string
			 }
			 return sign + resultDec;
		 }
		 
		char sign = big_decimal[0];

		attach_sign(big_decimal);
		attach_sign(anotherDec.big_decimal);

		equalize_size(anotherDec.big_decimal);

		for (int i = anotherDec.big_decimal.length() - 1; i >= 0; i--)
		{
			//checking if the number needs to borrow from the next number 
		    while (big_decimal[i] < anotherDec.big_decimal[i])
		    {
				big_decimal[i - 1] -= 1;
				big_decimal[i] += 10;

		    }
			res_digit = int(big_decimal[i] - '0') - int(anotherDec.big_decimal[i] - '0');   //subtracting the two integers 
			resultDec = char(res_digit + '0') + resultDec;  //returning result to a string
		}
		return sign + resultDec ;
		
	 }
 }



 bool BigDecimalInt::operator> (BigDecimalInt anotherDec)
 {
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



 bool BigDecimalInt::operator== (BigDecimalInt anotherDec) {
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
	 big_decimal = sign_second + anotherDec.big_decimal;
	 return false;
 }



 BigDecimalInt BigDecimalInt::operator= (BigDecimalInt anotherDec) {
	 big_decimal = anotherDec.big_decimal;
	 return *this;
 }
