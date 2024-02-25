#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

void split_file(const string& input_file, const int& numLine, const string& output_file1, const string output_file2)
{
	ifstream infile(input_file.c_str());
	if (infile.bad()) {
		cout << "Unable to open input file: " << input_file << endl;
		return;
	}
		
	ofstream outfile1(output_file1.c_str());
	if (outfile1.bad()) {
		cout << "Unable to open input file: " << output_file1 << endl;
		return;
	}

	ofstream outfile2(output_file2.c_str());
	if (outfile2.bad()) {
		cout << "Unable to open input file: " << output_file2 << endl;
		return;
	}

	// new lines will be skipped unless we stop it from happening:    
    // myfile.unsetf(std::ios_base::skipws);

	unsigned line_count = count(istreambuf_iterator<char>(infile), istreambuf_iterator<char>(), '\n');	

	if ( line_count <= numLine) {
		cout << "File has fewer than number of lines specified" << endl;
		return;
	}

	string line;
	int i = 0;
	infile.seekg(0, ios::beg);

	while (getline(infile, line) && i < line_count) {
		if (i < numLine) {
			outfile1 << line << endl;
		} else {
			outfile2 << line << endl;
		}
		i++;
	}

	infile.close();
	outfile1.close();
	outfile2.close();
}

int main(int argc, char** argv)
{
	string input_file = argv[1];
	int numLine;
	stringstream(argv[2]) >> numLine;
	string output_file1 = argv[3];
	string output_file2 = argv[4];

	split_file(input_file, numLine, output_file1, output_file2);
	return 0;
}