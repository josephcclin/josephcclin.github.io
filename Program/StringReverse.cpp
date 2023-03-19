#include <iostream.h>
#include <string.h>
#include <conio.h>

const int MAX = 80;
int main()
{
	char string[1000];
	char* str = NULL;
	cout << "\nPlease input the string you want to reverse: ";
	cin.get(string, MAX);
	str = string;
	cout << str << endl;
	int l = strlen(str);
	for(int i=l; i>=0; i--)
	{
		cout << *(str+i);
	}
	cout << endl;
	getche();
	return 0;
}
