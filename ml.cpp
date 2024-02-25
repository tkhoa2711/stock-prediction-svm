#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include "ml.h"

using namespace std;

namespace machine_learning 
{

/*****************************************************************************/
/*
 * Multivariate Function
 */

vector<double> MultiVariateFunction::getTheta() const
{
	return theta_;
}

double MultiVariateFunction::getTheta(const int& index) const
{
	return theta_.at(index);
}

// MultiVariateFunction

/*****************************************************************************/
/*
 * KernelFunction
 */
void KernelFunction::print()
{
	copy(coefficient_.begin(), coefficient_.end(), ostream_iterator<double>(cout, "\n"));
}

// KernelFunction

/*****************************************************************************/
/* 
 * MultiVariateLinearFunction
 */

MultiVariateLinearFunction::MultiVariateLinearFunction()
{
	cout << "MultiVariateLinearFunction() called." << endl;
}

MultiVariateLinearFunction::MultiVariateLinearFunction(const vector<double>& theta)
{
	for (vector<double>::const_iterator it = theta.begin(); it != theta.end(); ++it)
		this->theta_.push_back(*it);
	// for_each(theta.begin(), theta.end(), this->theta_.push_back(_1));
}

ostream& operator<<(ostream& os, const MultiVariateLinearFunction& function)
{		
	vector<double> theta_(function.getTheta());		
	for (size_t i = 0, max = theta_.size(); i != max; i++) {
		if (i == 0) {
			os << theta_.at(i);
		} else {
			os << " + " << theta_.at(i) << "x[" << i << "]";		
		}
	}
	os << endl;
	return os;
}

istream& operator>>(istream& is, MultiVariateLinearFunction& function)
{
	while(!is.eof()) {
		double x;
		is >> x;
		function.insertTheta(x);
	}
	return is;
}

double MultiVariateLinearFunction::operator()(const vector<double>& x)
{
	return getResult(x);
}

void MultiVariateLinearFunction::setTheta(const std::vector<double>& theta)
{
	theta_ = theta;
}

vector<double> MultiVariateLinearFunction::getTheta() const
{
	return theta_;
}

double MultiVariateLinearFunction::getTheta(const int& index) const
{
	return theta_.at(index);
}

void MultiVariateLinearFunction::insertTheta(const double& theta)
{
	theta_.push_back(theta);
}

double MultiVariateLinearFunction::getResult(const vector<double>& x) const
{
	double result = 0.0;
	if (x.size() != theta_.size())
		return result;
	for (int i = 0; i < theta_.size(); i++)
		result += theta_.at(i) * x.at(i);
	return result;
}

// MultiVariateLinearFunction

}