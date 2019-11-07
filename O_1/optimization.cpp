#include <iostream>
#include <cmath>

const double goldenRatio = 0.618;
const double accuracy = 0.00001;
const double lowerBound = -1;
const double upperBound = 1;

using namespace std;

// f(x) = arctg(sin(2x+1))
double f(double x)
{
	return atan(sin(2 * x + 1));
}

// Takes lower bound, upper bound and inner point
double calculateExtremum(double a, double b, double x1, bool isMinimum)
{
	if ((b - a) < accuracy)	// End of searching
		return f((a + b) / 2);

	double x2;	// Establish points x1 and x2
	if (x1 > (a + b) / 2)	// x1 is actually x2
	{
		x2 = x1;
		x1 = b - (b - a) * goldenRatio;	// Calculate x1 based on the length of the interval
	}
	else
		x2 = a + (b - a) * goldenRatio; // Calculate x2 based on the length of the interval

	if (isMinimum)
	{
		if (f(x1) >= f(x2))
			return calculateExtremum(x1, b, x2, true);		// New interval is <x1, b> with x2 as inner point
		else
			return calculateExtremum(a, x2, x1, true);		// New interval is <a, x2> with x1 as inner point
	}
	else
	{
		if (f(x1) <= f(x2))
			return calculateExtremum(x1, b, x2, false);		// New interval is <x1, b> with x2 as inner point
		else
			return calculateExtremum(a, x2, x1, false);		// New interval is <a, x2> with x1 as inner point
	}

	return 0;
}

int main()
{
	double potentialMinimum = calculateExtremum(lowerBound, upperBound, upperBound - ((upperBound - lowerBound) * goldenRatio), true);
	if (potentialMinimum < f(lowerBound) && potentialMinimum < f(upperBound))		// Check if is smaller than values on the boundaries
		cout << "Minimum: " << potentialMinimum << endl;
	else
	{
		double maximum = calculateExtremum(lowerBound, upperBound, upperBound - ((upperBound - lowerBound) * goldenRatio), false);
		cout << "Maximum: " << maximum << endl;
	}

	system("pause");
	return 0;
}