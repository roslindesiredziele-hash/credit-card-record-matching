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

    return 0;
}