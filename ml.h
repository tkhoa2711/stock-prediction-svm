#pragma once

#ifndef MACHINE_LEARNING_H
#define MACHINE_LEARNING_H

#include <iostream>
#include <vector>
#include <fstream>

typedef std::vector<double> VectorDouble;
typedef std::vector<double>::iterator VectorDoubleIter;
typedef std::vector<double>::const_iterator VectorDoubleIterConst;

namespace machine_learning 
{

struct svm_feature {
	string name;
};

struct svm_node
{
	int index;
	double value;
};

struct svm_problem
{
	int l;
	double *y;
	struct svm_node **x;
};

/*****************************************************************************/
/*
 * @Class: Function
 * @Description: A generic abstract function
 */
class Function
{
public:
	virtual void operator()() = 0;

protected:
	virtual ~Function() {};
};

/*****************************************************************************/
/*
 * @Class: Polynomial
 */
class Polynomial
{
public:
	Polynomial();
	~Polynomial();

	friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial);

private:
	std::vector<double> coefficent_;	
};	// Polynomial

/*****************************************************************************/
/*
 * KernelFunction
 * F(X) = f(x[1]) + f(x[2]) + ... + f(x[n])
 * X = (x[1], x[2], ... , x[n])
 */
	
class KernelFunction {
public:
	KernelFunction();
	KernelFunction(const std::vector<double>& coefficent);
	~KernelFunction();

	double operator()(const std::vector<double>& x);
	void print();

private:
	std::vector<double> coefficient_;
};	// KernelFunction

/*****************************************************************************/
/*
 * MultiVariateFunction
 */
class MultiVariateFunction {
public:
	MultiVariateFunction();
	~MultiVariateFunction();

	friend std::ostream& operator<<(std::ostream& os, const MultiVariateFunction& function);
	std::vector<double> getTheta() const;
	double getTheta(const int& index) const;


private:
	std::vector<double> theta_;
};	// MultiVariateFunction

/*****************************************************************************/
/*
 * MultiVariateLinearFunction
 * f(x) = theta0.x[0] + theta1.x[1] + theta2.x[2] + .. thetan.x[n]
 *      = theta0 + theta1.x[1] + theta2.x[2] + .. thetan.x[n]		  
 * Note: x[0] = 1
 */
class MultiVariateLinearFunction {
public:
	MultiVariateLinearFunction();
	MultiVariateLinearFunction(const std::vector<double>& theta);
	// ~MultiVariateLinearFunction();

	friend std::ostream& operator<<(std::ostream& os, const MultiVariateLinearFunction& function);
	friend std::istream& operator>>(std::istream& is, MultiVariateLinearFunction& function);
	double operator()(const std::vector<double>& x);
	void setTheta(const std::vector<double>& theta);
	std::vector<double> getTheta() const;
	double getTheta(const int& index) const;
	void insertTheta(const double& theta);
	double getResult(const std::vector<double>& x) const;

private:
	std::vector<double> theta_;		
};	// MultiVariateLinearFunction

/*****************************************************************************/
/*
 * GradientDescend
 */
class GradientDescend
{
public:
	GradientDescend();
	~GradientDescend();

private:
};	// GradientDescend

}

#endif	// MACHINE_LEARNING_H
