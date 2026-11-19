#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>

#include "MatchingAlgorithms.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

double MeasureMergeSort(
    const vector<CardRecord> &dump1,
    const vector<CardRecord> &dump2,
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
            (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
        }

    return totalTime / repetitions;
    }

double MeasureLinearSort(
    const vector<CardRecord> &dump1,
    const vector<CardRecord> &dump2,
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
            (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
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
        // 5 - 25
        5,
        10,
        15,
        20,
        25,

        // 25 - 50
        25,
        30,
        35,
        40,
        45,
        50,

        // 50 - 100
        50,
        60,
        70,
        80,
        90,
        100,

        // 100 - 1000
        100,
        200,
        300,
        400,
        500,
        600,
        700,
        800,
        900,
        1000,

        // 1000 - 2000
        1000,
        1200,
        1400,
        1600,
        1800,
        2000
        };

    for (int size : sizes)
        {
        int repetitions;

        if (size <= 100)
            {
            repetitions = 1000;
            }
        else if (size <= 1000)
            {
            repetitions = 200;
            }
        else
            {
            repetitions = 50;
            }

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

    cout << "\nBenchmark completed.\n";
    cout << "Results saved to ./data/data.csv\n";

    return 0;
    }
