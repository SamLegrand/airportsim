//
// Created by sam on 16.03.18.
//

#ifndef AIRPORTSIM_UTILS_H
#define AIRPORTSIM_UTILS_H

#include <iostream>

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);

std::string to_string(int i);

#endif //AIRPORTSIM_UTILS_H
