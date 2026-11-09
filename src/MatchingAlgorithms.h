#ifndef MATCHING_ALGORITHMS_H
#define MATCHING_ALGORITHMS_H

#include "CardRecord.h"

#include <vector>
#include <string>

using namespace std;

vector<CardRecord> LoadCSV(const string& filename);

string ReconstructCardNumber(const string& firstPart, const string& secondPart);

bool CompareCards(const CardRecord& a,  const CardRecord& b);

bool IsSortedByExpiryAndPin(const vector<CardRecord>& cards);

vector<CardRecord> SortBasedMatch(const vector<CardRecord>& part1, vector<CardRecord> part2);

vector<CardRecord> HashBasedMatch(const vector<CardRecord>& part1, const vector<CardRecord>& part2);

#endif