#include <iostream>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;

int main()
{
	double epsilon;
	double term;
	double sum;
	double x;
	int n;
	cout << "input x = ";
	cin >> x;
	
	if (x <= -1 || x >= 1)
	{
		cout << "error: x must be more than -1 and less than 1";
		return 0;
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

	term = 1.0;
	sum = 0.0;
	n = 1;
	while (fabs(term) >= epsilon)
	{
		sum += term;
		term = (-term * x * n) / (n+1);
		n += 2;
	}

	cout.precision(k);

	cout << "1 / sqrt(1+x) = " << 1.0 / std::sqrt(1+x) << "\nS = " << sum;

	return 0;
}