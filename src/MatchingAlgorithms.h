#ifndef MATCHING_ALGORITHMS_H
#define MATCHING_ALGORITHMS_H

#include "CardRecord.h"

#include <vector>
#include <string>

using namespace std;

vector<CardRecord> LoadCSV(const string& filename);

#endif