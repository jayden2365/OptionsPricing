#include "Option.h"
#include <iostream>

using namespace std;

void
Option::print() {
	cout << "Option:" << endl;
	cout << "Spot Price: " << this->spotPrice << endl;
	cout << "Strike Price: " << this->strikePrice << endl;
	cout << "Rate: " << this->rate << endl;
	cout << "Volatility: " << this->vol << endl;
	cout << "Maturity: " << this->maturity << " year(s)" << endl;
	cout << "Option Type: " << ((this->e_a == European) ? "European" : "American") << endl;
	cout << "Exercise Type: " << ((this->c_p == Call) ? "Call" : "Put") << endl;
}