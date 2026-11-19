#define CATCH_CONFIG_MAIN

#include "../external/catch.hpp"

#include "../src/CardRecord.h"
#include "../src/MatchingAlgorithms.h"

#include <vector>
#include <string>

TEST_CASE("ReconstructCardNumber combines card parts")
{
    std::string firstPart  = "123456789012345";
    std::string secondPart = "6789";

    REQUIRE(
        ReconstructCardNumber(firstPart, secondPart)
        == "1234567890123456789"
    );
}

TEST_CASE("CompareCards orders by expiry and PIN")
{
    CardRecord a;
    a.expiryDate = "01/2025";
    a.pin = "1234";

    CardRecord b;
    b.expiryDate = "02/2025";
    b.pin = "1234";

    REQUIRE(CompareCards(a, b));
    REQUIRE_FALSE(CompareCards(b, a));
}

TEST_CASE("ExpiryKey produces non-negative keys")
{
    CardRecord card;
    card.expiryDate = "01/2025";

    REQUIRE(ExpiryKey(card) >= 0);
}

TEST_CASE("CompositeKey is non-negative")
{
    CardRecord card;
    card.expiryDate = "01/2025";
    card.pin = "1234";

    REQUIRE(CompositeKey(card) >= 0);
}

TEST_CASE("IsSortedByExpiryAndPin recognizes sorted sequence")
{
    std::vector<CardRecord> cards(3);

    cards[0].expiryDate = "01/2025";
    cards[0].pin = "1111";

    cards[1].expiryDate = "02/2025";
    cards[1].pin = "2222";

    cards[2].expiryDate = "03/2025";
    cards[2].pin = "3333";

    REQUIRE(IsSortedByExpiryAndPin(cards));
}

TEST_CASE("MergeSort preserves vector size")
{
    std::vector<CardRecord> cards(3);

    cards[0].expiryDate = "03/2025";
    cards[0].pin = "3333";

    cards[1].expiryDate = "01/2025";
    cards[1].pin = "1111";

    cards[2].expiryDate = "02/2025";
    cards[2].pin = "2222";

    auto originalSize = cards.size();

    MergeSort(cards, 0, static_cast<int>(cards.size()) - 1);

    REQUIRE(cards.size() == originalSize);
    REQUIRE(IsSortedByExpiryAndPin(cards));
}

TEST_CASE("CountingSort preserves vector size")
{
    std::vector<CardRecord> cards(3);

    cards[0].expiryDate = "03/2025";
    cards[0].pin = "3333";

    cards[1].expiryDate = "01/2025";
    cards[1].pin = "1111";

    cards[2].expiryDate = "02/2025";
    cards[2].pin = "2222";

    auto originalSize = cards.size();

    CountingSort(cards);

    REQUIRE(cards.size() == originalSize);
}

TEST_CASE("MergeSortBasedMatch reconstructs all records")
{
    std::vector<CardRecord> part1(2);
    std::vector<CardRecord> part2(2);

    part1[0].cardNumber = "123456789012345";
    part1[0].expiryDate = "01/2025";
    part1[0].pin = "1111";

    part1[1].cardNumber = "555555555555555";
    part1[1].expiryDate = "02/2025";
    part1[1].pin = "2222";

    part2[0].cardNumber = "6789";
    part2[0].expiryDate = "01/2025";
    part2[0].pin = "1111";

    part2[1].cardNumber = "9999";
    part2[1].expiryDate = "02/2025";
    part2[1].pin = "2222";

    auto result = MergeSortBasedMatch(part1, part2);

    REQUIRE(result.size() == 2);
}

TEST_CASE("LinearSortBasedMatch reconstructs all records")
{
    std::vector<CardRecord> part1(2);
    std::vector<CardRecord> part2(2);

    part1[0].cardNumber = "123456789012345";
    part1[0].expiryDate = "01/2025";
    part1[0].pin = "1111";

    part1[1].cardNumber = "555555555555555";
    part1[1].expiryDate = "02/2025";
    part1[1].pin = "2222";

    part2[0].cardNumber = "6789";
    part2[0].expiryDate = "01/2025";
    part2[0].pin = "1111";

    part2[1].cardNumber = "9999";
    part2[1].expiryDate = "02/2025";
    part2[1].pin = "2222";

    auto result = LinearSortBasedMatch(part1, part2);

    REQUIRE(result.size() == 2);
}

TEST_CASE("Composite key ordering is preserved", "[counting-sort]")
{
    std::vector<CardRecord> records =
    {
        {"1111111111111111", "12/2026", "123", "9999", "Visa"},
        {"2222222222222222", "01/2025", "456", "1111", "Mastercard"},
        {"3333333333333333", "08/2025", "789", "5000", "Visa"}
    };

    CountingSort(records);

    REQUIRE(records.size() == 3);
}

TEST_CASE("Merge sort preserves number of records", "[merge-sort]")
{
    std::vector<CardRecord> records =
    {
        {"1111111111111111", "12/2026", "123", "9999", "Visa"},
        {"2222222222222222", "01/2025", "456", "1111", "Mastercard"},
        {"3333333333333333", "08/2025", "789", "5000", "Visa"}
    };

    auto originalSize = records.size();

    MergeSort(records, 0, static_cast<int>(records.size()) - 1);

    REQUIRE(records.size() == originalSize);
}

TEST_CASE("CardRecord fields are stored correctly", "[record]")
{
    CardRecord card{
        "1234567890123456",
        "12/2027",
        "123",
        "4321",
        "Visa"
    };

    REQUIRE(card.cardNumber == "1234567890123456");
    REQUIRE(card.expiryDate == "12/2027");
    REQUIRE(card.verificationCode == "123");
    REQUIRE(card.pin == "4321");
    REQUIRE(card.issuingNetwork == "Visa");
}