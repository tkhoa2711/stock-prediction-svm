#pragma once

#ifndef FINANCIAL_RATIO_H
#define FINANCIAL_RATIO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <queue>
#include "util.h"

using namespace std;

/*****************************************************************************/
/*
 * Exponential Moving Average
 */
template<typename T>
class EMA {
public:	
	void operator()(std::vector<T>& ema, const std::vector<T>& price, const int& period = 14)
	{
		T alpha = 2 / ((T)period + 1);
		T last_ema = 0.0;
		T current_ema = 0.0;
		for (typename vector<T>::const_iterator it = price.begin(); it != price.end(); ++it) {
			T current_price = *it;
			if (ema.empty())
				ema.push_back(current_price);
			else {
				current_ema = last_ema + alpha * (current_price - last_ema);
				ema.push_back(current_ema);
				last_ema = current_ema;
			}
		}
	}
};

/*
 * Relative Strength Index
 */
template<typename T>
class RSI
{
public:	
	void operator()(std::vector<T>& rsi, const std::vector<T>& price, const int& period = 14)
	{
		vector<T> gain;
		vector<T> loss;
		vector<T> average_gain;
		vector<T> average_loss;
		EMA<T> ema_calc;

		for (int i = 0; i < price.size()-1; i++) {
			if (price.at(i) < price.at(i+1)) {
				gain.push_back(price.at(i+1));
				loss.push_back(0);
			} else if (price.at(i) > price.at(i+1)) {
				gain.push_back(0);
				loss.push_back(price.at(i+1));
			} else if (price.at(i) == price.at(i+1)) {
				gain.push_back(0);
				loss.push_back(0);
			}			
		}

		ema_calc(average_gain, gain, period);
		ema_calc(average_loss, loss, period);

		// RSI = 100 - 100 / (1 + ema(up)/ema(down));
		rsi.push_back(50);
		for (int i = 0; i < price.size()-1; i++) {
			rsi.push_back(100 - 100/(1 + average_gain.at(i)/average_loss.at(i)));
		}
	}
};

/*****************************************************************************/
/*
 * Add a column to CSV file according to an indicator
 */
template< template<typename T> class Calc, typename T>
void add_feature(const std::string& filename, const std::string& title)
{
	ifstream infile(filename.c_str());
	if (infile.bad())
		cout << "ifstream is bad!" << endl;

	vector<string> buffer;
	string header;
	string line;
	int i = 0;
	while (getline(infile, line)) {
		if (i == 0) {
			header = line.append(",").append(title);
		} else {
			buffer.push_back(line);
		}
		i++;
	}
	infile.close();

	vector<T> close_price;
	get_csv_column_data<T>(close_price, filename, "Close");

	vector<T> series;
	Calc<T> calc;
	calc(series, close_price, 14);
	// calculate_ema_series<double>(ema, close_price, 14);

	ofstream outfile(filename.c_str());
	if (outfile.bad())
		cout << "ofstream is bad!" << endl;

	outfile << header << endl;
	for (int j = 0; j < buffer.size(); j++) {
		outfile << buffer.at(j) << "," << series.at(j) << endl;
	}
	outfile.close();	
}


#endif	// FINANCIAL_RATIO_H
