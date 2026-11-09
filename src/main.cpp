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

    cout << dump2[0].key() << endl;

    cout
<< ReconstructCardNumber(
      "5471-0712-2573-****",
      "****-****-****-9527")
<< endl;

cout << dump2[1].expiryDate << endl;

vector<CardRecord> matches =
    SortBasedMatch(dump1, dump2);

cout << matches[0].cardNumber
     << endl;

cout << matches[0].expiryDate
     << endl;

cout << matches[0].pin
     << endl;

cout << IsSortedByExpiryAndPin(matches)
     << endl;

    return 0;
}