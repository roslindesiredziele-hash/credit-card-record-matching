#include "MatchingAlgorithms.h"

#include <fstream>
#include <sstream>

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