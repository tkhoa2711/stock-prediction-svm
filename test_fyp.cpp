#define BOOST_TEST_MODULE FypTest

#include <boost/test/included/unit_test.hpp>

#include "ml.h"
#include "financial_ratio.h"
#include "util.cpp"

#if _cplusplus >= 201103L			// C++0x/C++11 (only applicable with gcc-4.7 onwards)
# ifndef __GXX_EXPERIMENTAL_CXX0X__	// applicable with gcc-4.4 onwards
#  define __GXX_EXPERIMENTAL_CXX0X__ 1
# endif
# pragma message "Compiled with C++0x flag"
#else	// _cplusplus == 199711L	// C++98/03
# pragma message "Compiled without C++0x flag"
#endif

using namespace std;
using namespace machine_learning;
using namespace financial_ratio;
using namespace util;

/*
 * Test suite for compiling, linking and building program
 */
BOOST_AUTO_TEST_SUITE(Building)

BOOST_AUTO_TEST_CASE(compilerFlag)
{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	cout << "Compiled with C++0x flag" << endl;
#else
	cout << "Compiled without C++0x flag" << endl;
#endif
}

// BOOST_AUTO_TEST_CASE(readCSV)
// {

// }

BOOST_AUTO_TEST_CASE(convertCsvToSvm)
{
	string csv_file;
	string svm_file;
	boost::shared_ptr<CSV> csv_data(new CSV());	
	csv_file = "data/sbuxPrices.csv";
	svm_file = "data/sbuxPrices.csv.svm";
	//csv_to_svm(csv_file, svm_file, csv_data.get());
}

BOOST_AUTO_TEST_SUITE_END()

/*
 * Test suite for FinancialRatio
 */	
BOOST_AUTO_TEST_SUITE(FinancialRatio)

BOOST_AUTO_TEST_CASE(emaSeries)
{
	ExponentialMovingAverage ema;
	//BOOST_CHECK_EQUAL(add(2, 2), 4);
}

BOOST_AUTO_TEST_SUITE_END()

/*
 * Test suite for MachineLearning
 */	
BOOST_AUTO_TEST_SUITE(MachineLearning)

BOOST_AUTO_TEST_CASE(multiVariateLinearFunction)
{

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	// Source code is compiled with c++0x flag
	vector<double> v = {1.0, 4.12, 13.1};
	vector<double> x = {0.0, 0.4, 3.5};
	double result = 47.498;
#else
	// Source code is compiled without c++0x flag
	double arr_v[] = {1.0, 4.12, 13.1};
	vector<double> v(arr_v, arr_v + sizeof(arr_v) / sizeof(double));
	double arr_x[] = {0.0, 0.4, 3.5};
	vector<double> x(arr_x, arr_x + sizeof(arr_x) / sizeof(double));
	double result = 47.498;
#endif

	BOOST_REQUIRE(v.size() == x.size());
	MultiVariateLinearFunction f1(v);
	cout << "f1(x) = " << f1 << endl;	
	BOOST_CHECK_MESSAGE(f1(x) == result, "f1(x) = " << f1(x) << ", expected: " << result);
}

BOOST_AUTO_TEST_SUITE_END()
