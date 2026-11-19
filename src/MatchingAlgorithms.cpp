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

void Merge(vector<CardRecord>& cards, int left, int mid, int right)
{
    int n = right - left + 1;

    vector<CardRecord> temp;
    temp.reserve(n);

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (CompareCards(cards[i], cards[j]))
        {
            temp.push_back(cards[i]);
            i++;
        }
        else
        {
            temp.push_back(cards[j]);
            j++;
        }
    }

    while (i <= mid)
    {
        temp.push_back(cards[i]);
        i++;
    }

    while (j <= right)
    {
        temp.push_back(cards[j]);
        j++;
    }

    for (size_t step = 0; step < temp.size(); step++)
    {
        cards[left + static_cast<int>(step)]
            = temp[step];
    }
}

void MergeSort(vector<CardRecord>& cards, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid =
        left + (right - left) / 2;

    MergeSort(cards, left, mid);
    MergeSort(cards, mid + 1, right);

    Merge(cards, left, mid, right);
}

vector<CardRecord> MergeSortBasedMatch(const vector<CardRecord>& part1, vector<CardRecord> part2)
{
    MergeSort(part2, 0, static_cast<int>(part2.size()) - 1);

    vector<CardRecord> result;
    result.reserve(part1.size());

    for (size_t i = 0; i < part1.size(); i++)
    {
        result.push_back(
        {
            ReconstructCardNumber(
                part1[i].cardNumber,
                part2[i].cardNumber),

            part2[i].expiryDate,
            part2[i].verificationCode,
            part2[i].pin,
            part2[i].issuingNetwork
        });
    }

    return result;
}