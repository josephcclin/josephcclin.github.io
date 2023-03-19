#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <math.h>

int main()
{
        long double x, n, result;

        cout << "\nCalculate x^(1/n);";
        cout << "\nEnter x: ";
        cin >> x;
        cout << "Enter n: ";
        cin >> n;
        result = exp(log(x)/n);
        cout << "\nResult = " << result;
        cout << "\nPress any key to escape.";
        getchar();
        getchar();
        system("cls");
        return 0;
}
