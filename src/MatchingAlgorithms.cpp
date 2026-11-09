#include "MatchingAlgorithms.h"

#include <fstream>
#include <sstream>

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