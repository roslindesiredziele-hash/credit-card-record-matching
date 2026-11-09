#ifndef MATCHING_ALGORITHMS_H
#define MATCHING_ALGORITHMS_H

#include "CardRecord.h"

#include <vector>
#include <string>

using namespace std;

vector<CardRecord> LoadCSV(const string& filename);

string ReconstructCardNumber(
    const string& firstPart,
    const string& secondPart);

vector<CardRecord> SortBasedMatch(
    const vector<CardRecord>& part1,
    vector<CardRecord> part2);

#endif