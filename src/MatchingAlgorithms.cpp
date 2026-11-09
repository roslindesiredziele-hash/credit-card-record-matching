#include "MatchingAlgorithms.h"

#include <fstream>
#include <sstream>
#include <algorithm>

string ReconstructCardNumber(
    const string& firstPart,
    const string& secondPart)
{
    return firstPart.substr(0, 15)
        + secondPart.substr(15);
}

vector<CardRecord> LoadCSV(const string& filename)
{
    vector<CardRecord> cards;

    ifstream file(filename);

    if (!file)
    {
        return cards;
    }

    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        CardRecord card;

        getline(ss, card.cardNumber, ',');
        getline(ss, card.expiryDate, ',');
        getline(ss, card.verificationCode, ',');
        getline(ss, card.pin, ',');
        getline(ss, card.issuingNetwork, ',');

        cards.push_back(card);
    }

    return cards;
}

bool CompareCards(const CardRecord& a, const CardRecord& b)
{
    if (a.expiryDate == b.expiryDate)
    {
        return a.pin < b.pin;
    }

    return a.expiryDate < b.expiryDate;
}

vector<CardRecord> SortBasedMatch(const vector<CardRecord>& part1, vector<CardRecord> part2)
{
    sort(
        part2.begin(),
        part2.end(),
        CompareCards);

    vector<CardRecord> result;

    for (size_t i = 0;
         i < part1.size();
         i++)
    {
        CardRecord merged;

        merged.cardNumber =
            ReconstructCardNumber(
                part1[i].cardNumber,
                part2[i].cardNumber);

        merged.expiryDate =
            part2[i].expiryDate;

        merged.verificationCode =
            part2[i].verificationCode;

        merged.pin =
            part2[i].pin;

        merged.issuingNetwork =
            part2[i].issuingNetwork;

        result.push_back(merged);
    }

    return result;
}