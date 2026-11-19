#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "MatchingAlgorithms.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>

double MeasureMergeSort( const vector<CardRecord>& dump1, const vector<CardRecord>& dump2,
    int repetitions)
{
    LARGE_INTEGER start, end, frequency;

    QueryPerformanceFrequency(&frequency);

    double totalTime = 0.0;

    for (int i = 0; i < repetitions; i++)
    {
        QueryPerformanceCounter(&start);

        MergeSortBasedMatch(
            dump1,
            dump2);

        QueryPerformanceCounter(&end);

        totalTime +=
            (end.QuadPart - start.QuadPart)
            * 1000.0
            / frequency.QuadPart;
    }

    return totalTime / repetitions;
}

double MeasureLinearSort(
    const vector<CardRecord>& dump1,
    const vector<CardRecord>& dump2,
    int repetitions)
{
    LARGE_INTEGER start, end, frequency;

    QueryPerformanceFrequency(&frequency);

    double totalTime = 0.0;

    for (int i = 0; i < repetitions; i++)
    {
        QueryPerformanceCounter(&start);

        LinearSortBasedMatch(
            dump1,
            dump2);

        QueryPerformanceCounter(&end);

        totalTime +=
            (end.QuadPart - start.QuadPart)
            * 1000.0
            / frequency.QuadPart;
    }

    return totalTime / repetitions;
}

int main()
{
    vector<CardRecord> dump1 =
        LoadCSV("./data/carddump1.csv");

    vector<CardRecord> dump2 =
        LoadCSV("./data/carddump2.csv");

    ofstream outfile("./data/data.csv");

    if (!outfile)
    {
        cerr << "Unable to open data.csv\n";
        return 1;
    }

    outfile
        << "Size,"
        << "MergeSortMs,"
        << "LinearSortMs"
        << endl;

    vector<int> sizes =
    {
        100,
        500,
        1000,
        2500,
        5000,
        10000,
        15000,
        20000
    };

    const int repetitions = 30;

    for (int size : sizes)
    {
        vector<CardRecord> d1(
            dump1.begin(),
            dump1.begin() + size);

        vector<CardRecord> d2(
            dump2.begin(),
            dump2.begin() + size);

        double mergeTime =
            MeasureMergeSort(
                d1,
                d2,
                repetitions);

        double linearTime =
            MeasureLinearSort(
                d1,
                d2,
                repetitions);

        cout
            << "Size: "
            << size
            << " | MergeSort: "
            << mergeTime
            << " ms"
            << " | Linear: "
            << linearTime
            << " ms"
            << endl;

        outfile
            << size
            << ","
            << mergeTime
            << ","
            << linearTime
            << endl;
    }

    outfile.close();

    return 0;
}