#include "MatchingAlgorithms.h"

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

int main()
{
    vector<CardRecord> dump1 = LoadCSV("./data/carddump1.csv");
    vector<CardRecord> dump2 = LoadCSV("./data/carddump2.csv");

    ofstream outfile("./data/data.csv");
    
    if (!outfile)
    {
        cerr << "Unable to open data.csv\n";
        return 1;
    }

        outfile
        <<"Size"
        <<" MergeSortBasedMatch,"
        <<" LinearSortBasedMatch" << endl;

    LARGE_INTEGER t, t1, f;
    QueryPerformanceFrequency(&f);

    QueryPerformanceCounter(&t);
    vector<CardRecord> Mmatches = MergeSortBasedMatch(dump1, dump2);
    QueryPerformanceCounter(&t1);
    double MergeTime = (t1.QuadPart - t.QuadPart) * 1000.0 / f.QuadPart;

    QueryPerformanceCounter(&t);
    vector<CardRecord> Lmatches = LinearSortBasedMatch(dump1, dump2);
    QueryPerformanceCounter(&t1);
    double LinearTime = (t1.QuadPart - t.QuadPart) * 1000.0 / f.QuadPart;

    outfile
    << MergeTime <<","<< LinearTime << endl;

     outfile.close();

    return 0;
}