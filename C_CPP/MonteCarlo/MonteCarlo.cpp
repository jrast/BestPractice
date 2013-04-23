//============================================================================
// Name        : MonteCarlo.cpp
// Author      : Jürg Rast
// Description : MonteCarlo Demo
//============================================================================

#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;


// integrates the function f within [lb,hb] using the Monte Carlo method, stops as soon as change <= epsilon
double monteCarlo(double (*f)(double x), // ptr to function to integrate
		double lb, // lower bound
		double hb, // higher bound
		double height, // must be higher than max of f(x) within [lb,hb]
		double epsilon = 1e-5, // minimal change
		unsigned long minIterations = 10000); // minimal number of iterations

// function to integrate
double f(double x);

int main() {
	srand(time(0));
	cout << setprecision(10) << "Berechnung von PI mit Monte-Carlo " << endl;
	cout << "---- Pi ----" << endl;
	double piEstimate = 4.0 * monteCarlo(f, 0.0, 1.0, 1.0, 1e-8);
	cout << "Accurate Pi:  " << M_PI << endl;
	cout << "Estimated Pi: " << piEstimate << endl;
	return 0;
}


double monteCarlo(double (*f)(double x), double lb, double hb, double height, double epsilon, unsigned long minIterations) {
	unsigned long points = 0, pointsInside = 0; // Counters for total points and points inside area
	double area[2] = {(hb -lb)* height, -(hb-lb)*height}; // Array for the current area and the last area
	do {
		// Generate Random y, compare with f(random(x)) and decide if point inside or outside area
		if(((double)rand() / RAND_MAX * height) <= f((double)rand() / RAND_MAX * (hb - lb) + lb) ) pointsInside++;
		// Assign new area, increase total points, compare last and new area, leave loop if areas differ in less than epsilon and more points than minIteration are computed
	} while(fabs( area[(points+1)%2] - ( area[points%2] = (double)pointsInside/++points * (hb - lb) * height) ) > epsilon || points < minIterations );
	
	return area[points%2];
}

// Kreis
double f(double x) {
  return sqrt(1.0 - x * x);
}

