#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;

int main() 
{
	double epsilon;
	double term;
	double sum = 0;
	double x;
	int n;
	cout << "input x = ";
	cin >> x;

	while (x >= 2 * M_PI || x <= -2 * M_PI) 
	{
		if (x < 0) 
		{
			x = x + 2*M_PI;
		}
		else 
		{
			x = x - 2*M_PI;
		}
	}
	cout << "\nInput k (k > 1) = ";
	int k;
	cin >> k;

	if (k <= 1)
	{
		cout << "error: k must be more than 1";
		return 0;
	}

	epsilon = 1.0;

	for (int i = 1; i <= k; ++i)
	{
		epsilon *= 0.1;
	}
	
	cout << "epsilon = " << epsilon << '\n';

	term = x;
	n = 1;
	while (fabs(term) >= epsilon)
	{
		sum += term;
		term = (-term * x * x) / (2 * n * (2*n + 1));
		++n;
	}

	cout.precision(k);

	cout << "sin(x) = " << std::sin(x) << "\nS = " << sum;

	return 0;
}