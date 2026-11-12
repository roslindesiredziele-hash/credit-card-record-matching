#include <iostream>
#include <unordered_map>

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
    SortBasedMatch(dump1, dump2);

cout << "Matched records: "
     << matches.size()
     << endl;

cout << "Sorted correctly: "
     << IsSortedByExpiryAndPin(matches)
     << endl;

    return 0;
}