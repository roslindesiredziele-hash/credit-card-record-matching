#include <iostream>

#include "MatchingAlgorithms.h"

using namespace std;

int main()
{
    vector<CardRecord> dump1 =
        LoadCSV("./data/carddump1.csv");

    vector<CardRecord> dump2 =
        LoadCSV("./data/carddump2.csv");

    cout << "Dump1: "
     << dump1.size()
     << endl;

cout << "Dump2: "
     << dump2.size()
     << endl;

vector<CardRecord> matches =
    MergeSortBasedMatch(dump1, dump2);

cout << "MergeSort Matched records: "
     << matches.size()
     << endl;

cout << "MergeSort Sorted correctly: "
     << IsSortedByExpiryAndPin(matches)
     << endl;

     vector<CardRecord> linearMatches =
    LinearSortBasedMatch(dump1, dump2);

cout << "Linear matched records: "
     << linearMatches.size()
     << endl;

cout << "Linear sorted correctly: "
     << IsSortedByExpiryAndPin(linearMatches)
     << endl;

     cout << "Same size: "
     << (matches.size() ==
         linearMatches.size())
     << endl;

cout << "First card equal: "
     << (matches[0].cardNumber ==
         linearMatches[0].cardNumber)
     << endl;

    return 0;
}