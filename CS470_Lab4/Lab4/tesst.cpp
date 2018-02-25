#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <random>
#include <time.h>
#include "baseToDecimal.h"


#ifndef NULL
#define NULL 0
#endif

using namespace std;


int getBase(void)
{
	// lower bound: (9k % 9) + 2 = 0 + 2 = 2
	// upper bound: ((9k + 8) % 9) + 2 = 8 + 2 = 10
	return (rand() % 9) + 2;
}

int generateNumberInBase(const int i_base)
{
	int i_length = 0; // length of number
	
	switch(i_base)
	{
		case 2:
			i_length = 17;
			break;
		case 3:
			i_length = 11;
			break;
		case 4:
			i_length = 9;
			break;
		case 5:
			i_length = 8;
			break;
		case 6:
			i_length = 7;
			break;
		case 7:
		case 8:
		case 9:
			i_length = 6;
			break;
		case 10:
			i_length = 5;
			break;
	} // end switch
	
	int current_number = 0;
	
	while(true)
	{
		stringstream number;
			
		// pick a number between 1 and base as leading digit
		number << ((rand()%(i_base-1)) + 1);
		
		for(int i = 1; i < i_length; i++)
		{
			int temp = rand() % i_base;
			number << temp;
		} // end for
		
		string num = number.str();
		cout << "[Server]: picked number " << num << " (" << i_base << ")" << endl;
		current_number = convertToDecimal(num, i_base);
		if(i_base != 10)
			cout << "[Server]: converted to base 10: " << current_number << endl;
			
		if(current_number < 100000)
		{
			break;
		}
		else
		{
			cout << "[Server]: number too large, picking new number ..." << endl;
		}
	}
	return current_number;
} // end method generateNumberInBase

int main()
{
	srand((unsigned)(time(NULL)));
	for(int i = 0; i < 100000; i++)
	{
		cout << i+1 << "th number:" << endl;
		int k = generateNumberInBase(getBase());
		if(k >= 100000)
			break;
	}
}