#include <string>
#include "csv_to_svm.h"
#include "financial_ratio.h"
#include "util.h"

// #include "libsvm-3.12/svm.h"

using namespace std;

void predictStock(std::string csv_file_name, std::string svm_file_name, const int& task)
{
	reverse_csv_data(csv_file_name);

	add_feature<EMA, double>(csv_file_name, "EMA");
	add_feature<RSI, double>(csv_file_name, "RSI");

	remove_csv_column_data(csv_file_name, "Date");
	remove_csv_column_data(csv_file_name, "Adj Close");
	// remove_csv_column_data(csv_file_name, "Open");
	remove_csv_column_data(csv_file_name, "High");
	remove_csv_column_data(csv_file_name, "Low");
	remove_csv_column_data(csv_file_name, "Volume");

	csv_to_svm(csv_file_name, svm_file_name, task);
}

int main(int argc, char** argv)
{
	// task:
	// - 0 : classification
	// - 1 : regression
	const int task = 0;

	string csv_file_name = argv[1];
	string svm_file_name = argv[2];

	predictStock(csv_file_name, svm_file_name, task);

	return 0;
}
