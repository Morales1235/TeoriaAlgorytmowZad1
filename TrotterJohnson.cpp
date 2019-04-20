#include "TrotterJohnson.h"

#include <algorithm>
#include <iostream>
#include <array>
#include <cmath>

int TrotterJohnson::Rank(std::vector<int>&& permutation)
{
    return Rank(permutation);
}
int TrotterJohnson::Rank(std::vector<int>& permutation)
{
    auto currSize = permutation.size();
    if(currSize < 2)
        return 0;
    auto removedIndex = GetLowerPerm(permutation);
    auto lowerRank = Rank(permutation);
    if(lowerRank % 2 == 0)
        return currSize * lowerRank + currSize - removedIndex;
    else
        return currSize * lowerRank + removedIndex - 1;
}

std::vector<int> TrotterJohnson::Unrank(int index, int permutationSize)
{
    if(permutationSize < 2)
        return {1};

    if(permutationSize == 2)
    {
        if(index == 0)
            return {1, 2};
        else if(index == 1)
            return {2,1};
    }

    int lowerIndex = index/permutationSize;
    auto lowerPermutation = Unrank(lowerIndex, permutationSize-1);
    int indexHelper = index - permutationSize*lowerIndex;

    auto insertionIterator = lowerPermutation.begin();
    if( lowerIndex % 2 == 0 )
        std::advance(insertionIterator, permutationSize - indexHelper - 1);
    else
        std::advance(insertionIterator, indexHelper);
    lowerPermutation.insert(insertionIterator, permutationSize);

    return lowerPermutation;
}

int TrotterJohnson::GetLowerPerm(std::vector<int>& permutation)
{
    auto valToRemove = std::find(std::begin(permutation), std::end(permutation), permutation.size());
    if(valToRemove != permutation.end())
        permutation.erase(valToRemove);
    else
        std::cerr << "Cos nie tak!\n";
    return std::distance(permutation.begin(), valToRemove) + 1;
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("RankTest")
{
    CHECK(TrotterJohnson::Rank(std::vector<int>{1,2}) == 0);
    CHECK(TrotterJohnson::Rank(std::vector<int>{2,1}) == 1);
    CHECK(TrotterJohnson::Rank(std::vector<int>{1,2,3}) == 0);
    CHECK(TrotterJohnson::Rank(std::vector<int>{1,3,2}) == 1);
    CHECK(TrotterJohnson::Rank(std::vector<int>{3,1,2}) == 2);
    CHECK(TrotterJohnson::Rank(std::vector<int>{3,2,1}) == 3);
    CHECK(TrotterJohnson::Rank(std::vector<int>{3,4,2,1}) == 13);
    CHECK(TrotterJohnson::Rank(std::vector<int>{1,2,3,4,5}) == 0);
}

TEST_CASE("UnrankTest")
{
    CHECK(TrotterJohnson::Unrank(0, 2) == std::vector<int>{1,2});
    CHECK(TrotterJohnson::Unrank(1, 2) == std::vector<int>{2,1});
    CHECK(TrotterJohnson::Unrank(0, 3) == std::vector<int>{1,2,3});
    CHECK(TrotterJohnson::Unrank(4, 3) == std::vector<int>{2,3,1});
    CHECK(TrotterJohnson::Unrank(13, 4) == std::vector<int>{3,4,2,1});
    CHECK(TrotterJohnson::Unrank(0, 5) == std::vector<int>{1,2,3,4,5});
}
