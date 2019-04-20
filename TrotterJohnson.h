#pragma once

#include <vector>

class TrotterJohnson
{
public:
    static int Rank(std::vector<int> &&);
    static int Rank(std::vector<int> &);

    static std::vector<int> Unrank(int, int);
private:
    static int GetLowerPerm(std::vector<int>& permutation);
};
