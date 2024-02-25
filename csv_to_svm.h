#pragma once

#ifndef CSV_TO_SVM_H
#define CSV_TO_SVM_H

#include <string>
#include "util.h"

void csv_to_svm(const std::string& input_file, const std::string& output_file, const int& task);

#endif

