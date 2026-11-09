#ifndef CARD_RECORD_H
#define CARD_RECORD_H

#include <string>

using namespace std;

struct CardRecord
{
    string cardNumber;
    string expiryDate;
    string verificationCode;
    string pin;
    string issuingNetwork;

    string key() const
    {
        return expiryDate + "#" + pin;
    }
};

#endif
