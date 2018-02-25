#include <iostream>
#include <sstream>
#include <cmath>

#ifndef NULL
#define NULL 0
#endif

using namespace std;


int convertToDecimal(string& s_input, const int i_base)
{
	int l_result  = 0, 
		i_counter = 0,
		i_length  = s_input.length(); 
		  
	if(i_length > 0)
	{
		char* cp_input  = &s_input[i_length-1]; // empty string treated as 0
		
		for(int i = i_length - 1; i >= 0; i--)
		{
			int i_temp = static_cast<int>(*cp_input - 48); // convert numeric digit
			
			if(i_temp > 9) // convert alphabetic number
			{
				i_temp = static_cast<int>(*cp_input - 87); // a = 10
			} // end if
			if(i_temp < 0 || i_temp > 36) // ensure valid input received
			{
				throw new invalid_argument("Received something that isn't a number.");
			} // end if
			
			l_result += static_cast<int>(i_temp * pow(i_base, i_counter++));
			cp_input--;
		} // end for
	} // end if
	return l_result;
} // end method convertToDecimal