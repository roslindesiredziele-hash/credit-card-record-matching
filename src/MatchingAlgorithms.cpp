#include "MatchingAlgorithms.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

string ReconstructCardNumber(const string& firstPart, const string& secondPart)
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

bool CompareCards(const CardRecord& a,  const CardRecord& b)
{
    int monthA = stoi(a.expiryDate.substr(0, 2));
    int yearA  = stoi(a.expiryDate.substr(3, 4));

    int monthB = stoi(b.expiryDate.substr(0, 2));
    int yearB  = stoi(b.expiryDate.substr(3, 4));

    if (yearA != yearB)
    {
        return yearA < yearB;
    }

    if (monthA != monthB)
    {
        return monthA < monthB;
    }

    return stoi(a.pin) < stoi(b.pin);
}

bool IsSortedByExpiryAndPin(const vector<CardRecord>& cards)
{
    for(size_t i = 1; i < cards.size(); i++)
    {
        if (CompareCards(cards[i], cards[i - 1]))
        {
            return false;
        }
    }

    return true;
}

vector<CardRecord> SortBasedMatch(const vector<CardRecord>& part1, vector<CardRecord> part2)
{
    sort(part2.begin(), part2.end(), CompareCards);

    vector<CardRecord> result;
    result.reserve(part1.size());

    for (size_t i = 0; i < part1.size(); i++)
    {
       result.push_back
       (
        {
            ReconstructCardNumber(part1[i].cardNumber, part2[i].cardNumber),
            part2[i].expiryDate,
            part2[i].verificationCode,
            part2[i].pin,
            part2[i].issuingNetwork
        }
       );
    }
    
    return result;
}

vector<CardRecord> HashBasedMatch(const vector<CardRecord>& part1, const vector<CardRecord>& part2)
{
    unordered_map<string, CardRecord> table;

    for (const CardRecord& card : part2)
    {
        table.emplace(card.key(), card);
    }

    vector<CardRecord> result;
    result.reserve(part1.size());

    return result;
}