#ifndef CARD_RECORD_H
#define CARD_RECORD_H

#include <string>

using namespace std;

class CardRecord
{
    public:
    string cardNumber;
    string expiryDate;
    string verificationCode;
    string pin;
    string issuingNetwork;
};

#endif
