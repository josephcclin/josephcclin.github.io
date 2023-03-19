// =====================================================
// Computational Verification of the 3n+1 conjecture 
// Author: Joseph, Chuang-Chieh Lin 						
// Date: January 25, 2008										
// =====================================================

#include <iostream.h>

typedef unsigned long huge;
huge calculate(unsigned long number);

int main()
{
	huge range, max=1, temp;
	cout << "Input range = ";
	cin >> range;
	for (int i=1; i<=range; i++) {	
		temp = calculate(i);
		if (temp > max) max = temp;
	}
	cout << "Max = " << max << endl;	
	return 0;
}

huge calculate(huge n)
{
	huge max = n;
	//cout << n << " -> ";
	while (n != 1) {
		if ((n % 2) == 1) {
			n = 3*n+1;
			if (n > max) { max = n; }
			//cout << n << " -> ";
		}
		else n = n/2;
		//cout << n << " -> ";
	}
	//cout << "Halt! \nMax = " << max << endl;
	return max;
}
