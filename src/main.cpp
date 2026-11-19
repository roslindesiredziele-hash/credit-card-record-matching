#include "MatchingAlgorithms.h"

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

int main()
{
    ofstream outfile("./data/data.csv");

     if (!outfile)
        {
            cerr << "Unable to open data.csv\n";
            return 1;
        }

        outfile
        <<" MergeSortBasedMatch,"
        <<" LinearBasedMatch" << endl;

    

    return 0;
}