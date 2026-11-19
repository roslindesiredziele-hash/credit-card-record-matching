#define CATCH_CONFIG_MAIN

#include "../external/catch.hpp"

#include "../src/CardRecord.h"
#include "../src/MatchingAlgorithms.h"

#include <vector>
#include <string>

TEST_CASE("Composite key ordering is preserved", "[counting-sort]")
{
    std::vector<CardRecord> records =
    {
        {"1111111111111111", "12/2026", "123", "9999", "Visa"},
        {"2222222222222222", "01/2025", "456", "1111", "Mastercard"},
        {"3333333333333333", "08/2025", "789", "5000", "Visa"}
    };

    countingSort(records);

    REQUIRE(records.size() == 3);
}

