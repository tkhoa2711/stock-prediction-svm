#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;

typedef std::vector<double> CSV_RowData;
typedef std::vector<CSV_RowData> CSV_Row;
typedef std::vector<string> CSV_Column;

void reverse_csv_data(std::string csv_file_name);

template<typename T>
T fromString(const std::string& str)
{
	std::stringstream ss(str);
	T t;
	ss >> t;
	return t;
}

template<typename T>
string toString(const T& x)
{
	std::ostringstream ss;
	ss << x;
	return ss.str();
}

/*****************************************************************************/
/*
 * CSV utility functions
 */

void remove_csv_column_data(const string& filename, const string& title);

template<typename T>
void get_csv_column_data(std::vector<T>& data, const std::string& input_file, const std::string& header)
{
	ifstream infile(input_file.c_str());
	if (infile.bad())
		cout << "Unable to open input file: " << input_file << endl;

	string line;
	int column_index;
	int i = 0;

	while (getline(infile, line)) {
		istringstream iss(line);
		vector<string> words;
		string word;
		// Parse each word of a line into a vector
		while (getline(iss, word, ','))
			words.push_back(word);
		if (i == 0) {
			// First line
			column_index = find(words.begin(), words.end(), header) - words.begin();				
			if (column_index >= words.size()) {
				cout << "Unable to find index of column " << header << endl;
				break;
			}
		} else {
			data.push_back(fromString<double>(words.at(column_index)));			
		}
		i++;
	}
	infile.close();
}

/*
 * A struct represents CSV data
 */
struct CSV
{
public:
	CSV()
	{
		cout << "CSV()" << endl;
	}

	void insertRow(const CSV_RowData& row)
	{
		row_.push_back(row);
	}

	void setRow(const CSV_Row& row)
	{
		for (CSV_Row::const_iterator it = row.begin(), it_end = row.end();
			it != it_end; ++it) {
			CSV_RowData new_row;
			for (CSV_RowData::const_iterator it_row = it->begin(), it_row_end = it->end();
				it_row != it_row_end; ++it) {
				new_row.push_back(*it_row);
			}
			this->insertRow(new_row);
		}
	}

	CSV_Row getRow() const
	{
		return row_;
	}

	void insertColumn(const std::string& column)
	{
		column_.push_back(column);
	}

	void setColumn(const CSV_Column& column)
	{
		column_ = column;
	}

	CSV_Column getColumn() const
	{
		return column_;
	}

	friend ostream& operator<<(ostream& os, const CSV& csv_data)
	{
		// Column header
		CSV_Column col = csv_data.getColumn();
		for (CSV_Column::const_iterator it = col.begin(); it != col.end(); ++it)
			if (it == (--col.end()))
				os << "[" << *it << "]" << endl;
			else
				os << "[" << *it << "] ";
		// Row
		return os;
	}

private:
	CSV_Column column_;
	CSV_Row row_;
};	// CSV

/*****************************************************************************/

template<typename T, int N>
class MovingAverage
{
public:
	MovingAverage(): num_samples_(0), total_(0) {}
	~MovingAverage();
	void operator()(T& sample)
	{
		if (num_samples_ < N) {
			samples_.push_back(sample);
			total_ += sample;
		} else {
			total_ -= samples_.pop_front();
			samples_.push_back(sample);
			total_ += sample;
		}
	}
	
	double operator()() const
	{
		// return total_ / std::min(num_samples_, N);
		return total_ / num_samples_;
	}
	
private:
	std::queue<T> samples_[N];
	int num_samples_;
	T total_;
};


#endif // UTIL_H
