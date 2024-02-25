#!/usr/bin/env bash

filename=data/GOOG

csv_data=${filename}.csv
svm_data=${filename}
train_data=${filename}.train
test_data=${filename}.test
model=${filename}.model
output=${filename}.out

TRAIN_EXEC=libsvm-3.12/windows/svm-train.exe
PREDICT_EXEC=libsvm-3.12/windows/svm-predict.exe

echo "Compiling ..."
# g++ -o split split.cpp
g++ -o fyp fyp.cpp csv_to_svm.cpp util.cpp financial_ratio.cpp

echo "Converting ..."
# convert from csv to svm format
./fyp.exe $csv_data $svm_data

# <<COMMENT

# echo "Scaling ..."
# libsvm-3.12/windows/svm-scale.exe -l -1 -u 1 -y -1 1 -s range $svm_data > ${svm_data}.scale

# cp ${svm_data}.scale $svm_data

echo "Splitting data ..."
# split data into training and testing
# python libsvm-3.12/tools/subset.py $svm_data 1500 $train_data $test_data
./split.exe $svm_data 1500 $train_data $test_data

echo "Training data ..."
# train the training data and output the model
# param:
# -s svm type, 3 for epsilon-SVR
# -t kernel type, 2 for RBF
# $TRAIN_EXEC -s 3 -t 2 $train_data $model
$TRAIN_EXEC -t 2 -s 3 $train_data $model

echo ""
echo "Predicting ..."
# test (predict) the model with testing data
$PREDICT_EXEC $test_data $model $output

# COMMENT

# cp "${filename} - Copy.csv" $csv_data
# [ $? -eq 0 ] && echo "Restored original file" || echo "Could not restore original version"

# COMMENT
