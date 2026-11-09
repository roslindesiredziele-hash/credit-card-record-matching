#ifndef MATCHING_ALGORITHMS_H
#define MATCHING_ALGORITHMS_H

#include <vector>
#include "CardRecord.h"

using namespace std;

vector<CardRecord> LoadCSV(const string& filename);

vector<CardRecord> SortBasedMatch(
    const vector<CardRecord>& part1,
    const vector<CardRecord>& part2);

vector<CardRecord> HashBasedMatch(
    const vector<CardRecord>& part1,
    const vector<CardRecord>& part2);

#endif