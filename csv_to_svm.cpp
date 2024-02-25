#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "csv_to_svm.h"

using namespace std;

void csv_to_svm(const string& input_file, const string& output_file, const int& task)
{	
	ifstream infile(input_file.c_str());
	// cout << infile.rdbuf();	// output entire input file
	if (infile.bad())
		cout << "Unable to open input file: " << input_file << endl;
		
	ofstream outfile(output_file.c_str());
	if (!outfile.is_open())
		cout << "Unable to open output file: " << output_file << endl;

	int date = 1;

	if (infile.good()) {
		unsigned int price_index = 0;
		int i = 0;
		string line;
		int previous = 0;
		while (getline(infile, line)) {
			istringstream iss(line);
			vector<string> words;
			string word;
			// Parse each word of a line into a vector
			while (getline(iss, word, ','))
				words.push_back(word);
			if (i == 0) {
				// First line
				// Get index of closing stock price
				string header = "Close";
				price_index = find(words.begin(), words.end(), header) - words.begin();				
				if (price_index >= words.size()) {
					cout << "Unable to find stock price index" << endl;
					break;
				}
			} else {
				// Make close price at output
				// Regression
				if (task == 1) {
					outfile << words.at(price_index);					
				} else // Classification
				if (task == 0) {
					int current = atoi(words.at(price_index).c_str());
					if (previous == 0) {
						outfile << 1;
					} else {
						if (previous < current)
							outfile << "-1";
						else outfile << 1;
					}
					previous = current;
				}
				// Delete close price
				words.erase(words.begin() + price_index);
				// Delete date info
				// words.erase(words.begin());
				// words.push_back(toString<int>(date++));
				// Delete Adj close price
				// words.erase(words.end() - 1);
				for (int j = 0; j < words.size(); j++) {
					outfile << " " << (j+1) << ":" << words.at(j);
				}
				outfile << endl;
			}			
			i++;
		}
		infile.close();
	}

	if (outfile.is_open()) outfile.close();
	// cout << "Done!" << endl;
}

/*
int main(int argc, char** argv)
{
	string csv_file_name = argv[1];
	string svm_file_name = argv[2];
	csv_to_svm(csv_file_name, svm_file_name);
	return 0;
}
*/