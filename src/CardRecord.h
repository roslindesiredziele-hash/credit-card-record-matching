#ifndef CARD_RECORD_H
#define CARD_RECORD_H

#include <string>

struct CardRecord
{
    std::string cardNumber;
    std::string expiration;
    std::string pin;
};

#endif
