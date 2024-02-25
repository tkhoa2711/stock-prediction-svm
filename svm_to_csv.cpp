#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

void svm_to_csv(const std::string& input_file_name, const std::string& output_file_name)
{
	ifstream infile(input_file_name.c_str());
	if (infile.bad())
		cout << "Unable to open input file: " << input_file_name << endl;

	ofstream outfile(output_file_name.c_str());
	if (outfile.bad())
		cout << "Unable to open output file: " << output_file_name << endl;

	string line;
	
	while (getline(infile, line)) {
		cout << line << endl;
		istringstream iss(line);
		vector<string> words;
		string word;
		
		getline(iss, word);
		string edited_line = word;

		// while (getline(iss, word)) {
		// 	unsigned pos = word.find(":");
		// 	edited_line.append(",").append(word.substr(pos+1));
		// }
		outfile << edited_line << endl;
	}

	infile.close();
	outfile.close();
}

int main(int argc, char** argv)
{
	string input_file_name = argv[1];
	string output_file_name = input_file_name.append(".csv");

	svm_to_csv(input_file_name, output_file_name);

	return 0;
}