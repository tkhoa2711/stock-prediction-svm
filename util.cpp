#include "util.h"

using namespace std;

void remove_csv_column_data(const string& filename, const string& title)
{
	ifstream infile(filename.c_str());
	if (infile.bad())
		cout << "Unable to open input file: " << filename << endl;

	string line;
	string header;
	vector<string> edited_lines;
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
			column_index = find(words.begin(), words.end(), title) - words.begin();				
			if (column_index >= words.size()) {
				cout << "Unable to find index of column " << title << endl;
				return;
			}
			words.erase(words.begin() + column_index);
			for (size_t j = 0; j < words.size(); j++)
				header.append(words.at(j)).append(",");
		} else {
			words.erase(words.begin() + column_index);
			string tmp;
			for (int j = 0; j < words.size(); j++) {
				tmp.append(words.at(j)).append(",");
			}
			// Remove the last ','
			// tmp.resize(0, tmp.size() - 1);
			edited_lines.push_back(tmp.substr(0, tmp.size()-1));
		}
		i++;
	}
	infile.close();

	ofstream outfile(filename.c_str());
	if (outfile.bad())
		cout << "Unable to open output file: " << filename << endl;

	outfile << header.substr(0, header.size()-1) << endl;
	for (int j = 0; j < edited_lines.size(); j++)
		outfile << edited_lines.at(j) << endl;
	outfile.close();
}

void reverse_csv_data(std::string csv_file_name)
{
	ifstream infile(csv_file_name.c_str());
	if (infile.bad())
		cout << "Unable to open input file: " << csv_file_name << endl;

	string line;
	string header;
	vector<string> lines;
	int i = 0;

	while (getline(infile, line)) {
		if (i == 0)
			header = line;
		else
			lines.push_back(line);
		i++;
	}
	infile.close();

	reverse(lines.begin(), lines.end());

	ofstream outfile(csv_file_name.c_str());
	if (outfile.bad())
		cout << "Unable to open output file: " << csv_file_name << endl;

	outfile << header << endl;
	for (int j = 0; j < lines.size(); j++)
		outfile << lines.at(j) << endl;
	outfile.close();
}
