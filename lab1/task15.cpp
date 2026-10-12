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
		cout << "error: x must be more than -1 and less than 1\n";
		return 0;
	}

	cout << "\nInput k (k > 1) = ";
	int k;
	cin >> k;

	if (k <= 1)
	{
		cout << "error: k must be more than 1";
	}

	epsilon = 1.0;

	for (int i = 0; i < k; ++i)
	{
		epsilon *= 0.1;
	}

	cout << "epsilon = " << epsilon << '\n';

	term = x;
	sum = 0.0;
	n = 3;

	while (fabs(term) >= epsilon)
	{
		sum += term;
		term = (term * x * x * (n - 2)) / n;
		n += 2;
	}

	cout.precision(k);

	cout << "arth x = " << std::atanh(x) << '\n';
	cout << "1/2 * ln((1+x)/(1-x)) = " << 0.5 * std::log((1+x) / (1-x)) << '\n';
	cout << "sum = " << sum << '\n';

	return 0;
}