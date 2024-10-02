#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>

bool enoughVowels(const std::string& input)
{
    auto count = [input](const char& vowel)
    { return std::count(input.cbegin(), input.cend(), vowel); };

    return count('a') + count('e') + count('i') + count('o') + count('u') > 2;
}

bool twins(const std::string& input)
{
    for (int i = 0; i < input.size() - 1; ++i)
    {
        if (input[i] == input[i + 1])
            return true;
    }

    return false;
}

bool noForbiddenPattern(const std::string& input)
{
    auto contains = [input](const std::string& pattern)
    { return input.find(pattern) != std::string::npos; };

    return !contains("ab") && !contains("cd") && !contains("pq") && !contains("xy");
}

int main()
{
    std::string   input;
    std::ifstream fileStream;
    fileStream.open("input.txt");

    size_t nice = 0;
    while (std::getline(fileStream, input))
    {
        if (!enoughVowels(input))
            continue;

        if (!twins(input))
            continue;

        if (!noForbiddenPattern(input))
            continue;

        nice++;
    }

    std::cout << nice << std::endl;

    return 0;
}