#ifndef MATCHING_ALGORITHMS_H
#define MATCHING_ALGORITHMS_H

#include <vector>
#include "CardRecord.h"

using namespace std;

vector<CardRecord> LoadCSV(const string& filename);

vector<CardRecord> SortBasedMatch(
    const vector<CardRecord>& carddump1,
    const vector<CardRecord>& carddump2);

vector<CardRecord> HashBasedMatch(
    const vector<CardRecord>& carddump1,
    const vector<CardRecord>& carddump2);

#endif